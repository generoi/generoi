<?php

/**
 * Implements hook_html_head_alter().
 */
function generoi_html_head_alter(&$head_elements) {
  // Make canonical links absolute.
  foreach ($head_elements as $key => $element) {
    if (isset($element['#attributes']['rel']) && $element['#attributes']['rel'] == 'canonical') {
      $canonical_href = $element['#attributes']['href'];

      if ($canonical_href[0] == '/') {
        global $base_url;
        $host = parse_url($base_url, PHP_URL_HOST);
        $head_elements[$key]['#attributes']['href'] = 'http://' . $host . $canonical_href;
      }
      else {
        unset($head_elements[$key]);
      }
    }
  }
}

/**
 * Implements hook_date_select_process_alter().
 *
 * Make date selects use proper month names instead of odd abbreviations.
 * @see date_parts_element().
 */
function generoi_date_select_process_alter(&$element, $form_state, $context) {
  if (is_array($element['#default_value'])) {
    $date = date_select_input_date($element, $element['#default_value']);
  }
  elseif (!empty($element['#default_value'])) {
    $date = date_default_date($element);
  }
  $part_required = (bool) $element['#required'] && is_object($date);
  // Change the month to use full names
  if (isset($element['month'])) {
    // Keep the label
    $labels = array_values($element['month']['#options']);
    $first = array_shift($labels);
    // Use date_month_names() instead of date_month_names_abbr().
    $element['month']['#options'] = date_month_names($part_required);
    $element['month']['#options'][''] = $first;
  }

  $year = date('Y');
  // Set the years default value to the current year.
  if (isset($element['year']['#options'][$year]) && empty($element['year']['#default_value'])) {
    $element['year']['#default_value'] = $year;
  }

  foreach (array('year', 'month', 'day', 'hour', 'minute', 'second') as $select) {
    if (isset($element[$select]['#options'])) {
      // Remove the leading dash in the first option (label) of date selects.
      $element[$select]['#options'][''] = preg_replace('/^-/', '', $element[$select]['#options']['']);
      // As this element is already printed once it hits
      // hook_form_views_exposed_form_alter() add the styling class here.
      $element[$select]['#attributes']['class'][] = 'button-dropdown';
    }
  }
}
