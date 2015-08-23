<?php

/**
 * Implements hook_panels_layouts()
 */
function generoi_generoi_reset_panels_layouts() {
  $items['generoi_reset'] = array(
    'title' => t('Reset'),
    'category' => t('One Column'),
    'icon' => 'generoi_reset.png',
    'theme' => 'generoi_reset',
    'regions' => array(
      'middle' => t('Content'),
    ),
  );
  return $items;
}
