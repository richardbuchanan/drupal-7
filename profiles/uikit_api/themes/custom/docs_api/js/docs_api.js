/**
 * @file
 * Attaches behaviors to the Docs API theme.
 */

(function ($) {
  'use strict';

  Drupal.behaviors.docsAPIExternalLinks = {
    attach: function () {
      $('a').each(function () {
        if (this.hostname !== location.host && this.hostname !== 'ftp.drupal.org') {
          // Make sure all external links open in a new tab, except project
          // download files.
          $(this).prop('target', '_blank');

          if (/drupal/i.test(this.hostname)) {
            $(this).addClass('drupal-api');
          }
        }
      });
    }
  };

  Drupal.behaviors.docsAPIDrupalAPILinks = {
    attach: function () {
      $('code').find('a').each(function () {
        if (/drupal/i.test(this.hostname)) {
          // Add the drupal-api class to linkable elements in API code elements.
          $(this).addClass('drupal-api');
        }
      });
    }
  }
})(jQuery);