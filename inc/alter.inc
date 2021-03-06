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

/**
 * Implements hook_css_alter().
 */
function generoi_css_alter(&$css) {
  $exclude = array(
    'sites/all/themes/zurb-foundation/css/normalize.css' => FALSE,
    'sites/all/themes/zurb-foundation/css/foundation.min.css' => FALSE,
    'sites/all/modules/contrib/date/date_popup/themes/datepicker.1.7.css' => FALSE,
    'sites/all/modules/contrib/date/date_api/date.css' => FALSE,
    'sites/all/modules/contrib/picture/picture_wysiwyg.css' => FALSE,
    'modules/user/user.css' => FALSE,
    'modules/node/node.css' => FALSE,
    'sites/all/modules/contrib/logintoboggan/logintoboggan.css' => FALSE,
    'sites/all/modules/contrib/ckeditor/ckeditor.css' => FALSE,
    // Fivestar requests a bunch of images we do not need.
    'sites/all/modules/contrib/fivestar/css/fivestar.css' => FALSE,
    'sites/all/modules/contrib/viewfield/viewfield.css' => FALSE, // request fails, file does not exist.
    'modules/system/system.messages.css' => FALSE, // We use foundation
    'modules/system/system.base.css' => FALSE, // Dont load all those images
    'modules/system/system.theme.css' => FALSE, // Dont load all those images
    // Zurb removes system.menus.css
    'modules/filter/filter.css' => FALSE, // Dont load all those images
  );
  $css = array_diff_key($css, $exclude);
}

/**
 * Implements hook_js_alter().
 */
function generoi_js_alter(&$javascript) {
  $exclude = array(
    'misc/textarea.js' => FALSE,
    'misc/tableheader.js' => FALSE,
    'misc/tabledrag.js' => FALSE,
    'sites/all/modules/contrib/admin_menu/admin_devel/admin_devel.js' => FALSE,
    // Included in foundation.js
    'sites/all/modules/contrib/picture/picturefill/matchmedia.js' => FALSE,
  );
  $javascript = array_diff_key($javascript, $exclude);
}
