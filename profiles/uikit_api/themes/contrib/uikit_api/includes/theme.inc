<?php

/**
 * @file
 * The UIkit theme system, which controls the output of the UIkit API theme.
 *
 * The theme system allows for nearly all output of the Drupal system to be
 * customized by UIkit themes.
 *
 * @ingroup uikit_themeable
 */

/**
 * Implements theme_container().
 */
function uikit_api_container($variables) {
  $element = $variables['element'];
  // Ensure #attributes is set.
  $element += array('#attributes' => array());

  // Special handling for form elements.
  if (isset($element['#array_parents'])) {
    // Assign an html ID.
    if (!isset($element['#attributes']['id'])) {
      $element['#attributes']['id'] = $element['#id'];
    }

    // Add the 'form-wrapper' class.
    $element['#attributes']['class'][] = 'form-wrapper';
  }

  return '<div' . drupal_attributes($element['#attributes']) . '>' . $element['#children'] . '</div>';
}

/**
 * Implements theme_fieldset().
 */
function uikit_api_fieldset__format($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id'));
  _form_set_class($element, array('form-wrapper'));
  $output = '<div' . drupal_attributes($element['#attributes']) . '>';

  if (!empty($element['#title'])) {
    $output .= '<legend class="fieldset-legend">' . $element['#title'] . '</legend>';
  }

  if (!empty($element['#description'])) {
    $output .= '<p class="uk-text-small uk-text-muted uk-margin-small-top">' . $element['#description'] . '</p>';
  }

  $output .= $element['#children'];

  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }

  $output .= '</div>';

  return $output;
}

/**
 * Implements theme_filter_tips().
 */
function uikit_api_filter_tips($variables) {
  $tips = $variables['tips'];
  $long = $variables['long'];
  $output = '';

  $multiple = count($tips) > 1;
  if ($multiple) {
    $output = '<h3>' . t('Text Formats') . '</h3>';
  }

  if (count($tips)) {
    if ($multiple) {
      $output .= '<div class="compose-tips">';
    }

    foreach ($tips as $name => $tiplist) {
      if ($multiple) {
        $output .= '<div class="filter-type filter-' . drupal_html_class($name) . '">';
        $output .= '<h4>' . check_plain($name) . '</h4>';
      }

      if (count($tiplist) > 0) {
        $output .= '<ul class="tips uk-list uk-list-divider uk-margin-top">';
        foreach ($tiplist as $tip) {
          $output .= '<li' . ($long ? ' id="filter-' . str_replace("/", "-", $tip['id']) . '">' : '>') . $tip['tip'] . '</li>';
        }
        $output .= '</ul>';
      }

      if ($multiple) {
        $output .= '</div><hr class="uk-article-divider">';
      }
    }

    if ($multiple) {
      $output .= '</div>';
    }
  }

  return $output;
}

/**
 * Implements theme_item_list().
 */
function uikit_api_item_list($variables) {
  $items = $variables['items'];
  $title = $variables['title'];
  $type = $variables['type'];
  $attributes = $variables['attributes'];

  // Only output the list title, if there are any list items.
  // Check to see whether the block title exists before adding a header.
  // Empty headers are not semantic and present accessibility challenges.
  $output = '';
  if (isset($title) && $title !== '') {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    $i = 0;

    foreach ($items as $item) {
      $attributes = array();
      $children = array();
      $data = '';
      $i++;

      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }

      if (count($children) > 0) {
        // Render nested list.
        $data .= theme_item_list(array(
          'items' => $children,
          'title' => NULL,
          'type' => $type,
          'attributes' => $attributes,
        ));
      }

      if ($i == 1) {
        $attributes['class'][] = 'first';
      }

      if ($i == $num_items) {
        $attributes['class'][] = 'last';
      }

      $xmlDoc = new DOMDocument();
      $xmlDoc->loadHTML($data);
      $search_node = $xmlDoc->getElementsByTagName( "a" );

      foreach ($search_node as $node_item) {
        $classes = $node_item->getAttribute('class');
        preg_match('/(active)/', $classes, $matches);

        if ($matches) {
          $attributes['class'][] = 'uk-active';
        }
      }

      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }

  return $output;
}

/**
 * Implements theme_form_element().
 */
