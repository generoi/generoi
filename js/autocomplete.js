(function($) {
  /**
   * Override Drupal autocomplete to submit when an option is selected.
   */
  if (Drupal.jsAC) {
    Drupal.jsAC.prototype.select = function(node) {
      this.input.value = jQuery(node).data('autocompleteValue');
      if (jQuery(this.input).hasClass('form-autocomplete')) {
        this.input.form.submit();
      }
    };
  }

  /**
   * Handler for the "onkeydown" event.
   *
   * Overwritten from Drupal's autocomplete.js to automatically selects
   * the highlighted item if the input has the auto-submit call and the
   * user presses enter.
   */
  Drupal.jsAC.prototype.onkeyup = function (input, e) {
    if (!e) {
      e = window.event;
    }
    switch (e.keyCode) {
      case 16: // Shift.
      case 17: // Ctrl.
      case 18: // Alt.
      case 20: // Caps lock.
      case 33: // Page up.
      case 34: // Page down.
      case 35: // End.
      case 36: // Home.
      case 37: // Left arrow.
      case 38: // Up arrow.
      case 39: // Right arrow.
      case 40: // Down arrow.
        return true;

      case 9:  // Tab.
      case 13: // Enter.
      case 27: // Esc.
        this.hidePopup(e.keyCode);
        if (13 == e.keyCode && $(input).hasClass('auto_submit')) {
          input.form.submit();
        }
        return true;

      default: // All other keys.
        if (input.value.length > 0 && !input.readOnly) {
          this.populatePopup();
        }
        else {
          this.hidePopup(e.keyCode);
        }
        return true;
    }
  };

  /**
   * Remove autocomplete attribute from search fields.
   */
  Drupal.behaviors.removeAutocomplete = {
    attach: function(context) {
      $(document).on('focus', '.form-autocomplete', function() {
        $(this).attr('autocomplete', 'off');
      });
    }
  };
}(jQuery));
