<?php

/**
 * Overrides theme_facetapi_count().
 */
function generoi_facetapi_count($variables) {
  return '<span class="count">(' . (int) $variables['count'] . ')</span>';
}

/**
 * Overrides theme_facetapi_link_inactive().
 */
function generoi_facetapi_link_inactive($variables) {
  // Builds accessible markup.
  // @see http://drupal.org/node/1316580
  $accessible_vars = array(
    'text' => $variables['text'],
    'active' => FALSE,
  );
  $accessible_markup = theme('facetapi_accessible_markup', $accessible_vars);

  // Sanitizes the link text if necessary.
  $sanitize = empty($variables['options']['html']);
  $variables['text'] = ($sanitize) ? check_plain($variables['text']) : $variables['text'];

  // Adds count to link if one was passed.
  if (isset($variables['count'])) {
    $variables['text'] .= ' ' . theme('facetapi_count', $variables);
  }

  // Resets link text, sets to options to HTML since we already sanitized the
  // link text and are providing additional markup for accessibility.
  $variables['text'] .= $accessible_markup;
  $variables['options']['html'] = TRUE;
  return theme_link($variables);
}

/**
 * Overrides theme_facetapi_link_active().
 */
function generoi_facetapi_link_active($variables) {

  // Sanitizes the link text if necessary.
  $sanitize = empty($variables['options']['html']);
  $link_text = ($sanitize) ? check_plain($variables['text']) : $variables['text'];

  // Theme function variables fro accessible markup.
  // @see http://drupal.org/node/1316580
  $accessible_vars = array(
    'text' => $variables['text'],
    'active' => TRUE,
  );

  // Builds link, passes through t() which gives us the ability to change the
  // position of the widget on a per-language basis.
  $replacements = array(
    '!facetapi_deactivate_widget' => theme('facetapi_deactivate_widget', $variables),
    '!facetapi_accessible_markup' => theme('facetapi_accessible_markup', $accessible_vars),
    '!facetapi_markup' => $link_text,
  );
  $variables['text'] = t('!facetapi_deactivate_widget !facetapi_accessible_markup !facetapi_markup', $replacements);
  $variables['options']['html'] = TRUE;
  $variables['options']['attributes']['title'] = t('Remove @filter filter', array('@filter' => $link_text));
  return theme_link($variables);
}

/**
 * Overrides theme_facetapi_deactivate_widget().
 */
function generoi_facetapi_deactivate_widget($variables) {
  return '<span class="remove">&times;</span>';
}

/**
 * Overrides theme_search_api_fivestar_facetapi_link_inactive().
 */
function generoi_search_api_fivestar_facetapi_link_inactive($variables) {
  // Builds accessible markup.
  // @see http://drupal.org/node/1316580
  $accessible_vars = array(
    'text' => $variables['text'],
    'active' => FALSE,
  );
  $accessible_markup = theme('facetapi_accessible_markup', $accessible_vars);

  $variables['text'] = theme('fivestar_static', array(
    'rating' => $variables['rating'] * 20,
    'stars' => $variables['stars'], // @todo should be set on the facet instead as a variable.
    'tag' => 'vote', // @todo should be exposed not only here but for indexing as well.
    'widget' => $variables['widget'],
  ));
  $variables['text'] = '<span class="prefix">' . check_plain($variables['prefix']) . '</span>'
    . $variables['text']
    . '<span class="suffix">' . check_plain($variables['suffix']) . '</span>';

  // Adds count to link if one was passed.
  if (isset($variables['count'])) {
    $variables['text'] .= ' ' . theme('facetapi_count', $variables);
  }

  // Resets link text, sets to options to HTML since we already sanitized the
  // link text and are providing additional markup for accessibility.
  $variables['text'] .= $accessible_markup;
  $variables['options']['html'] = TRUE;

  return theme_link($variables);
}

/**
 * Overrides theme_search_api_fivestar_facetapi_link_active().
 */
function generoi_search_api_fivestar_facetapi_link_active($variables) {
  // Theme function variables fro accessible markup.
  // @see http://drupal.org/node/1316580
  $accessible_vars = array(
    'text' => $variables['text'],
    'active' => TRUE,
  );
  $link_text = theme('fivestar_static', array(
    'rating' => $variables['rating'] * 20,
    'stars' => $variables['stars'], // @todo should be set on the facet instead as a variable.
    'tag' => 'vote', // @todo should be exposed not only here but for indexing as well.
    'widget' => $variables['widget'],
  ));

  $link_text = '<span class="prefix">' . check_plain($variables['prefix']) . '</span>'
    . $link_text
    . '<span class="suffix">' . check_plain($variables['suffix']) . '</span>';

  // Builds link, passes through t() which gives us the ability to change the
  // position of the widget on a per-language basis.
  $replacements = array(
    '!facetapi_deactivate_widget' => theme('facetapi_deactivate_widget', $variables),
    '!facetapi_accessible_markup' => theme('facetapi_accessible_markup', $accessible_vars),
    '!facetapi_markup' => $link_text,
  );
  $variables['text'] = t('!facetapi_deactivate_widget !facetapi_accessible_markup !facetapi_markup', $replacements);
  $variables['options']['html'] = TRUE;
  $variables['options']['attributes']['title'] = t('Remove @filter/5 filter', array('@filter' => $variables['rating']));

  return theme_link($variables);
}
