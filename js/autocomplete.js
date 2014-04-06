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
