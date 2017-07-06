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
 * Implements hook_preprocess_HOOK() for api-class-page.tpl.php.
 */
function bdg_api_preprocess_api_class_page(&$variables) {
  $alternatives = $variables['alternatives'];

  if ($alternatives) {
    $alternatives = _api_get_html_by_tags($alternatives, 'li');
    $items = [];

    foreach ($alternatives as $alternative) {
      $alternative = _api_remove_branch_from_text($alternative);
      $items[] = $alternative;
    }

    $variables['alternatives'] = theme('item_list', array('items' => $items, 'type' => 'ul'));
  }
}

/**
 * Implements hook_preprocess_HOOK() for api-constant-page.tpl.php.
 */
function bdg_api_preprocess_api_constant_page(&$variables) {
  $alternatives = $variables['alternatives'];

  if ($alternatives) {
    $alternatives = _api_get_html_by_tags($alternatives, 'li');
    $items = [];

    foreach ($alternatives as $alternative) {
      $alternative = _api_remove_branch_from_text($alternative);
      $items[] = $alternative;
    }

    $variables['alternatives'] = theme('item_list', array('items' => $items, 'type' => 'ul'));
  }
}

/**
 * Implements hook_preprocess_HOOK() for api-defined.tpl.php.
 */
function bdg_api_preprocess_api_defined(&$variables) {
  $object = $variables['object'];
  $api_file_link = api_file_link($object);
  $file_info_array = explode('<wbr />', $api_file_link);
  unset($file_info_array[0]);
  $file_link = implode('<wbr />', $file_info_array);
  $variables['file_link'] = $file_link;

  if ($object->start_line) {
    $variables['file_link'] = t('!file, line @start_line', array('!file' => $file_link, '@start_line' => $object->start_line));
  }
}

/**
 * Implements hook_preprocess_hook() for api-file-page.tpl.php.
 */
function bdg_api_preprocess_api_file_page(&$variables) {
  $alternatives = $variables['alternatives'];
  $defined = $variables['defined'];
  $defined_array = explode('/', $defined);
  unset($defined_array[0]);
  $variables['defined'] = implode('/', $defined_array);

  if ($alternatives) {
    $alternatives = _api_get_html_by_tags($alternatives, 'li');
    $items = [];

    foreach ($alternatives as $alternative) {
      $alternative = _api_remove_branch_from_text($alternative);
      $items[] = $alternative;
    }

    $variables['alternatives'] = theme('item_list', array('items' => $items, 'type' => 'ul'));
  }
}

/**
 * Implements hook_preprocess_HOOK() for api-functions.tpl.php.
 */
function bdg_api_preprocess_api_functions(&$variables) {
  foreach ($variables['functions'] as $index => $function) {
    $file = _api_remove_branch_from_beginning_text($function['file']);
    $variables['functions'][$index]['file'] = $file;
  }
}

/**
 * Implements hook_preprocess_HOOK() for api-global-page.tpl.php.
 */
function bdg_api_preprocess_api_global_page(&$variables) {
  $alternatives = $variables['alternatives'];

  if ($alternatives) {
    $alternatives = _api_get_html_by_tags($alternatives, 'li');
    $items = [];

    foreach ($alternatives as $alternative) {
      $alternative = _api_remove_branch_from_text($alternative);
      $items[] = $alternative;
    }

    $variables['alternatives'] = theme('item_list', array('items' => $items, 'type' => 'ul'));
  }
}

/**
 * Implements hook_preprocess_HOOK() for api-group-page.tpl.php.
 */
function bdg_api_preprocess_api_group_page(&$variables) {
  $alternatives = $variables['alternatives'];

  if ($alternatives) {
    $alternatives = _api_get_html_by_tags($alternatives, 'li');
    $items = [];

    foreach ($alternatives as $alternative) {
      $alternative = _api_remove_branch_from_text($alternative);
      $items[] = $alternative;
    }

    $variables['alternatives'] = theme('item_list', array('items' => $items, 'type' => 'ul'));
  }
}

/**
 * Implements hook_preprocess_HOOK() for api-property-page.tpl.php.
 */
function bdg_api_preprocess_api_property_page(&$variables) {
  $alternatives = $variables['alternatives'];

  if ($alternatives) {
    $alternatives = _api_get_html_by_tags($alternatives, 'li');
    $items = [];

    foreach ($alternatives as $alternative) {
      $alternative = _api_remove_branch_from_text($alternative);
      $items[] = $alternative;
    }

    $variables['alternatives'] = theme('item_list', array('items' => $items, 'type' => 'ul'));
  }
}

