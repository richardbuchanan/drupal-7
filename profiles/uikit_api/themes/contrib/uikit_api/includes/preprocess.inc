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
 * Implements template_preprocess_html().
 */
function uikit_api_preprocess_html(&$variables) {
  drupal_add_css('//fonts.googleapis.com/css?family=Montserrat:300,400', array('type' => 'external'));
  drupal_add_css('//fonts.googleapis.com/css?family=Roboto+Mono:300,400', array('type' => 'external'));

  if (in_array('page-api-drupal-documentationtopicsforms-api-referencehtml', $variables['classes_array'])) {
    $variables['classes_array'][] = 'page-forms-api-reference';
  }
}

/**
 * Implements template_preprocess_page().
 */
function uikit_api_preprocess_page(&$variables) {
  uikit_api_set_branch_main_page_title();
  $sticky = 'media: 960';

  if (user_access('access toolbar') || user_access('access administration menu')) {
    $sticky = 'media: 960; offset: 29';
  }

  $variables['header_attributes_array'] = array(
    'uk-sticky' => $sticky,
    'class' => array(
      'uk-navbar-container',
      'tm-navbar-container',
      'uk-sticky',
      'uk-sticky-fixed',
    ),
  );

  $variables['navbar_attributes_array']['class'] = array('uk-nav');
  $sidebar_first = isset($variables['page']['sidebar_first']) ? $variables['page']['sidebar_first'] : '';
  $sidebar_second = isset($variables['page']['sidebar_second']) ? $variables['page']['sidebar_second'] : '';

  $variables['content_attributes_array'] = array(
    'id' => 'page-content',
  );

  $variables['sidebar_first_attributes_array'] = array(
    'id' => 'sidebar-first',
    'class' => array('uk-width-1-3@l'),
  );

  $variables['sidebar_second_attributes_array'] = array(
    'id' => 'sidebar-second',
    'class' => array('uk-width-1-3@l'),
  );

  if (!empty($sidebar_first) && !empty($sidebar_second)) {
    $variables['content_attributes_array']['class'][] = 'uk-width-1-3@l';
    $variables['content_attributes_array']['class'][] = 'uk-push-1-3@l';

    $variables['sidebar_first_attributes_array']['class'][] = 'uk-width-1-3@l';
    $variables['sidebar_first_attributes_array']['class'][] = 'uk-pull-2-3@l';

    $variables['sidebar_second_attributes_array']['class'][] = 'uk-width-1-3@l';
    $variables['sidebar_second_attributes_array']['class'][] = 'uk-push-pull-@l';
  }
  elseif (!empty($sidebar_first)) {
    $variables['content_attributes_array']['class'][] = 'uk-width-2-3@l';
    $variables['content_attributes_array']['class'][] = 'uk-push-1-3@l';

    $variables['sidebar_first_attributes_array']['class'][] = 'uk-width-1-3@l';
    $variables['sidebar_first_attributes_array']['class'][] = 'uk-pull-2-3@l';
  }
  elseif (!empty($sidebar_second)) {
    $variables['content_attributes_array']['class'][] = 'uk-width-2-3@l';
    $variables['content_attributes_array']['class'][] = 'uk-push-pull-@l';

    $variables['sidebar_second_attributes_array']['class'][] = 'uk-width-1-3@l';
    $variables['sidebar_second_attributes_array']['class'][] = 'uk-push-pull-@l';
  }
  elseif (empty($sidebar_first) && empty($sidebar_second)) {
    $variables['content_attributes_array']['class'][] = 'uk-width-1-1';
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_breadcrumb().
 */
function uikit_api_preprocess_breadcrumb(&$variables) {
  $breadcrumb = $variables['breadcrumb'] ? count($variables['breadcrumb']) : 0;

  if ($breadcrumb <= 2) {
    $variables['breadcrumb'] = array();
  }
  else {
    array_shift($variables['breadcrumb']);
    array_shift($variables['breadcrumb']);
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_button().
 */
function uikit_api_preprocess_button(&$variables) {
  $variables['element']['#attributes']['class'] = array('uk-button');

  switch ($variables['element']['#value']) {
    case 'Apply':
    case 'Create new account':
    case 'E-mail new password':
    case 'Log in':
    case 'Preview':
    case 'Save':
    case 'Search':
      $variables['element']['#attributes']['class'][] = 'uk-button-primary';
      break;

    default:
      $variables['element']['#attributes']['class'][] = 'uk-button-default';
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_textfield().
 */
function uikit_api_preprocess_textfield(&$variables) {
  $parents = isset($variables['element']['#parents']) ? $variables['element']['#parents'] : array();

  if (in_array('search', $parents)) {
    $variables['theme_hook_suggestions'][] = 'textfield__search';
  }
}

/**
 * Implements hook_preprocess_HOOK() for views-view-table.tpl.php.
 */
function uikit_api_preprocess_views_view_table(&$variables) {
  $variables['classes_array'][] = 'uk-table';
  $variables['classes_array'][] = 'uk-table-divider';
  $variables['classes_array'][] = 'uk-table-striped';
  $variables['attributes_array']['class'] = $variables['classes_array'];

  foreach ($variables['header'] as $field => $label) {
    $variables['header_attributes_array'][$field] = array();

    if ($variables['header_classes'][$field]) {
      $header_classes = explode(' ', $variables['header_classes'][$field]);
    }

    $header_classes[] = 'uk-text-nowrap';
    $variables['header_attributes_array'][$field]['class'] = $header_classes;
    $variables['header_attributes_array'][$field]['scope'] = 'col';
  }

  foreach ($variables['rows'] as $row_count => $row) {
    if ($variables['row_classes'][$row_count]) {
      $variables['row_attributes_array'][$row_count]['class'] = $variables['row_classes'][$row_count];
    }

    foreach ($row as $field => $content) {
      $variables['field_attributes_array'][$field][$row_count] = array();

      if ($variables['field_classes'][$field][$row_count]) {
        $field_classes = explode(' ', $variables['field_classes'][$field][$row_count]);
        $variables['field_attributes_array'][$field][$row_count]['class'] = $field_classes;
      }
    }
  }
}
