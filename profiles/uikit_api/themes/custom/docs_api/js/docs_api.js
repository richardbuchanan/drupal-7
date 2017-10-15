/**
 * @file
 * Attaches behaviors to the UIkit theme.
 */

(function ($) {
  'use strict';

  Drupal.behaviors.docsAPI = {
    attach: function () {
      $('a').each(function () {
        if (this.hostname !== location.host) {
          // Make sure all external links open in a new tab.
          $(this).prop('target', '_blank');

          if (/drupal/i.test(this.hostname)) {
            $(this).addClass('drupal-api');
          }
        }
      });
    }
  }
})(jQuery);