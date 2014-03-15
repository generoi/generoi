<?php

/**
 * Overrides theme_links() for locale_block.
 */
function generoi_links__locale_block($variables) {
  // Set a .menu class to the <ul>-element so it can be styled like
  // menu_block:s.
  $variables['attributes']['class'][] = 'menu';
  return theme('links', $variables);
}

/**
 * Overides theme_status_messages().
 *
 * Use foundation classes for status message.
 */
function generoi_status_messages($vars) {
  $display = $vars['display'];
  $output = '';
  $content = '';
  foreach (drupal_get_messages($display) as $type => $messages) {
    foreach ($messages as $message) {
      $content .= '<div data-alert class="alert-box ' . $type . '">';
      $content .= $message;
      $content .= '<a href="#" class="close">&times;</a>';
      $content .= '</div>';
    }
  }
  if ($content) {
    $output = '<div id="messages">' . $content . '</div>';
  }

  return $output;
}

/**
 * Implements theme_context_bean_child().
 *
 * Dont render the title for the child beans, leave it up that bean instead.
 */
function generoi_context_bean_child(&$variables) {
  $child_bean = entity_view('bean', array($variables['entity']), $variables['view_mode']);
  $content = '<div id="block-bean-' . $variables['entity']->delta . '" class="block block-bean ' . $variables['css_class'] . '">';
  $content .= drupal_render($child_bean);
  $content .= '</div>';
  return $content;
}
