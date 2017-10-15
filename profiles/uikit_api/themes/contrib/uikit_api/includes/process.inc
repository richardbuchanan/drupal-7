<?php

/**
 * @file
 * Set up variables to be placed within the template (.tpl.php) files.
 *
 * The variables set up here apply to both templates (.tpl.php) files and
 * functions (theme_HOOK). See preprocess.inc for providing
 * @link https://www.drupal.org/node/223440 template suggestions @endlink.
 *
 * @see preprocess.inc
 */

/**
 * Implements hook_process_HOOK() for views-view-table.tpl.php.
 */
function uikit_api_process_views_view_table(&$variables) {
  foreach ($variables['header'] as $field => $label) {
    $variables['header_attributes'][$field] = drupal_attributes($variables['header_attributes_array'][$field]);
  }

  foreach ($variables['rows'] as $row_count => $row) {
    $variables['row_attributes'][$row_count] = drupal_attributes($variables['row_attributes_array'][$row_count]);

    foreach ($row as $field => $content) {
      $variables['field_attributes'][$field][$row_count] = drupal_attributes($variables['field_attributes_array'][$field][$row_count]);
    }
  }
}
