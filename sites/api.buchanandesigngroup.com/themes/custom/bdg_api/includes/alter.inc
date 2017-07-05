<?php

/**
 * @file
 * Modify structured content arrays.
 *
 * These hooks are called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * content structure has been built.
 *
 * If the theme wishes to act on the rendered HTML of the content rather than
 * the structured content array, it may use this hook to add a #post_render
 * callback. Alternatively, it could also implement hook_preprocess_HOOK().
 *
 * @see drupal_render()
 * @see theme()
 */

/**
 * Implements hook_page_alter().
 */
function bdg_api_page_alter(&$page) {
  $content = isset($page['content']['system_main']) && isset($page['content']['system_main']['main']) ? $page['content']['system_main']['main']['#markup'] : FALSE;

  if ($content) {
    $page['content']['system_main']['main']['#markup'] = str_replace('drupal-7.x/<wbr />', '', $content);
    $page['content']['system_main']['main']['#markup'] = str_replace('drupal-8.0.x/<wbr />', '', $content);
    $page['content']['system_main']['main']['#markup'] = str_replace('drupal-8.1.x/<wbr />', '', $content);
    $page['content']['system_main']['main']['#markup'] = str_replace('drupal-8.2.x/<wbr />', '', $content);
    $page['content']['system_main']['main']['#markup'] = str_replace('drupal-8.3.x/<wbr />', '', $content);
    $page['content']['system_main']['main']['#markup'] = str_replace('drupal-8.4.x/<wbr />', '', $content);
  }
}
