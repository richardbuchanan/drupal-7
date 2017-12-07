(function($) {
  'use strict';

  var $iframe = $('#uikit-tests');

  $iframe.load(function () {
    // Resize the iframe to fit the content height.
    this.style.height = (this.contentWindow.document.documentElement.offsetHeight) + 'px';

    // We initially hide the iframe. After resizing, show the content and
    // perform a click event so the container element is also resized. Otherwise
    // we end up having a container with a smaller height than the iframe which
    // displays a horizontal scroll bar.
    $(this).show().click();
  });
})(jQuery);
