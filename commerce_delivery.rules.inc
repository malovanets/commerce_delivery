<?php
// $Id$

/**
 * @file
 * Rules integration for deliveries.
 *
 * @addtogroup rules
 * @{
 */

/**
 * Implements hook_rules_event_info().
 */
function commerce_delivery_rules_event_info() {
  $events = array();

  $events['commerce_delivery_insert'] = array(
    'label' => t('After saving a new delivery'),
    'group' => t('Commerce Delivery'),
    'variables' => commerce_delivery_rules_event_variables(t('Created delivery'), TRUE),
//    'access callback' => 'commerce_delivery_rules_access',
  );
  $events['commerce_delivery_update'] = array(
    'label' => t('After updating an existing delivery'),
    'group' => t('Commerce Delivery'),
    'variables' => commerce_delivery_rules_event_variables(t('Updated delivery'), TRUE),
//    'access callback' => 'commerce_delivery_rules_access',
  );
/*  $events['commerce_delivery_delete'] = array(
    'label' => t('After deleting a delivery'),
    'group' => t('Commerce Delivery'),
    'variables' => commerce_delivery_rules_event_variables(t('Deleted delivery')),
    'access callback' => 'commerce_delivery_rules_access',
  );
*/
  return $events;
}

/**
 * Returns a variables array for delivery events.
 *
 * @param $label
 *   The label for the primary delivery variable.
 * @param $unchanged
 *   Boolean indicating whether or not to include the unchanged order.
 * @param $skip_save
 *   Boolean indicating whether or not the primary delivery variable should skip
 *     saving after event execution.
 */
function commerce_delivery_rules_event_variables($label, $unchanged = FALSE, $skip_save = FALSE) {
  $variables = array(
    'delivery' => array(
      'type' => 'commerce_delivery',
      'label' => $label,
      'skip save' => $skip_save,
    ),
  );

  if ($unchanged) {
    $variables['delivery_unchanged'] = array(
      'type' => 'commerce_delivery',
      'label' => t('Unchanged delivery'),
      'skip save' => TRUE,
      'handler' => 'rules_events_entity_unchanged',
    );
  }

  return $variables;
}

/**
* Implements hook_rules_condition_info() 
*/
function commerce_delivery_rules_condition_info() {
  $conditions = array();

  $conditions['commerce_delivery_order_has_shippable_item'] = array(
    'label' => t('Order has shippable items'),
    'parameter' => array(
      'order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
      ),
    ),
    'group' => t('Delivery'),
  );
  $conditions['commerce_delivery_order_has_status'] = array(
    'label' => t('Order has status'),
    'parameter' => array(
      'order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
      ),
      'status' => array(
        'type' => 'list<text>',
        'label' => t('Order status'),
        'options list' => 'commerce_order_status_options_list',
        'description' => 'Select status (multiple allowed).',
        'restriction' => 'input',
      ),
    ),
    'group' => t('Delivery'),
  );
  $conditions['commerce_delivery_item_is_shippable'] = array(
    'label' => t('Line item is shippable'),
    'parameter' => array(
      'line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('Line item'),
      ),
    ),
    'group' => t('Delivery'),
  );
  $conditions['commerce_delivery_item_is_orphan'] = array(
    'label' => t('Line item is not in any delivery'),
    'parameter' => array(
      'line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('Line item'),
      ),
    ),
    'group' => t('Delivery'),
  );
  $conditions['commerce_delivery_active_delivery_exists'] = array(
    'label' => t('Order has active deliveries'),
    'parameter' => array(
      'order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
      ),
    ),
    'group' => t('Delivery'),
  );

  return $conditions;
}

/**
 * Rules condition: checks to see if the given order has shippable items
 */
function commerce_delivery_order_has_shippable_item($order) {
  $shippables = views_get_view_result('shippable_items', 'defaults', $order->order_id);
  if (count($shippables) == 0) {
    return FALSE;
  } 
  return TRUE;
}

/**
 * Rules condition: checks to see if the given order has a selected status 
 */
