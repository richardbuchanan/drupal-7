<?php

/**
 * @file
 * The UIkit theme system, which controls the output of the BDG API theme.
 *
 * @ingroup bdg_api_themeable
 */

/**
 * Implements theme_menu_tree() for the user menu.
 */
function bdg_api_menu_tree__user_menu($variables) {
  return '<ul class="uk-subnav uk-subnav-line uk-flex-center">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_table().
 */
function bdg_api_table($variables) {
  $header = $variables['header'];
  $rows = $variables['rows'];
  $attributes = $variables['attributes'];
  $caption = $variables['caption'];
  $colgroups = $variables['colgroups'];
  $sticky = $variables['sticky'];
  $empty = $variables['empty'];

  // Add sticky headers, if applicable.
  if (count($header) && $sticky) {
    drupal_add_js('misc/tableheader.js');
    // Add 'sticky-enabled' class to the table to identify it for JS.
    // This is needed to target tables constructed by this function.
    $attributes['class'][] = 'sticky-enabled';
  }

  $output = '<div class="uk-overflow-container uk-margin-bottom">';
  $output .= '<table' . drupal_attributes($attributes) . '>';

  if (isset($caption)) {
    $output .= '<caption>' . $caption . '</caption>';
  }

  // Format the table columns:
  if (count($colgroups)) {
    foreach ($colgroups as $colgroup) {
      $attributes = array();

      // Check if we're dealing with a simple or complex column.
      if (isset($colgroup['data'])) {
        foreach ($colgroup as $key => $value) {
          if ($key == 'data') {
            $cols = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $cols = $colgroup;
      }

      // Build colgroup.
      if (is_array($cols) && count($cols)) {
        $output .= ' <colgroup' . drupal_attributes($attributes) . '>';

        foreach ($cols as $col) {
          $output .= ' <col' . drupal_attributes($col) . ' />';
        }

        $output .= '</colgroup>';
      }
      else {
        $output .= ' <colgroup' . drupal_attributes($attributes) . ' />';
      }
    }
  }

  // Add the 'empty' row message if available.
  if (!count($rows) && $empty) {
    $header_count = 0;

    foreach ($header as $header_cell) {
      if (is_array($header_cell)) {
        $header_count += isset($header_cell['colspan']) ? $header_cell['colspan'] : 1;
      }
      else {
        $header_count++;
      }
    }

    $rows[] = array(
      array(
        'data' => $empty,
        'colspan' => $header_count,
        'class' => array('empty', 'message'),
      ),
    );
  }

  // Format the table header:
  if (count($header)) {
    $ts = tablesort_init($header);
    // HTML requires that the thead tag has tr tags in it followed by tbody
    // tags. Using ternary operator to check and see if we have any rows.
    $output .= (count($rows) ? '<thead><tr class="uk-text-left">' : '<tr>');

    foreach ($header as $cell) {
      $cell = tablesort_header($cell, $header, $ts);
      $output .= _theme_table_cell($cell, TRUE);
    }

    // Using ternary operator to close the tags based on whether or not there
    // are rows.
    $output .= (count($rows) ? '</tr></thead>' : '</tr>');
  }
  else {
    $ts = array();
  }

  // Format the table rows:
  if (count($rows)) {
    $output .= '<tbody>';
    $flip = array('even' => 'odd', 'odd' => 'even');
    $class = 'even';

    foreach ($rows as $row) {
      // Check if we're dealing with a simple or complex row.
      if (isset($row['data'])) {
        $cells = $row['data'];
        $no_striping = isset($row['no_striping']) ? $row['no_striping'] : FALSE;

        // Set the attributes array and exclude 'data' and 'no_striping'.
        $attributes = $row;
        unset($attributes['data']);
        unset($attributes['no_striping']);
      }
      else {
        $cells = $row;
        $attributes = array();
        $no_striping = FALSE;
      }

      if (count($cells)) {
        // Add odd/even class.
        if (!$no_striping) {
          $class = $flip[$class];
          $attributes['class'][] = $class;
        }

        $attributes['class'][] = 'uk-text-left';

        // Build row.
        $output .= '<tr' . drupal_attributes($attributes) . '>';
        $i = 0;

        foreach ($cells as $cell) {
          $cell = tablesort_cell($cell, $header, $ts, $i++);
          $output .= _theme_table_cell($cell);
        }
        $output .= '</tr>';
      }
    }
    $output .= '</tbody>';
  }

  $output .= '</table>';
  $output .= '</div>';
  return $output;
}

/**
 * Implements theme_textfield().
 */
function bdg_api_textfield($variables) {
  $element = $variables['element'];

  element_set_attributes($element, array(
    'id',
    'name',
    'value',
    'size',
    'maxlength',
  ));

  _form_set_class($element, array('form-text'));
  $element['#attributes']['type'] = 'text';
  $element['#attributes']['size'] = '25';
  $extra = '';
  $prefix = '';
  $suffix = '';

  if ($element['#autocomplete_path'] && !empty($element['#autocomplete_input'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';

    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#autocomplete_input']['#id'];
    $attributes['value'] = $element['#autocomplete_input']['#url_value'];
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';
    $extra = '<input' . drupal_attributes($attributes) . ' />';
    $prefix = '<div class="uk-form-icon uk-width-1-1">';
    $prefix .= '<i class="uk-icon-circle-o-notch"></i>';
    $suffix = '</div>';
  }

  // Check for errors and set correct error class.
  if (form_get_error($element)) {
    $element['#attributes']['class'][] = 'uk-form-danger';
  }

  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  return $prefix . $output . $extra . $suffix;
}
