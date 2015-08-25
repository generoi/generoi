<?php

/**
 * Implements hook_panels_layouts()
 */
function generoi_generoi_2col_stacked_panels_layouts() {
  $items['generoi_2col_stacked'] = array(
    'title' => t('Two columns stacked'),
    'category' => t('Two Columns'),
    'icon' => 'generoi_2col_stacked.png',
    'theme' => 'generoi_2col_stacked',
    'admin css' => '../generoi_panels_admin.css',
    'regions' => array(
      'top' => t('Top'),
      'left' => t('Left'),
      'right' => t('Right'),
      'bottom' => t('Bottom'),
    ),
  );
  return $items;
}
