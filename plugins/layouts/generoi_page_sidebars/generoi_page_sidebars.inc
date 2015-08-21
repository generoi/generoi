<?php

/**
 * Implements hook_LAYOUT_panels_layouts()
 */
function generoi_generoi_page_sidebars_panels_layouts() {
  $items['generoi_page_sidebars'] = array(
    'title' => t('Page with optional sidebars'),
    'category' => t('Page'),
    'icon' => 'generoi_page_sidebars.png',
    'theme' => 'generoi_page_sidebars',
    'admin css' => '../generoi_panels_admin.css',
    'regions' => array(
      'header' => t('Header'),
      'navigation' => t('Navigation'),
      'featured' => t('Featured'),
      'highlighted' => t('Highlighted'),
      'sidebar_first' => t('Left Sidebar'),
      'content_above' => t('Above content'),
      'content' => t('Main Content'),
      'content_below' => t('Below content'),
      'sidebar_second' => t('Right Sidebar'),
      'footer' => t('Footer'),
    ),
  );
  return $items;
}