function commerce_delivery_order_has_status($order, $status_list) {
  if (in_array($order->status,$status_list)) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Callback function & Rules condition: 
 * checks to see if the given line item is shippable
 */
function commerce_delivery_item_is_shippable($line_item) {
  $wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
  return $wrapper->commerce_product->field_shippable->value();
}

/**
 * Rules condition: checks to see if the given item is in any delivery 
 */
function commerce_delivery_item_is_orphan($line_item) {
  // FIXME: find a way to avoid using ['und'][0]['value']
  if ($line_item->delivery_ref['und'][0]['value'] == 0) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Rules condition: checks to see if the given order has delivery with active status 
 */
function commerce_delivery_active_delivery_exists($order) {
  // getting this order deliveries.
  $deliveries = commerce_delivery_get_deliveries($order->order_id, 'active');
  if (count($deliveries) > 0) {
    return TRUE;
  }
  return FALSE;
}

/**
* Implements hook_rules_action_info() 
*/
function commerce_delivery_rules_action_info() {
  $actions = array();

  $actions['commerce_delivery_assign_delivery'] = array(
    'label' => t('Assign line item to delivery'),
    'parameter' => array(
      'line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('Line item'),
      ),
    ),
    'group' => t('Commerce Line Item'),
  );
  $actions['commerce_delivery_assign_orphans'] = array(
    'label' => t('Assign orphan line items to delivery'),
    'parameter' => array(
      'delivery' => array(
        'type' => 'commerce_delivery',
        'label' => t('Delivery'),
      ),
    ),
    'group' => t('Commerce Line Item'),
  );
  return $actions;
}

/**
 * Rules action: assign line items to order default delivery.
 */
function commerce_delivery_assign_delivery($line_item) {
  // getting this order deliveries. 
  $deliveries = commerce_delivery_get_deliveries($line_item->order_id, 'active');
  // reloading the line item or saving gives error
  $item = current(entity_load('commerce_line_item', array($line_item->line_item_id)));
  $wrapper = entity_metadata_wrapper('commerce_line_item', $item);
  // setting the deliver ref
  $wrapper->delivery_ref = current($deliveries['commerce_delivery'])->delivery_id;
  commerce_line_item_save($item);
}

/**
 * Rules action: assign orphan line items to order default delivery.
 */
function commerce_delivery_assign_orphans($delivery) {
  // getting shippable items from this order
  $items = views_get_view_result('shippable_items', 'defaults', $delivery->order_id);
  foreach($items as $item) {
    $line_item = current(entity_load('commerce_line_item', array($item->line_item_id)));
    $wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
    // checking if it's orphan
    if ($wrapper->delivery_ref->value() == array('und' => array(0 => array('value' => 0)))) { 
      $wrapper->delivery_ref = $delivery->delivery_id;
      commerce_line_item_save($line_item);
    }
  }
}

/**
* Implements hook_default_rules_configuration().
*/
function commerce_delivery_default_rules_configuration() {
  $rule = rules_reaction_rule();
  $rule->label = 'Add delivery';
  $rule->event('commerce_order_insert')
       ->event('commerce_order_update')
       ->condition(rules_condition('commerce_delivery_active_delivery_exists', array('order:select' => 'order'))->negate())
       ->condition('commerce_delivery_order_has_shippable_item', array('order:select' => 'order'))
       ->condition('commerce_delivery_order_has_status', array('order:select' => 'order','status' => array('pending'=>'pending', 'processing'=>'processing')))
       ->action('entity_create', array('type' => 'commerce_delivery', 'param_order_id:select' => 'order:order_id', 'param_status' => '0'));
  $configs['rules_add_delivery'] = $rule;
  
  $rule = rules_reaction_rule();
  $rule->label = 'Assign new line item to delivery';
  $rule->event('commerce_line_item_insert')
       ->condition('commerce_delivery_item_is_shippable', array('line_item:select' => 'line_item'))
       ->condition('entity_exists', array('type' => 'commerce_delivery','property' => 'order_id', 'value:select' => 'line-item:order-id'))
       ->action('commerce_delivery_assign_delivery', array('line_item:select' => 'line_item', 'delivery_status' => array('0' , '1')));
  $configs['rules_assign_line_item_to_delivery'] = $rule;

  $rule = rules_reaction_rule();
  $rule->label = 'Assign orphan item to new delivery';
  $rule->event('commerce_delivery_insert')
       ->action('commerce_delivery_assign_orphans', array('delivery:select' => 'delivery',));
  $configs['rules_assign_orphan_to_new_delivery'] = $rule;
  
/* 
** not needed any more. leaving it as example of adding a rules component by code
**
  $rule = rule(array('line_item' => array('label' => 'line_item', 'type' => 'commerce_line_item',)));
  $rule->label = 'Item to delivery';
  $rule->condition('commerce_delivery_item_is_shippable', array('line_item:select' => 'line_item'))
       ->condition('commerce_delivery_item_is_orphan', array('line_item:select' => 'line_item'))
       ->action('commerce_delivery_assign_orphans', array('line_item:select' => 'line_item',));
  $configs['rules_item_to_delivery'] = $rule;
 */ 
  return $configs;
}
