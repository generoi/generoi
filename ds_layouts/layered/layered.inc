<?php

function ds_layered() {
  return array(
    'label' => t('Layered'),
    'css' => TRUE,
    'regions' => array(
      'header' => t('Header'),
      'background' => t('Background'),
      'foreground' => t('Foreground'),
      'footer' => t('Footer'),
    ),
  );
}
