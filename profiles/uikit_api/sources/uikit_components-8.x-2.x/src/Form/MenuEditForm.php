<?php

namespace Drupal\uikit_components\Form;

use Drupal\Core\Form\FormStateInterface;
use Drupal\menu_ui\MenuForm;
use Drupal\uikit_components\UIkitComponents;

/**
 * Base form for menu edit forms.
 */
class MenuEditForm extends MenuForm {

  /**
   * {@inheritdoc}
   */
  public function form(array $form, FormStateInterface $form_state) {
    $form = parent::form($form, $form_state);

    $t_args = [
      ':list' => UIkitComponents::getComponentURL('list'),
      ':nav' => UIkitComponents::getComponentURL('nav'),
      ':subnav' => UIkitComponents::getComponentURL('subnav'),
      ':grid' => UIkitComponents::getComponentURL('grid'),
    ];

    $description_links = [
      $this->t('<a href=":list" target="_blank">List</a>', $t_args),
      $this->t('<a href=":nav" target="_blank">Nav</a>', $t_args),
      $this->t('<a href=":subnav" target="_blank">Subnav</a>', $t_args),
    ];

    $links = [
      '#markup' => implode(', ', $description_links)
    ];

    $width_classes = UIkitComponents::getNavWidthClasses($this->entity->id()) ? UIkitComponents::getNavWidthClasses($this->entity->id()) : '';

    $form['label']['#weight'] = -10;
    $form['id']['#weight'] = -9;
    $form['description']['#weight'] = -8;

    $form['menu_style'] = [
      '#type' => 'select',
      '#title' => $this->t('UIkit menu style'),
      '#description' => $this->t('<p>Select the UIkit component to set a default style for the menu. Some options will provide additional settings. Examples: @examples</p>', ['@examples' => render($links)]),
      '#options' => [
        $this->t('List')->render() => [
          'uk-list' => $this->t('Default list'),
          'uk-list-line' => $this->t('Line list'),
          'uk-list-space' => $this->t('Spaced list'),
          'uk-list-striped' => $this->t('Striped list'),
        ],
        'uk-nav' => $this->t('Nav'),
        $this->t('Subnav')->render() => [
          'uk-subnav' => $this->t('Default subnav'),
          'uk-subnav-line' => $this->t('Subnav line'),
          'uk-subnav-pill' => $this->t('Subnav pill'),
        ],
      ],
      '#empty_value' => '',
      '#default_value' => UIkitComponents::getMenuStyle($this->entity->id()),
      '#weight' => -7,
    ];

    $form['menu_style_wrapper_widths'] = [
      '#type' => 'textfield',
      '#title' => $this->t('Menu wrapper width classes'),
      '#description' => $this->t('Enter the <a href=":grid" target="_blank">width classes</a>, separated with a space, to wrap the menu in.', $t_args),
      '#default_value' => $width_classes,
      '#weight' => -2,
    ];

    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    parent::submitForm($form, $form_state);
    UIkitComponents::setMenuStyle($this->entity->id(), $form_state->getValue('menu_style'));
    UIkitComponents::setNavWidthClasses($this->entity->id(), $form_state->getValue('menu_style_wrapper_widths'));

    // For good measure, flush all cache.
    drupal_flush_all_caches();
  }

}
