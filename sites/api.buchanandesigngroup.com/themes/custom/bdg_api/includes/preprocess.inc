<?php

/**
 * @file
 * Set up variables to be placed within the template (.tpl.php) files.
 *
 * The variables set up here apply to both templates (.tpl.php) files and
 * functions (theme_HOOK). These are also used for providing
 * @link https://www.drupal.org/node/223440 template suggestions @endlink.
 *
 * @see process.inc
 */

/**
 * Implements hook_preprocess_HOOK() for theme_menu_local_tasks().
 */
function bdg_api_preprocess_menu_local_tasks(&$variables) {
  $variables['primary_attributes_array']['class'][] = 'uk-margin-bottom';
  $variables['secondary_attributes_array']['class'][] = 'uk-margin-bottom';
}

/**
 * Implements template_preprocess_views_view_table().
 */
function bdg_api_preprocess_views_view_table(&$variables) {
  drupal_add_js('misc/tableheader.js');
  // Add 'sticky-enabled' class to the table to identify it for JS.
  // This is needed to target tables constructed by this function.
  $variables['classes_array'][] = 'sticky-enabled';
  $variables['classes_array'][] = 'uk-table';
  $variables['classes_array'][] = 'uk-table-striped';
  $variables['classes_array'][] = 'uk-table-hover';
}
