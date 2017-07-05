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
