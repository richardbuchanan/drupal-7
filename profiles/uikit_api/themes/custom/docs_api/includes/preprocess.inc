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
function docs_api_preprocess_page(&$variables) {
  $docs = drupal_get_path('theme', 'docs');
  $svg_logo = '/' . $docs . '/logo_large.svg';
  $variables['logo'] = $svg_logo;

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

  $variables['page_container_attributes_array'] = array('id' => 'page');
  $variables['content_attributes_array'] = array('id' => 'page-content');
  $variables['sidebar_first_attributes_array'] = array('id' => 'sidebar-first');
  $variables['sidebar_second_attributes_array'] = array('id' => 'sidebar-second');

  if (!drupal_is_front_page()) {
    $variables['page_container_attributes_array']['class'][] = 'uk-container';
    $variables['page_container_attributes_array']['class'][] = 'uk-margin-top';
    $variables['sidebar_first_attributes_array']['class'] = array('uk-width-1-3@l');
    $variables['sidebar_second_attributes_array']['class'] = array('uk-width-1-3@l');

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
  else {
    unset($variables['header_attributes_array']['uk-sticky']);
    $variables['content_attributes_array']['class'][] = 'uk-width-1-1';
  }
}
