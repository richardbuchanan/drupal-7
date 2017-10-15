<?php

/**
 * @file
 * Conditional logic and data processing for uikit_api.
 *
 * The functions below are just examples of the most common functions a
 * sub-theme can implement. Feel free to remove these functions or implement
 * other functions.
 */

/**
 * Load UIkit's include files for theme processing.
 */
uikit_load_include('inc', 'uikit_api', 'preprocess', 'includes');
uikit_load_include('inc', 'uikit_api', 'process', 'includes');
uikit_load_include('inc', 'uikit_api', 'alter', 'includes');
uikit_load_include('inc', 'uikit_api', 'theme', 'includes');

function uikit_api_set_branch_main_page_title() {
  $branches = api_get_branches();
  $branch_main_pages = array('api');

  if (count($branches)) {
    foreach ($branches as $branch) {
      if (!in_array('api/' . $branch->project, $branch_main_pages)) {
        $branch_main_pages[] = 'api/' . $branch->project;
      }
      if (!in_array('api/' . $branch->project . '/' . $branch->branch_name, $branch_main_pages)) {
        $branch_main_pages[] = 'api/' . $branch->project . '/' . $branch->branch_name;
      }
    }
  }

  if (in_array(current_path(), $branch_main_pages)) {
    $branch = api_get_active_branch();
    drupal_set_title($branch->title);
  }
}

function uikit_api_get_active_branch_routes() {
  $active_branch = api_get_active_branch();
  return array(
    'api',
    'api/' . $active_branch->project,
    'api/' . $active_branch->project . '/' . $active_branch->branch_name,
  );
}
