<?php

/**
 * Implements hook_form_FORM_ID_alter().
 */
function generoi_form_commerce_cart_add_to_cart_form_alter(&$form, $form_state) {
  $form['quantity']['#title'] = t('Quantity');
  $form['submit']['#attributes']['class'][] = 'add-to-cart';
}
