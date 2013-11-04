<?php

/**
 * @file
 * Field handler to select items.
 */
class commerce_delivery_handler_field_delivery_items extends views_handler_field {
  function query() {
    $this->ensure_my_table();
  }

  function render($values) {
    $items = array();

    $items_data = commerce_delivery_get_items($values->delivery_id);

    if ($items_data) {
      foreach ($items_data as $delivery_item) {
        if ($delivery_item->qty) {
          $line_item = commerce_line_item_load($delivery_item->line_item_id);
          $items[] = $delivery_item->qty . '/' . round($line_item->quantity) . ' x ' . $line_item->line_item_label;
        }
      }
    }

    return $items ? implode('<br/>', $items) : t('Empty');
  }
}
