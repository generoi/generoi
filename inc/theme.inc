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

/**
 * Overrides theme_field().
 *
 * Add back core theme_field(), zurb foundation removes too much.
 */
function generoi_field($variables) {
  $output = '';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<div class="field-label"' . $variables['title_attributes'] . '>' . $variables['label'] . ':&nbsp;</div>';
  }

  // Render the items.
  $output .= '<div class="field-items"' . $variables['content_attributes'] . '>';
  foreach ($variables['items'] as $delta => $item) {
    $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
    $output .= '<div class="' . $classes . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</div>';
  }
  $output .= '</div>';

  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . '"' . $variables['attributes'] . '>' . $output . '</div>';

  return $output;
}

/**
 * Overrides theme_links().
 *
 * Set a foudnation has-dropdown class for menu_minipanel links.
 *
 * @see generoi_preprocess_link().
 * @see generoi_theme_registry_alter().
 * @see generoi_preprocess_menu_minipanel().
 */
function generoi_links($variables) {
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $heading = $variables['heading'];
  global $language_url;
  $output = '';

  if (count($links) > 0) {

    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,

          // Set the default level of the heading.
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    $output .= '<ul' . drupal_attributes($attributes) . '>';

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = array($key);

      // Add first, last and active classes to the list of links to help out themers.
      if ($i == 1) {
        $class[] = 'first';
      }
      if ($i == $num_links) {
        $class[] = 'last';
      }
      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page())) && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $class[] = 'active';
      }
      $li_attributes = array('class' => $class);

      // Add a has-dropdown for menu minipanels.
      if (!empty($link['menu_minipanels_hover'])) {
        $li_attributes['class'][] = 'has-dropdown';
        $li_attributes['class'][] = 'menu-minipanel';
      }
      $output .= '<li' . drupal_attributes($li_attributes) . '>';

      if (isset($link['href'])) {
        // Pass in $link as $options, they share the same keys.
        $output .= module_exists('menu_minipanels') ? menu_minipanels_theme_link($link) : theme_link($link);
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }

      $i++;
      $output .= "</li>\n";
    }

    $output .= '</ul>';
  }

  return $output;
}
