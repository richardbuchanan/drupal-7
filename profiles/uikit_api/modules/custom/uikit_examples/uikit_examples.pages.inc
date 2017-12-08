<?php

/**
 * @file
 * Page callbacks for the UIkit Examples module.
 */

/**
 * Menu callback: display UIkit v3 examples.
 *
 * A clone of the UIkit git repository is stored in the "includes/uikit/v3"
 * directory. The overview page is displayed in an iframe in order to render the
 * tests.
 */
function _uikit_examples_examples_v3() {
  _uikit_examples_examples_js();
  $src = '/' . drupal_get_path('module', 'uikit_examples') . '/includes/uikit/v3/tests/index.html';

  $output = '<p>This overview gives you a hint of what you can do with UIkit. The examples are rendered using the default styling for the selected UIkit version.</p>';
  $output .= '<iframe id="uikit-tests" src="' . $src . '" style="height: 4643px; width: 100%; box-shadow: 0 5px 15px rgba(0,0,0,0.1);"></iframe>';

  return $output;
}

/**
 * Menu callback: display UIkit v2 examples.
 *
 * A clone of the UIkit git repository is stored in the "includes/uikit/v2"
 * directory. The overview page is displayed in an iframe in order to render the
 * tests.
 */
function _uikit_examples_examples_v2() {
  _uikit_examples_examples_js();
  $src = '/' . drupal_get_path('module', 'uikit_examples') . '/includes/uikit/v2/tests/overview.html';

  $output = '<p>This overview gives you a hint of what you can do with UIkit. The examples are rendered using the default styling for the selected UIkit version.</p>';
  $output .= '<iframe id="uikit-tests" src="' . $src . '" style="height: 1487px; width: 100%; box-shadow: 0 5px 15px rgba(0,0,0,0.1);"></iframe>';

  return $output;
}

/**
 * Menu callback: display UIkit v3 documentation.
 */
function _uikit_examples_docs_v3() {
  $output = '<div class="uk-cover-background uk-position-relative" style="height: 300px;">';
  $output .= '<div class="uk-position-cover uk-flex uk-flex-center uk-flex-middle">';
  $output .= '<div style="background: transparent; font-size: 50px; line-height: 75px; color: #2ba3d4; height: 300px; width: 100%; text-align: center;">';
  $output .= '<span style="display: block; padding: 112px 0; vertical-align: middle;">Coming Soon!</span>';
  $output .= '</div>';
  $output .= '</div>';
  $output .= '</div>';

  return $output;
}

/**
 * Menu callback: display UIkit v2 documentation.
 */
function _uikit_examples_docs_v2() {
  $output = '<div class="uk-cover-background uk-position-relative" style="height: 300px;">';
  $output .= '<div class="uk-position-cover uk-flex uk-flex-center uk-flex-middle">';
  $output .= '<div style="background: transparent; font-size: 50px; line-height: 75px; color: #2ba3d4; height: 300px; width: 100%; text-align: center;">';
  $output .= '<span style="display: block; padding: 112px 0; vertical-align: middle;">Coming Soon!</span>';
  $output .= '</div>';
  $output .= '</div>';
  $output .= '</div>';

  return $output;
}
