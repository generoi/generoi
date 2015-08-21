<?php

$plugin = array(
  'title' => t('Foundation Top Bar'),
  'description' => t('Style the content as a foundation top bar. This style should be set both for the region and the panes.'),

  'render region' => 'generoi_foundation_topbar_style_render_region',
  'settings form' => 'generoi_foundation_topbar_style_region_settings_form',

  'render pane' => 'generoi_foundation_topbar_style_render_pane',
  'pane settings form' => 'generoi_foundation_topbar_style_pane_settings_form'
);

/**
 * Form callback; Customize topbar region.
 */
function generoi_foundation_topbar_style_region_settings_form($style_settings, $display, $pid, $type, $form_state) {
  $form['contain_to_grid'] = array(
    '#type' => 'checkbox',
    '#title' => t('Contain to grid'),
    '#default_value' => (isset($style_settings['contain_to_grid'])) ? $style_settings['contain_to_grid'] : FALSE,
  );
  $form['fixed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Fix top top'),
    '#default_value' => (isset($style_settings['fixed'])) ? $style_settings['fixed'] : FALSE,
  );
  $form['is_hover'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display on mouseover instead of on click.'),
    '#default_value' => (isset($style_settings['is_hover'])) ? $style_settings['is_hover'] : TRUE,
  );
  $form['sticky'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Sticky on screen sizes'),
    '#options' => array(
      'small' => 'Small screen',
      'medium' => 'Medium screen',
      'large' => 'Large screen',
      'xlarge' => 'X-Large screen',
      'xxlarge' => 'XX-Large screen',
    ),
    '#default_value' => (isset($style_settings['sticky'])) ? $style_settings['sticky'] : '',
  );
  return $form;
}

/**
 * Form callback; Customize topbar pane sections.
 */
function generoi_foundation_topbar_style_pane_settings_form($style_settings, $display, $pid, $type, $form_state) {
  $form['alignment'] = array(
    '#type' => 'select',
    '#title' => t('Alignment'),
    '#options' => array(
      'left' => 'Left',
      'right' => 'Right',
    ),
    '#default_value' => (isset($style_settings['alignment'])) ? $style_settings['alignment'] : 'left',
  );
  $form['has_form'] = array(
    '#type' => 'checkbox',
    '#title' => t('Contains a form'),
    '#default_value' => (isset($style_settings['has_form'])) ? $style_settings['has_form'] : FALSE,
  );
  return $form;
}

/**
 * Output the content as a foundation top bar.
 */
function theme_generoi_foundation_topbar_style_render_region($variables) {
  $options = array();
  $classes = array();
  $settings = $variables['settings'];

  if (empty($settings['is_hover'])) {
    $options[] = 'is_hover:false';
  }
  if ($sticky = array_filter($settings['sticky']) && !empty($sticky)) {
    $options[] = 'sticky_on:[' . implode(',', $sticky) . ']';
  }

  if (!empty($settings['fixed'])) {
    $classes[] = 'fixed';
  }
  if (!empty($settings['contain_to_grid'])) {
    $classes[] = 'contain-to-grid';
  }

  $attributes = array(
    'data-options' => implode(', ', $options),
    'data-topbar' => TRUE,
    'class' => array('top-bar'),
  );

  $content = '<div ' . drupal_attributes($attributes) . '>' . implode($variables['panes']) . '</div>';
  return '<div class="' . implode(' ', $classes) . '">'. $content . '</div>';
}

function theme_generoi_foundation_topbar_style_render_pane($variables) {
  $settings = $variables['settings'];
  $classes = array('top-bar-section');

  if ($settings['alignment'] == 'right') {
    $classes[] = 'right';
  }
  if (!empty($settings['has_form'])) {
    $classes[] = 'has-form';
  }
  return '<div class="' . implode(' ', $classes) . '">' . render($variables['content']->content) . '</div>';
}
