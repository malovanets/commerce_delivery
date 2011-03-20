<?php
// $Id$

class DeliveryEntityController extends DrupalDefaultEntityController {

  /**
   * Create a default delivery.
   *
   * @param $type
   *   The machine-readable type of the line item.
   * @param $order_id
   *   The ID of the order the line item belongs to (if available).
   *
   * @return
   *   A line item object with all default fields initialized.
   */
  public function create($type = 'commerce_delivery', $order_id = 0, $status = 0) {
    return (object) array(
      'delivery_id' => '',
      'order_id' => $order_id,
      'type' => $type,
      'status' => $status,
      'created' => '',
      'changed' => '',
    );
  }

  public function save($delivery) {

    $op = 'update';
    // Set the timestamp fields.
    if (empty($delivery->created)) {
      $delivery->created = REQUEST_TIME;
      $op = 'insert';
    }
    $delivery->changed = REQUEST_TIME;

    drupal_write_record('commerce_delivery', $delivery);
    field_attach_insert('commerce_delivery', $delivery);
    module_invoke_all('entity_insert', 'commerce_delivery', $delivery);
    rules_invoke_event('commerce_delivery_' . $op, $delivery);
    return $delivery;
  }
}



