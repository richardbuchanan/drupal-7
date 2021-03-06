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
 * Implements template_process_html().
 */
function uikit_process_html(&$variables) {
  // Convert attribute arrays to an attribute string.
  $variables['html_attributes'] = drupal_attributes($variables['html_attributes_array']);
}

/**
 * Implements template_process_page().
 */
function uikit_process_page(&$variables) {
  // Convert attribute arrays to an attribute string.
  $variables['page_container_attributes'] = drupal_attributes($variables['page_container_attributes_array']);
  $variables['sidebar_first_attributes'] = drupal_attributes($variables['sidebar_first_attributes_array']);
  $variables['sidebar_second_attributes'] = drupal_attributes($variables['sidebar_second_attributes_array']);
  $variables['header_attributes'] = drupal_attributes($variables['header_attributes_array']);
  $variables['navbar_attributes'] = drupal_attributes($variables['navbar_attributes_array']);
}

/**
 * Implements template_process_maintenance_page().
 */
function uikit_process_maintenance_page(&$variables) {
  $variables['content_attributes'] = drupal_attributes($variables['content_attributes_array']);
  $variables['sidebar_first_attributes'] = drupal_attributes($variables['sidebar_first_attributes_array']);
  $variables['sidebar_second_attributes'] = drupal_attributes($variables['sidebar_second_attributes_array']);
}

/**
 * Implements hook_process_HOOK() for region.tpl.php.
 */
function uikit_process_region(&$variables) {
  // Convert attribute arrays to an attribute string.
  $attributes = $variables['wrapper_attributes_array'];
  $variables['wrapper_attributes'] = drupal_attributes($attributes);
}

/**
 * Implements hook_preprocess_HOOK() for theme_html_tag().
 */
function uikit_process_html_tag(&$variables) {
  $element = &$variables['element'];

  // Remove type="..." and CDATA prefix/suffix.
  unset($element['#attributes']['type'], $element['#value_prefix'], $element['#value_suffix']);

  // Remove media="all" but leave others unaffected.
  if (isset($element['#attributes']['media']) && $element['#attributes']['media'] === 'all') {
    unset($element['#attributes']['media']);
  }
}

/**
 * Implements hook_process_HOOK() for theme_menu_local_tasks().
 */
function uikit_process_menu_local_tasks(&$variables) {
  // Convert attribute arrays to an attribute string.
  $variables['primary_attributes'] = drupal_attributes($variables['primary_attributes_array']);
  $variables['secondary_attributes'] = drupal_attributes($variables['secondary_attributes_array']);
}
