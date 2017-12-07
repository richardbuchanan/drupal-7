<?php

/**
 * Menu callback: display UIkit v2 tests.
 *
 * A clone of the UIkit git repository is stored in the "includes/uikit/v2"
 * directory. The overview page is displayed in an iframe in order to render the
 * tests.
 */
function _uikit_examples_tests_v2() {
  _uikit_examples_examples_js();
  $src = '/' . drupal_get_path('module', 'uikit_examples') . '/includes/uikit/v2/tests/overview.html';
  $output = '<iframe id="uikit-tests" src="' . $src . '" style="height: 1487px; width: 100%; box-shadow: 0 5px 15px rgba(0,0,0,0.1);"></iframe>';
  return $output;
}

/**
 * Menu callback: display UIkit v3 tests.
 *
 * A clone of the UIkit git repository is stored in the "includes/uikit/v3"
 * directory. The overview page is displayed in an iframe in order to render the
 * tests.
 */
function _uikit_examples_tests_v3() {
  _uikit_examples_examples_js();
  $src = '/' . drupal_get_path('module', 'uikit_examples') . '/includes/uikit/v3/tests/index.html';
  $output = '<iframe id="uikit-tests" src="' . $src . '" style="height: 4643px; width: 100%; box-shadow: 0 5px 15px rgba(0,0,0,0.1);"></iframe>';

  return $output;
}
