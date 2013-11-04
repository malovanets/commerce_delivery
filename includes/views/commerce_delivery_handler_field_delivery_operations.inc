<?php

/**
 * @file
 * Field handler to display operatons.
 */
class commerce_delivery_handler_field_delivery_operations extends views_handler_field {
  function query() {
    $this->ensure_my_table();
  }

  function render($values) {
    $links = array(
      'edit' => array(
        'title' => t('Edit'),
        'href' => 'admin/commerce/deliveries/' . $values->delivery_id . '/edit',
      ),
      'delete' => array(
        'title' => t('Delete'),
        'href' => 'admin/commerce/deliveries/' . $values->delivery_id . '/delete',
      ),
    );
    return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
  }
}
