<?php

/**
 * Theme callback: display prices in a table.
 */
function generoi_commerce_price_savings_formatter_formatter($vars) {
  // Build an array of table rows based on the prices passed in.
  $rows = array();

  // exit if no prices
  if (empty($vars['prices'])) {
    return '';
  }

  // store prices count
  $prices_count = count($vars['prices']);

  // extract price direction
  $price_direction = !empty($vars['price_direction']) ? $vars['price_direction'] : 'unchanged';
  // Change the label of list price.
  $vars['prices']['list']['#price_label'] = t('Retail');

  if (isset($vars['prices']['savings'])) {
    $price_element = $vars['prices']['savings'];
    unset($vars['prices']['savings']);
    if (!empty($price_element['#price_label'])) {
      $label = t('@label ', array('@label' => $price_element['#price_label']));
    }
    else {
      $label = '';
    }
    $savings = '<div class="commerce-price-savings-formatter-savings">' . $label . drupal_render($price_element) . '</div>';
  }
  else {
    $savings = '';
  }


  // build rows
  foreach ($vars['prices'] as $key => $price_element) {
    $row_data = array();

    // add label
    if (isset($price_element['#price_label'])) {
      if (!empty($price_element['#price_label'])) {
        $label = t('@label:', array('@label' => $price_element['#price_label']));
      }
      else {
        $label = '';
      }

      $row_data[] = array('data' => $label, 'class' => array('price-label'));
    }

    // add price
    $row_data[] = array('data' => drupal_render($price_element), 'class' => array('price-amount'));


    $rows[] = array(
      'data' => $row_data,
      'class' => array('commerce-price-savings-formatter-' . $key),
    );
  }

  $price_table = theme('table', array('rows' => $rows,
    'attributes' => array(
      'class' => array(
        'commerce-price-savings-formatter-prices',
        'commerce-price-savings-formatter-prices-count-' . $prices_count,
        'commerce-price-savings-formatter-prices-' . $price_direction,
      ),
    ),
  ));

  return '<div class="commerce-price-savings-formatter-wrapper">' . $price_table . $savings . '</div>';
}

/**
 * Theme callback: display prices as a list.
 */
function generoi_commerce_price_savings_formatter_inline($vars) {
  // Build an array of table rows based on the prices passed in.
  $rows = array();

  // exit if no prices
  if (empty($vars['prices'])) {
    return '';
  }

  // store prices count
  $prices_count = count($vars['prices']);

  // extract price direction
  $price_direction = !empty($vars['price_direction']) ? $vars['price_direction'] : 'unchanged';

  // build rows individually
  $price_row = array();
  $label_row = array();
  foreach ($vars['prices'] as $key => $price_element) {
    $row_data = array();

    // add label
    if (isset($price_element['#price_label'])) {
      if (!empty($price_element['#price_label'])) {
        $label = t('@label', array('@label' => $price_element['#price_label']));
      }
      else {
        $label = '';
      }

      $label_row[$key] = array('data' => '<span class="price-label">' . $label . '</span>', 'class' => array('commerce-price-savings-formatter-' . $key));
    }

    // add price
    $price = drupal_render($price_element);
    $price_row[$key] = array('data' => '<span class="price-amount">' . $price . '</span>', 'class' => array('commerce-price-savings-formatter-' . $key), 'title' => $price);
  }

  // fill out label row
  if (!empty($label_row) && count($label_row) != count($price_row)) {
    foreach ($price_row as $key => $price_cell) {
      if (!isset($label_row[$key])) {
        $label_row[$key] = '';
      }
    }
  }

  // combine rows
  $rows = array(
    array('data' => $price_row, 'class' => array('commerce-price-savings-formatter-price-row')),
    array('data' => $label_row, 'class' => array('commerce-price-savings-formatter-label-row')),
  );

  return theme('table', array('rows' => $rows,
    'attributes' => array(
      'class' => array(
        'inline',
        'commerce-price-savings-formatter-prices',
        'commerce-price-savings-formatter-prices-inline',
        'commerce-price-savings-formatter-prices-count-' . $prices_count,
        'commerce-price-savings-formatter-prices-' . $price_direction,
      ),
    ),
  ));
}
