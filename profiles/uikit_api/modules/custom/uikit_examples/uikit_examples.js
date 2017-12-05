(function($) {
  'use strict';

  var $iframe = $('#uikit-tests');

  $iframe.load(function () {
    this.style.height = (this.contentWindow.document.body.offsetHeight + 200) + 'px';
    $(this).show().click();
  });
})(jQuery);
