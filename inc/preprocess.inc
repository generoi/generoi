<?php

/**
 * Implements template_preprocess_html().
 */
function generoi_preprocess_html(&$variables) {
  // Add debugging helpers when the debug parameter is set.
  if (isset($_GET['debug']) || isset($_GET['DEBUG'])) {
    drupal_add_js('https://getfirebug.com/releases/lite/1.3/firebug-lite.js');
    drupal_add_js('window.DEBUG = true;', 'inline');
  }
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
