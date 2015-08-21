<?php

/**
 * Implements template_process_html().
 */
function generoi_process_html(&$variables) {
  // Add conditional scripts to the markup.
  $variables['conditional_scripts'] = '';
  foreach($variables['conditional_scripts_array'] as $script) {
    $element = array(
      '#tag' => 'script',
      '#attributes' =>  array(
        'src' => file_create_url($script['file']),
      ),
      '#browsers' => $script['condition'],
      '#pre_render' => array('drupal_pre_render_conditional_comments'),
    );
    $variables['conditional_scripts'] .= drupal_render($element);
  }
}
