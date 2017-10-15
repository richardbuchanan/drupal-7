/**
 * @file
 * Attaches behaviors for uikit_api.
 */

(function ($) {

  'use strict';

  Drupal.behaviors.UIkitAPI = {
    attach: function () {
      $('table[border="1"]')
        .removeAttr('border')
        .addClass('uk-table')
        .addClass('uk-table-divider')
        .addClass('uk-table-striped')
        .addClass('uk-table-small')
        .wrap('<div class="uk-overflow-auto"></div>')
        .show();

      $('table.uk-table').wrap('<div class="uk-overflow-auto"></div>');

      $('.uk-overflow-auto').doubleScroll();
    }
  };

  $.fn.doubleScroll = function(userOptions) {

    // Default options
    var options = {
      contentElement: undefined, // Widest element, if not specified first child element will be used
      scrollCss: {
        'overflow-x': 'auto',
        'overflow-y': 'hidden'
      },
      contentCss: {
        'overflow-x': 'auto',
        'overflow-y': 'hidden'
      },
      onlyIfScroll: true, // top scrollbar is not shown if the bottom one is not present
      resetOnWindowResize: false, // recompute the top ScrollBar requirements when the window is resized
      timeToWaitForResize: 30 // wait for the last update event (usefull when browser fire resize event constantly during ressing)
    };

    $.extend(true, options, userOptions);

    // do not modify
    // internal stuff
    $.extend(options, {
      topScrollBarMarkup: '<div class="doubleScroll-scroll-wrapper" style="height: 20px;"><div class="doubleScroll-scroll" style="height: 20px;"></div></div>',
      topScrollBarWrapperSelector: '.doubleScroll-scroll-wrapper',
      topScrollBarInnerSelector: '.doubleScroll-scroll'
    });

    var _showScrollBar = function($self, options) {

      if (options.onlyIfScroll && $self.get(0).scrollWidth <= $self.width()) {
        // content doesn't scroll
        // remove any existing occurrence...
        $self.prev(options.topScrollBarWrapperSelector).remove();
        return;
      }

      // add div that will act as an upper scroll only if not already added to the DOM
      var $topScrollBar = $self.prev(options.topScrollBarWrapperSelector);

      if ($topScrollBar.length === 0) {

        // creating the scrollbar
        // added before in the DOM
        $topScrollBar = $(options.topScrollBarMarkup);
        $self.before($topScrollBar);

        // apply the css
        $topScrollBar.css(options.scrollCss);
        $self.css(options.contentCss);

        // bind upper scroll to bottom scroll
        $topScrollBar.bind('scroll.doubleScroll', function() {
          $self.scrollLeft($topScrollBar.scrollLeft());
        });

        // bind bottom scroll to upper scroll
        var selfScrollHandler = function() {
          $topScrollBar.scrollLeft($self.scrollLeft());
        };
        $self.bind('scroll.doubleScroll', selfScrollHandler);
      }

      // find the content element (should be the widest one)
      var $contentElement;

      if (options.contentElement !== undefined && $self.find(options.contentElement).length !== 0) {
        $contentElement = $self.find(options.contentElement);
      } else {
        $contentElement = $self.find('>:first-child');
      }

      // set the width of the wrappers
      $(options.topScrollBarInnerSelector, $topScrollBar).width($contentElement.outerWidth());
      $topScrollBar.width($self.width());
      $topScrollBar.scrollLeft($self.scrollLeft());

    };

    return this.each(function() {

      var $self = $(this);

      _showScrollBar($self, options);

      // bind the resize handler
      // do it once
      if (options.resetOnWindowResize) {

        var id;
        var handler = function() {
          _showScrollBar($self, options);
        };

        $(window).bind('resize.doubleScroll', function() {
          // adding/removing/replacing the scrollbar might resize the window
          // so the resizing flag will avoid the infinite loop here...
          clearTimeout(id);
          id = setTimeout(handler, options.timeToWaitForResize);
        });

      }

    });

  }
})(jQuery);
