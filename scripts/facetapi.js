(function ($) {
  'use strict';

  if (Drupal.facetapi && Drupal.facetapi.makeCheckbox) {
    /**
    * Replace an unclick link with a checked checkbox.
    */
    Drupal.facetapi.makeCheckbox = function() {
      var $link = $(this),
          active = $link.hasClass('facetapi-active');

      if (!active && !$link.hasClass('facetapi-inactive')) {
        // Not a facet link.
        return;
      }

      // Derive an ID and label for the checkbox based on the associated link.
      // The label is required for accessibility, but it duplicates information
      // in the link itself, so it should only be shown to screen reader users.
      var id = this.id + '--checkbox',
          description = $link.find('.element-invisible').html(),
          label = $('<label class="element-invisible" for="' + id + '">' + description + '</label>'),
          checkbox = $('<input type="checkbox" class="facetapi-checkbox" id="' + id + '" />'),
          // Get the href of the link that is this DOM object.
          href = $link.attr('href'),
          redirect = new Drupal.facetapi.Redirect(href);

      checkbox.click(function (e) {
        Drupal.facetapi.disableFacet($link.parents('ul.facetapi-facetapi-checkbox-links'));
        redirect.gotoHref();
      });

      if (active) {
        checkbox.attr('checked', true);
        // Add the checkbox and label.
        $link.before(label).before(checkbox);
      }
      else {
        $link.before(label).before(checkbox);
      }
    };
  }
}(jQuery));
