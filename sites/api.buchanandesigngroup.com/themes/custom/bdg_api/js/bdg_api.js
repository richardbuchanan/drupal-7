/**
 * @file
 * Attaches behaviors to BDG API theme.
 */

(function ($) {

  'use strict';

  if (typeof Drupal.jsAC !== 'undefined') {
    /**
     * Override of the "onkeydown" event for misc/autocomplete.js.
     */
    Drupal.jsAC.prototype.onkeydown = function (input, e) {
      if (!e) {
        e = window.event;
      }
      $(input).siblings('i').addClass('uk-icon-spin');

      switch (e.keyCode) {
        case 40: // down arrow.
          this.selectDown();
          return false;
        case 38: // up arrow.
          this.selectUp();
          return false;
        default: // All other keys.
          return true;
      }
    };

    /**
     * Override of the "setStatus" event for misc/autocomplete.js.
     */
    Drupal.jsAC.prototype.setStatus = function (status) {
      switch (status) {
        case 'begin':
          $(this.input).addClass('throbbing');
          $(this.ariaLive).html(Drupal.t('Searching for matches...'));
          break;
        case 'cancel':
        case 'error':
        case 'found':
          $(this.input).removeClass('throbbing');
          $(this.input).siblings('i').removeClass('uk-icon-spin');
          break;
      }
    }
  }
}(jQuery));
