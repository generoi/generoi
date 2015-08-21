<?php

$plugin = array(
  'title' => t('Foundation Grid'),
  'description' => t('Style the content within a foundation grid.'),

  'render region' => 'generoi_foundation_grid_style_render_region',
  'settings form' => 'generoi_foundation_grid_style_region_settings_form',

  'render pane' => 'generoi_foundation_grid_style_render_pane',
  'pane settings form' => 'generoi_foundation_grid_style_region_settings_form',
);

function _generoi_foundation_grid_sizes($prefix = '') {
  $sizes = array(
    '' => t('Unspecified'),
    "${prefix}2" => '2/12',
    "${prefix}3" => '3/12',
    "${prefix}4" => '4/12',
    "${prefix}5" => '5/12',
    "${prefix}6" => '6/12',
    "${prefix}7" => '7/12',
    "${prefix}8" => '8/12',
    "${prefix}9" => '9/12',
    "${prefix}10" => '10/12',
    "${prefix}11" => '11/12',
    "${prefix}12" => '12/12',
  );
  return $sizes;
}

/**
 * Form callback; Customize grid pane sections.
 */
function generoi_foundation_grid_style_region_settings_form($style_settings, $display, $pid, $type, $form_state) {
  $sizes = array('small', 'medium', 'large', 'xlarge', 'xxlarge');

  $form['row'] = array(
    '#type' => 'checkbox',
    '#title' => t('Set this as a grid row instead of a column'),
    '#default_value' => (isset($style_settings['row'])) ? $style_settings['row'] : FALSE,
  );

  $form['end'] = array(
    '#type' => 'checkbox',
    '#title' => t('Specify this column as the last column'),
    '#default_value' => (isset($style_settings['end'])) ? $style_settings['end'] : FALSE,
    '#states' => array(
      'visible' => array(':input[name="settings[row]"]' => array('checked' => FALSE)),
    ),
  );
  foreach($sizes as $size) {
    $key = "${size}_width";
    $form['sizes'][$size] = array(
      '#type' => 'fieldset',
      '#states' => array(
        'visible' => array(':input[name="settings[row]"]' => array('checked' => FALSE)),
      ),
    );
    $states = array(
      'visible' => array(':input[name="settings[sizes][' . $size . '][enable]"]' => array('checked' => TRUE)),
    );
    $form['sizes'][$size]['enable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable @size sizing', array('@size' => ucfirst($size))),
      '#default_value' => (isset($style_settings['sizes'][$size]['enable'])) ? $style_settings['sizes'][$size]['enable'] : FALSE,
    );
    $form['sizes'][$size]['centered'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable centering on @size screens', array('@size' => ucfirst($size))),
      '#default_value' => (isset($style_settings['sizes'][$size]['centered'])) ? $style_settings['sizes'][$size]['centered'] : FALSE,
      '#states' => $states,
    );
    $form['sizes'][$size]['uncentered'] = array(
      '#type' => 'checkbox',
      '#title' => t('Disable centering on @size screens', array('@size' => ucfirst($size))),
      '#default_value' => (isset($style_settings['sizes'][$size]['uncentered'])) ? $style_settings['sizes'][$size]['uncentered'] : FALSE,
      '#states' => $states,
    );
    foreach (array('width', 'push', 'pull', 'offset') as $action) {
      $prefix = $action == 'width' ? "${size}-" : "${size}-${action}-";
      $form['sizes'][$size][$action] = array(
        '#type' => 'select',
        '#title' => t('@size @action', array('@size' => ucfirst($size), '@action' => $action)),
        '#options' => _generoi_foundation_grid_sizes($prefix),
        '#default_value' => (isset($style_settings['sizes'][$size][$action])) ? $style_settings['sizes'][$size][$action] : '',
        '#states' => $states,
      );
    }
  }
  return $form;
}

function _generoi_foundation_grid_attributes($settings) {
  $classes = array();
  // A row has no options
  if (!empty($settings['row'])) {
    $classes[] = 'row';
  }
  // Columns can have grid specifications.
  else {
    $classes[] = 'column';

    if (!empty($settings['end'])) {
      $classes[] = 'end';
    }

    foreach(array('small', 'medium', 'large', 'xlarge', 'xxlarge') as $size) {
      if (empty($settings['sizes'][$size]['enable'])) {
        continue;
      }
      if (!empty($settings['sizes'][$size]['centered'])) {
        $classes[] = "${size}-centered";
      }
      if (!empty($settings['sizes'][$size]['uncentered'])) {
        $classes[] = "${size}-uncentered";
      }
      foreach (array('width', 'pull', 'push', 'offset') as $action) {
        if (!empty($settings['sizes'][$size][$action])) {
          $classes[] = $settings['sizes'][$size][$action];
        }
      }
    }
  }

  $attributes = array();
  if (!empty($classes)) {
    $attributes['class'] = $classes;
  }

  return $attributes;
}

/**
 * Output the content as a foundation top bar.
 */
function theme_generoi_foundation_grid_style_render_region($variables) {
  $attributes = _generoi_foundation_grid_attributes($variables['settings']);

  return '<div ' . drupal_attributes($attributes) . '>' . implode($variables['panes']) . '</div>';
}

function theme_generoi_foundation_grid_style_render_pane($variables) {
  $attributes = _generoi_foundation_grid_attributes($variables['settings']);
  $content = render($variables['content']->content);
  if (!empty($attributes)) {
    $content = '<div ' . drupal_attributes($attributes) . '>' . $content . '</div>';
  }

  return $content;
}

