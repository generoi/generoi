<?php

/**
 * Implements hook_panels_layouts()
 */
function generoi_generoi_2col_panels_layouts() {
  $items['generoi_2col'] = array(
    'title' => t('Two columns'),
    'category' => t('Two Columns'),
    'icon' => 'generoi_2col.png',
    'theme' => 'generoi_2col',
    'admin css' => '../generoi_panels_admin.css',
    'regions' => array(
      'left' => t('Left'),
      'right' => t('Right')
    ),
  );
  return $items;
}
