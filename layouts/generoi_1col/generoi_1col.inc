<?php

/**
 * Implements hook_panels_layouts().
 */
function generoi_generoi_1col_panels_layouts() {
  $items['generoi_1col'] = array(
    'title' => t('Generoi: 1 column row'),
    'category' => t('Generoi'),
    'icon' => 'generoi_1col.png',
    'theme' => 'generoi_1col',
    'regions' => array('middle' => t('Main column')),
  );
  return $items;
}
