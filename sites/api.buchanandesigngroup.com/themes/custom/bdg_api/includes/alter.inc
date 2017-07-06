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
 * Implements hook_block_view_alter().
 */
function bdg_api_block_view_alter(&$data, $block) {
  if ($block->delta == 'navigation' && $block->module == 'api') {
    $data['content'] = str_replace('uk-list', 'uk-list uk-list-striped', $data['content']);
  }
  if ($block->delta == 'powered-by' && $block->module == 'system') {
    $args = array(
      '@license' => 'https://www.gnu.org/licenses/old-licenses/gpl-2.0.html',
      '@trademark' => 'http://drupal.com/trademark',
      '@dries' => 'http://buytaert.net/',
    );

    $output[] = t('All source code and documentation on this site is released under the terms of the <a href="@license" target="_blank">GNU General Public License, version 2 and later</a>.', $args);
    $output[] = t('Drupal is a <a href="@trademark" target="_blank">registered trademark</a> of <a href="@dries" target="_blank">Dries Buytaert</a>.', $args);
    $data['content'] = implode(' ', $output);
  }
}