function uikit_api_form_element($variables) {
  $element = &$variables['element'];
  $name = !empty($element['#name']) ? $element['#name'] : FALSE;
  $type = !empty($element['#type']) ? $element['#type'] : FALSE;
  $prefix = isset($element['#field_prefix']) ? $element['#field_prefix'] : '';
  $suffix = isset($element['#field_suffix']) ? $element['#field_suffix'] : '';
  $checkbox = $type && $type === 'checkbox';
  $radio = $type && $type === 'radio';

  // Create an attributes array for the wrapping container.
  if (empty($element['#wrapper_attributes'])) {
    $element['#wrapper_attributes'] = array();
  }

  $wrapper_attributes = &$element['#wrapper_attributes'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add wrapper ID for 'item' type.
  if ($type && $type === 'item' && !empty($element['#markup']) && !empty($element['#id'])) {
    $wrapper_attributes['id'] = $element['#id'];
  }

  // Add necessary classes to wrapper container.
  if ($name) {
    $wrapper_attributes['class'][] = 'form-item-' . drupal_html_class($name);
  }
  if ($type) {
    $wrapper_attributes['class'][] = 'form-type-' . drupal_html_class($type);
  }
  if (!empty($element['#attributes']['disabled'])) {
    $wrapper_attributes['class'][] = 'form-disabled';
  }
  if (!empty($element['#autocomplete_path']) && drupal_valid_path($element['#autocomplete_path'])) {
    $wrapper_attributes['class'][] = 'form-autocomplete';
  }

  // TODO: Add advanced password options in theme settings.
  // Add a space before the labels of checkboxes and radios.
  if (($checkbox || $radio) && isset($element['#title'])) {
    $variables['element']['#title'] = ' ' . $element['#title'];
  }

  // Create a render array for the form element.
  $build = array(
    '#theme_wrappers' => array('container__form_element'),
    '#attributes' => $wrapper_attributes,
  );

  // Render the label for the form element.
  $build['label'] = array(
    '#markup' => theme('form_element_label', $variables),
  );

  // Increase the label weight if it should be displayed after the element.
  if ($element['#title_display'] === 'after') {
    $build['label']['#weight'] = 10;
  }

  // Checkboxes and radios render the input element inside the label. If the
  // element is neither of those, then the input element must be rendered here.
  if (!$checkbox && !$radio) {

    if ((!empty($prefix) || !empty($suffix))) {
      if (!empty($element['#field_prefix'])) {
        $prefix = '<span class="form-item-prefix">' . $prefix . '</span>';
      }
      if (!empty($element['#field_suffix'])) {
        $suffix = '<span class="form-item-suffix">' . $suffix . '</span>';
      }

      // Add a wrapping container around the elements.
      $prefix .= '<div>' . $prefix;
      $suffix .= '</div>';
    }

    // Build the form element.
    $build['element'] = array(
      '#markup' => $element['#children'],
      '#prefix' => !empty($prefix) ? $prefix : NULL,
      '#suffix' => !empty($suffix) ? $suffix : NULL,
    );
  }

  // Construct the element's description markup.
  if (!empty($element['#description'])) {
    $build['description'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'description',
          'uk-text-small',
          'uk-text-muted',
        ),
      ),
      '#weight' => 20,
      0 => array('#markup' => $element['#description']),
    );
  }

  // Print the form element build array.
  return drupal_render($build);
}

/**
 * Implements theme_tablesort_indicator().
 */
function uikit_api_tablesort_indicator($variables) {
  if ($variables['style'] == "asc") {
    //return theme('image', array('path' => 'misc/arrow-asc.png', 'width' => 13, 'height' => 13, 'alt' => t('sort ascending'), 'title' => t('sort ascending')));
    return '<i class="uk-margin-left" uk-icon="chevron-down" title="' . t('sort ascending') . '"></i>';
  }
  else {
    //return theme('image', array('path' => 'misc/arrow-desc.png', 'width' => 13, 'height' => 13, 'alt' => t('sort descending'), 'title' => t('sort descending')));
    return '<i class="uk-margin-left" uk-icon="chevron-up" title="' . t('sort descending') . '"></i>';
  }
}

/**
 * Implements theme_textfield().
 */
function uikit_api_textfield($variables) {
  $element = $variables['element'];

  element_set_attributes($element, array(
    'id',
    'name',
    'value',
    'size',
    'maxlength',
  ));

  _form_set_class($element, array(
    'form-text',
    'uk-input',
  ));

  $element['#attributes']['type'] = 'text';
  $extra = '';

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
  }

  // Check for errors and set correct error class.
  if (form_get_error($element)) {
    $element['#attributes']['class'][] = 'uk-form-danger';
  }

  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  return $output . $extra;
}

/**
 * Implements theme_textfield().
 */
function uikit_api_textfield__search($variables) {
  $element = $variables['element'];

  element_set_attributes($element, array(
    'id',
    'name',
    'value',
    'size',
    'maxlength',
  ));

  _form_set_class($element, array(
    'form-text',
    'uk-input',
  ));

  $element['#attributes']['type'] = 'text';
  $extra = '';

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
  }

  // Check for errors and set correct error class.
  if (form_get_error($element)) {
    $element['#attributes']['class'][] = 'uk-form-danger';
  }

  $output = '<div class="uk-inline">';
  $output .= '<span class="uk-form-icon uk-form-icon-flip" uk-icon="icon: search"></span>';
  $output .= '<input' . drupal_attributes($element['#attributes']) . ' />';
  $output .= '</div>';

  return $output . $extra;
}
