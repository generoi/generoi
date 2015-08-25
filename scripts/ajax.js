if (Drupal.ajax) {
  /**
  * Handler for the form redirection error.
  */
  Drupal.ajax.prototype.error = function (xmlhttprequest, uri, customMessage) {
    console.log(xmlhttprequest, uri, customMessage);
    window.alert(Drupal.t('An unexpected error has occurred.'));
    // Remove the progress element.
    if (this.progress.element) {
      $(this.progress.element).remove();
    }
    if (this.progress.object) {
      this.progress.object.stopMonitoring();
    }
    // Undo hide.
    $(this.wrapper).show();
    // Re-enable the element.
    $(this.element).removeClass('progress-disabled').removeAttr('disabled');
    // Reattach behaviors, if they were detached in beforeSerialize().
    if (this.form) {
      var settings = this.settings || Drupal.settings;
      Drupal.attachBehaviors(this.form, settings);
    }
  };

  /**
  * Handle an event that triggers an Ajax response.
  *
  * When an event that triggers an Ajax response happens, this method will
  * perform the actual Ajax call. It is bound to the event using
  * bind() in the constructor, and it uses the options specified on the
  * ajax object.
  */
  Drupal.ajax.prototype.eventResponse = function (element, event) {
    // Create a synonym for this to reduce code confusion.
    var ajax = this;

    // Do not perform another ajax command if one is already in progress.
    if (ajax.ajaxing) {
      return false;
    }

    try {
      if (ajax.form) {
        // If setClick is set, we must set this to ensure that the button's
        // value is passed.
        if (ajax.setClick) {
          // Mark the clicked button. 'form.clk' is a special variable for
          // ajaxSubmit that tells the system which element got clicked to
          // trigger the submit. Without it there would be no 'op' or
          // equivalent.
          element.form.clk = element;
        }

        ajax.form.ajaxSubmit(ajax.options);
      }
      else {
        ajax.beforeSerialize(ajax.element, ajax.options);
        $.ajax(ajax.options);
      }
    }
    catch (e) {
      // Unset the ajax.ajaxing flag here because it won't be unset during
      // the complete response.
      ajax.ajaxing = false;
      console.log("An error occurred while attempting to process " + ajax.options.url + ": " + e.message);
      window.alert(Drupal.t('An unexpected error has occurred.'));
    }

    // For radio/checkbox, allow the default event. On IE, this means letting
    // it actually check the box.
    if (typeof element.type !== 'undefined' && (element.type === 'checkbox' || element.type === 'radio')) {
      return true;
    } else {
      return false;
    }

  };
}
