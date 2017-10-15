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
function uikit_api_block_view_alter(&$data, $block) {
  $branch = api_get_active_branch();

  if ($block->module == 'api' && $block->delta == 'navigation') {
    if (user_access('access API reference') && !empty($branch)) {
      // Figure out if this is the default branch for this project, the same
      // way the menu system decides.
      $projects = _api_make_menu_projects();
      $is_default = ($branch->branch_name === $projects[$branch->project]['use branch']);
      $suffix = ($is_default) ? '' : '/' . $branch->branch_name;

      // Determine if the branch main page route is active and add the uk-active
      // class to the options array.
      $active_branch_routes = uikit_api_get_active_branch_routes();
      $options = array();
      $main_page = 'api/' . $branch->project . $suffix;
      if (in_array($main_page, $active_branch_routes) && in_array(current_path(), $active_branch_routes)) {
        $options['attributes']['class'][] = 'uk-active';
      }

      $links = [];
      $links[] = l($branch->title, $main_page, $options);
      $types = api_listing_types($branch);

      if ($types['groups']) {
        $options = array();
        if (current_path() == 'api/' . $branch->project . '/groups/' . $branch->branch_name) {
          $options['attributes']['class'][] = 'uk-active';
        }
        $links[] = l(t('Topics'), 'api/' . $branch->project . '/groups' . $suffix, $options);
      }

      if ($types['classes']) {
        $options = array();
        if (current_path() == 'api/' . $branch->project . '/classes/' . $branch->branch_name) {
          $options['attributes']['class'][] = 'uk-active';
        }
        $links[] = l(t('Classes'), 'api/' . $branch->project . '/classes' . $suffix, $options);
      }

      if ($types['functions']) {
        $options = array();
        if (current_path() == 'api/' . $branch->project . '/functions/' . $branch->branch_name) {
          $options['attributes']['class'][] = 'uk-active';
        }
        $links[] = l(t('Functions'), 'api/' . $branch->project . '/functions' . $suffix, $options);
      }

      if ($types['files']) {
        $options = array();
        if (current_path() == 'api/' . $branch->project . '/files/' . $branch->branch_name) {
          $options['attributes']['class'][] = 'uk-active';
        }
        $links[] = l(t('Files'), 'api/' . $branch->project . '/files' . $suffix, $options);
      }

      if ($types['namespaces']) {
        $options = array();
        if (current_path() == 'api/' . $branch->project . '/namespaces/' . $branch->branch_name) {
          $options['attributes']['class'][] = 'uk-active';
        }
        $links[] = l(t('Namespaces'), 'api/' . $branch->project . '/namespaces' . $suffix, $options);
      }

      if ($types['services']) {
        $options = array();
        if (current_path() == 'api/' . $branch->project . '/services/' . $branch->branch_name) {
          $options['attributes']['class'][] = 'uk-active';
        }
        $links[] = l(t('Services'), 'api/' . $branch->project . '/services' . $suffix, $options);
      }

      if ($types['elements']) {
        $options = array();
        if (current_path() == 'api/' . $branch->project . '/elements/' . $branch->branch_name) {
          $options['attributes']['class'][] = 'uk-active';
        }
        $links[] = l(t('Elements'), 'api/' . $branch->project . '/elements' . $suffix, $options);
      }

      if ($types['constants']) {
        $options = array();
        if (current_path() == 'api/' . $branch->project . '/constants/' . $branch->branch_name) {
          $options['attributes']['class'][] = 'uk-active';
        }
        $links[] = l(t('Constants'), 'api/' . $branch->project . '/constants' . $suffix, $options);
      }

      if ($types['globals']) {
        $options = array();
        if (current_path() == 'api/' . $branch->project . '/globals/' . $branch->branch_name) {
          $options['attributes']['class'][] = 'uk-active';
        }
        $links[] = l(t('Globals'), 'api/' . $branch->project . '/globals' . $suffix, $options);
      }

      if ($types['deprecated']) {
        $options = array();
        if (current_path() == 'api/' . $branch->project . '/deprecated/' . $branch->branch_name) {
          $options['attributes']['class'][] = 'uk-active';
        }
        $links[] = l(t('Deprecated'), 'api/' . $branch->project . '/deprecated' . $suffix, $options);
      }

      $data = array(
        'subject' => t('API Navigation'),
        'content' => theme('item_list', array(
          'items' => $links,
          'attributes' => array(
            'class' => array(
              'uk-nav',
              'uk-nav-default',
              'tm-nav',
              'uk-nav-parent-icon',
              'api-navigation-nav',
            ),
          ),
        )),
      );
    }
  }
}