/**
 * Implements hook_preprocess_HOOK() for api-service-page.tpl.php.
 */
function bdg_api_preprocess_api_service_page(&$variables) {
  $alternatives = $variables['alternatives'];

  if ($alternatives) {
    $alternatives = _api_get_html_by_tags($alternatives, 'li');
    $items = [];

    foreach ($alternatives as $alternative) {
      $alternative = _api_remove_branch_from_text($alternative);
      $items[] = $alternative;
    }

    $variables['alternatives'] = theme('item_list', array('items' => $items, 'type' => 'ul'));
  }
}

/**
 * Implements template_preprocess_views_view_field().
 */
function bdg_api_preprocess_views_view_field(&$variables) {
  $href = _api_get_link_href($variables['output']);

  if ($href) {
    $text = _api_get_link_text($variables['output']);
    $options = array('html' => TRUE);
    $output = l($text, $href, $options);
  }
  else {
    $output = _api_remove_branch_from_beginning_text($variables['output']);
  }

  $variables['output'] = $output;
}

/**
 * Retrieves the href of an achor tag, if present.
 *
 * @param string $text
 *   The string to pull an anchor's href attribute from.
 *
 * @return bool|string
 *   Returns the anchor's href attribute, if found. Otherwise returns FALSE.
 */
function _api_get_link_href($text) {
  if (substr($text, 0, 1) == '<') {
    preg_match_all('/<a[^>]+href=([\'"])(?<href>.+?)\1[^>]*>/i', $text, $result);

    if (isset($result['href'])) {
      return urldecode($result['href'][0]);
    }
  }
  return FALSE;
}

/**
 * Retrieves the text of an anchor tag, if present.
 *
 * @param string $text
 *   The string to pull an achor's text from.
 *
 * @return bool|string
 *   Returns the anchor's text, if found. Otherwise returns FALSE.
 */
function _api_get_link_text($text) {
  preg_match('/<a[^>]*>(.*?)<\/a>/i', $text, $matches);
  return _api_remove_branch_from_beginning_text($matches[1]);
}

/**
 * Removes the API branch from a string.
 *
 * This does the same as _api_remove_branch_from_beginning_text(), except it
 * removes all occurences of the branch from the string.
 *
 * @param string $text
 *   The string to remove the branch from.
 *
 * @return string
 *   Returns the string with the API branch removed.
 */
function _api_remove_branch_from_text($text) {
  $branches = api_get_branches();

  foreach ($branches as $branch) {
    $project = $branch->project;
    $name = $branch->branch_name;
    $search = "$project-$name/";
    $text = str_replace($search, '', $text);
  }

  return $text;
}

/**
 * Removes the API branch from the beginning of a string.
 *
 * This does the same as _api_remove_branch_from_text(), except only removes
 * it from the beginning of the string. This ensures the rest of the string is
 * ignored.
 *
 * @param string $text
 *   The string to remove the branch from.
 *
 * @return string
 *   Returns the string with the API branch removed.
 */
function _api_remove_branch_from_beginning_text($text) {
  $branches = api_get_branches();

  foreach ($branches as $branch) {
    $project = $branch->project;
    $name = $branch->branch_name;
    $prefix = "$project-$name/<wbr />";

    if (substr($text, 0, strlen($prefix)) == $prefix) {
      $text = substr($text, strlen($prefix));
    }
  }

  return $text;
}

/**
 * Retrieves HTML from an HTML tag, given an HTML string.
 *
 * @param $html
 *   The HTML string to search the given tag for.
 * @param string $tag
 *   The HTML tag to search for in the given HTML string.
 *
 * @return array
 *   Returns an associative array of the HTML inside each occurence of the
 *   given tag.
 */
function _api_get_html_by_tags($html, $tag) {
  $dom = new DOMDocument();
  $dom->loadHTML($html);
  $content = array();

  foreach ($dom->getElementsByTagName($tag) as $index => $node) {
    $text = $dom->saveHTML($node);
    $text = str_replace("<$tag>", '', $text);
    $text = str_replace("</$tag>", '', $text);
    $content[$index] = trim($text);
  }

  return $content;
}
