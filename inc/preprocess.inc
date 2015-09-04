<?php

/**
 * Implements template_preprocess_html().
 */
function generoi_preprocess_html(&$variables) {
  // Add debugging helpers when the debug parameter is set.
  if (isset($_GET['debug']) || isset($_GET['DEBUG'])) {
    drupal_add_js('window.DEBUG = true;', 'inline');
    if (strpos($_GLOBAL['base_url'], '.dev') !== FALSE) {
      drupal_add_js($_GLOBALS['base_url'] . ':9090/target/target-script-min.js#anonymous');
    }
  }
  if (isset($_GET['firebug'])) {
    drupal_add_js('https://getfirebug.com/releases/lite/1.3/firebug-lite.js');
  }

  // Add shims and libraries.
  $condition = array('IE' => 'lt IE 9', '!IE' => FALSE);
  $options = array('every_page' => TRUE);

  $variables['conditional_scripts_array'][] = array(
    'file' =>  libraries_get_path('es5-shim') . '/es5-shim.js',
    'condition' => $condition,
  );
  $variables['conditional_scripts_array'][] = array(
    'file' =>  libraries_get_path('console-polyfill') . '/index.js',
    'condition' => $condition,
  );

  drupal_add_js(libraries_get_path('Array.from') . '/array-from.js', $options);
  drupal_add_js(libraries_get_path('jquery-touchswipe') . '/jquery.touchSwipe.min.js', $options);
  drupal_add_js(libraries_get_path('fastclick') . '/lib/fastclick.js', $options);
}

/**
 * Implements template_preprocess_page().
 */
function generoi_preprocess_page(&$variables) {
  // Remove tabs as contextual links are the preferred way at Genero.
  if (isset($variables['tabs'])) {
    unset($variables['tabs']);
  }
}

/**
 * Implements template_preprocess_region().
 */
function generoi_preprocess_region(&$variables) {
}

/**
 * Implements template_preprocess_taxonomy_term().
 */
function generoi_preprocess_taxonomy_term(&$variables) {
  // Add a layout class for the view-mode
  $view_mode = !empty($variables['view_mode']) ? $variables['view_mode'] : 'default';
  $variables['classes_array'][] = 'l-vm-' . $view_mode;
}

/**
 * Implements template_preprocess_node
 */
function generoi_preprocess_node(&$variables) {
  // Add a layout class for the view-mode
  $view_mode = !empty($variables['view_mode']) ? $variables['view_mode'] : 'default';
  $variables['classes_array'][] = 'l-vm-' . $view_mode;

  if ($variables['view_mode'] == 'full' && node_is_page($variables['node'])) {
    // Add a class to full page nodes
    $variables['classes_array'][] = 'node-full';
  }
  $variables['attributes_array']['data-id'] = $variables['nid'];
}

/**
 * Implements template_preprocess_field().
 */
function generoi_preprocess_field(&$variables) {
  if (!empty($variables['element']['#formatter'])) {
    switch ($variables['element']['#formatter']) {
      // Smart trim format removes the paragraph wrapper.
      case 'smart_trim_format':
        foreach ($variables['items'] as $idx => &$item) {
          $item['#markup'] = '<p>' . $item['#markup'] . '</p>';
        }
        break;
    }
  }
  // Convert newlines to <br> and wrap in a paragraph for plain text full text
  // fields.
  switch ($variables['element']['#field_type']) {
    case 'text_long':
    case 'text_with_summary':
      $field_name = $variables['element']['#field_name'];
      $language = $variables['element']['#language'];
      $entity = $variables['element']['#object'];
      foreach ($variables['items'] as $idx => &$item) {
        if (is_null($entity->{$field_name}[$language][$idx]['format'])) {
          $item['#markup'] = '<p>' . nl2br($item['#markup']) . '</p>';
        }
      }
      break;
  }
}

/**
 * Implements template_preprocess().
 */
function generoi_preprocess(&$variables, $hook) {
  switch ($hook) {
    case 'node':
    case 'taxonomy_term':
      // If the entity has chosen to display the DS preprocessed field,
      // region_content_field, load all blocks from the content_field region into
      // that field.
      if (!empty($variables['preprocess_fields']) && in_array('region_content_field', $variables['preprocess_fields'])) {
        $variables['region_content_field'] = array();
        if ($blocks = block_get_blocks_by_region('content_field')) {
          $variables['region_content_field'] = $blocks;
        }
        if (module_exists('context')) {
          $reaction = context_get_plugin('reaction', 'block');
          if ($context_blocks = $reaction->block_get_blocks_by_region('content_field')) {
            $variables['region_content_field'] = array_merge($variables['region_content_field'], $context_blocks);
            // @TODO proper sort
            // uasort($variables['region_content_field'], array('context_reaction_block', 'block_sort'));
          }
        }
        $variables['region_content_field'] = drupal_render($variables['region_content_field']);
      }
      break;
  }
}

/**
 * Implements template_preprocess_search_result().
 */
function generoi_preprocess_search_result(&$variables) {
}

/**
 * Implements template_preprocess_block()
 */
function generoi_preprocess_block(&$variables) {
  // Add `class` variable defined through blocktheme as real classes.
  if (isset($variables['blocktheme_vars']['class'])) {
    $blocktheme_classes = explode(' ', $variables['blocktheme_vars']['class']);
    $variables['classes_array'] = array_merge($variables['classes_array'], $blocktheme_classes);
  }

  switch ($variables['block']->module) {
    case 'bean':
      // Add a layout class for the view-mode
      if (!empty($variables['elements']['bean'])) {
        foreach (element_children($variables['elements']['bean']) as $key) {
          $element = $variables['elements']['bean'][$key];
          $view_mode = !empty($element['#view_mode']) ? $element['#view_mode'] : 'default';
          $variables['classes_array'][] = 'l-vm-' . $view_mode;
        }
      }
      break;
  }
}

/**
 * Implements template_preprocess_panels_pane().
 */
function generoi_preprocess_panels_pane(&$variables) {
  switch ($variables['pane']->type) {
    case 'menu':
      break;
  }
}

/**
 * Implements template_preprocess_link().
 *
 * Clean up menu minipanels output.
 *
 * @see generoi_link().
 * @see generoi_preprocess_menu_minipanel().
 */
function generoi_preprocess_link(&$variables) {
  if (!empty($variables['options']['minipanel'])) {
    $variables['options']['attributes']['class'] = array('menu-minipanel');
  }
}

/**
 * Implements template_preprocess_menu_minipanel().
 *
 * Add necessary foundation classes.
 *
 * @see generoi_link().
 * @see generoi_preprocess_link().
 */
function generoi_preprocess_menu_minipanel(&$variables) {
  $variables['classes_array'][] = 'dropdown';
}
