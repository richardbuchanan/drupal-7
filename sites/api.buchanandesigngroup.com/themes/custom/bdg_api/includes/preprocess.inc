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
 * Implements template_preprocess_page().
 */
function bdg_api_preprocess_page(&$variables) {
  $bdg_api = drupal_get_path('theme', 'bdg_api');
  $variables['logo_small'] = "/$bdg_api/logo-small.png";
}

/**
 * Implements hook_preprocess_HOOK() for block.tpl.php.
 */
function bdg_api_preprocess_block(&$variables) {
  $variables['title_attributes_array']['class'][] = 'block-title';
}

/**
 * Implements hook_preprocess_HOOK() for theme_item_list().
 */
function bdg_api_preprocess_item_list(&$variables) {
  if (isset($variables['striped']) && $variables['striped']) {
    $variables['attributes']['class'][] = 'uk-list-striped';
  }
  if (isset($variables['line']) && $variables['line']) {
    $variables['attributes']['class'][] = 'uk-list-line';
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_link().
 */
function bdg_api_preprocess_link(&$variables) {
  $classes = isset($variables['options']['attributes']) && isset($variables['options']['attributes']['class']) ? $variables['options']['attributes']['class'] : array();

  if (in_array('active', $classes)) {
    $variables['options']['attributes']['class'][] = 'uk-active';
  }
}

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
  $variables['classes_array'][] = 'sticky-enabled';
  $variables['classes_array'][] = 'uk-table';
  $variables['classes_array'][] = 'uk-table-striped';
  $variables['classes_array'][] = 'uk-table-hover';
}
