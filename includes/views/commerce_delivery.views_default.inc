<?php

/**
 * @file
 * Implements hook_views_default_views().
 */
function commerce_delivery_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'order_deliveries';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_delivery';
  $view->human_name = 'Order deliveries';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Order deliveries';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Nothing found';
  $handler->display->display_options['empty']['area']['format'] = 'commerce_order_message';
  /* Field: Bulk operations: Commerce Delivery */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'commerce_delivery';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
      'action::commerce_delivery_action_edit_status' => array(
          'selected' => 1,
          'postpone_processing' => 0,
          'skip_confirmation' => 1,
          'override_label' => 0,
          'label' => '',
      ),
      'action::commerce_delivery_action_delete' => array(
          'selected' => 1,
          'postpone_processing' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
      ),
      'action::views_bulk_operations_delete_item' => array(
          'selected' => 0,
          'postpone_processing' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
      ),
      'action::views_bulk_operations_script_action' => array(
          'selected' => 0,
          'postpone_processing' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
      ),
      'action::views_bulk_operations_modify_action' => array(
          'selected' => 0,
          'postpone_processing' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
          'settings' => array(
              'show_all_tokens' => 1,
              'display_values' => array(
                  '_all_' => '_all_',
              ),
          ),
      ),
      'action::views_bulk_operations_argument_selector_action' => array(
          'selected' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
          'settings' => array(
              'url' => '',
          ),
      ),
      'action::system_send_email_action' => array(
          'selected' => 0,
          'postpone_processing' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
      ),
  );
  /* Field: Commerce Delivery: Delivery id */
  $handler->display->display_options['fields']['delivery_id']['id'] = 'delivery_id';
  $handler->display->display_options['fields']['delivery_id']['table'] = 'commerce_delivery';
  $handler->display->display_options['fields']['delivery_id']['field'] = 'delivery_id';
  $handler->display->display_options['fields']['delivery_id']['element_label_colon'] = FALSE;
  /* Field: Commerce Delivery: Delivery items */
  $handler->display->display_options['fields']['items']['id'] = 'items';
  $handler->display->display_options['fields']['items']['table'] = 'commerce_delivery';
  $handler->display->display_options['fields']['items']['field'] = 'items';
  $handler->display->display_options['fields']['items']['label'] = 'Items';
  $handler->display->display_options['fields']['items']['element_label_colon'] = FALSE;
  /* Field: Commerce Delivery: Delivery status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'commerce_delivery';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  /* Field: Commerce Delivery: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_delivery';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Commerce Delivery: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'commerce_delivery';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Updated';
  $handler->display->display_options['fields']['changed']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* Field: Commerce Delivery: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'commerce_delivery';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['label'] = '';
  $handler->display->display_options['fields']['operations']['element_label_colon'] = FALSE;
  /* Contextual filter: Commerce Delivery: Order ID */
  $handler->display->display_options['arguments']['order_id']['id'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['table'] = 'commerce_delivery';
  $handler->display->display_options['arguments']['order_id']['field'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['order_id']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['order_id']['default_argument_options']['index'] = '3';
  $handler->display->display_options['arguments']['order_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['order_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['order_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Commerce Delivery: Delivery status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'commerce_delivery';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Filter by status';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
      2 => '2',
      1 => 0,
      3 => 0,
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  $views[$view->name] = $view;

  return $views;
}

