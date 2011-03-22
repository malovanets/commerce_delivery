<?php
// $Id$

/**
 * @file
 * Export Drupal Commerce deliveries to Views.
 */

/**
 * Implements hook_views_data()
 */
function commerce_delivery_views_data() {
  $data = array();

  $data['commerce_delivery']['table']['group']  = t('Commerce Delivery');

  $data['commerce_delivery']['table']['base'] = array(
    'field' => 'delivery_id',
    'title' => t('Commerce Delivery'),
    'help' => t('Delivery.'),
  );
  
  // Expose the order ID.
  $data['commerce_delivery']['order_id'] = array(
    'title' => t('Order ID'),
    'help' => t('The unique internal identifier of the order.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'order_number',
      'numeric' => TRUE,
      'validate type' => 'order_id',
    ),
    'relationship' => array(
       'base' => 'commerce_order',
       'field' => 'order_id',
       'handler' => 'views_handler_relationship',
       'label' => t('Order ID'),
     ),
  );

  // Expose the delivery id.
  $data['commerce_delivery']['delivery_id'] = array(
    'title' => t('Delivery id'),
    'help' => t('The delive id.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Expose the delivery status.
  $data['commerce_delivery']['status'] = array(
    'title' => t('Delivery status'),
    'help' => t('The workflow status of the delivery.'),
    'field' => array(
      'handler' => 'commerce_delivery_handler_field_delivery_status',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'commerce_delivery_handler_filter_delivery_status',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Expose the created and changed timestamps.
  $data['commerce_delivery']['created'] = array(
    'title' => t('Created date'),
    'help' => t('The date the delivery was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['commerce_delivery']['changed'] = array(
    'title' => t('Updated date'),
    'help' => t('The date the order was last updated.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  // Expose links to operate on the delivery.
  $data['commerce_delivery']['action_links'] = array(
    'field' => array(
      'title' => t('Action links'),
      'help' => t('Provide links to perform actions on each delivery.'),
      'handler' => 'commerce_delivery_handler_delivery_action_links',
    ),
  );

  // Expose links to operate on the line item delivery.
  $data['commerce_line_item']['set_delivery'] = array(
    'field' => array(
      'title' => t('Move item to delivery'),
      'help' => t('Provide links to move each line items to a different delivery.'),
      'handler' => 'commerce_delivery_handler_line_item_set_delivery',
    ),
  );
  
  return $data;
}

/**
 * Implements hook_views_default_views().
 */
function commerce_delivery_views_default_views() {
  $views = array();
  $view = new view;
  $view->name = 'commerce_delivery';
  $view->description = 'Display a list of deliveries for the store admin.';
  $view->tag = '';
  $view->base_table = 'commerce_delivery';
  $view->human_name = 'commerce_delivery';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'delivery_id' => 'delivery_id',
    'status' => 'status',
    'order_id' => 'order_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'delivery_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'order_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<a href="/admin/commerce/deliveries/add">+ add delivery</a>';
  /* Field: Commerce Delivery: Delivery id */
  $handler->display->display_options['fields']['delivery_id']['id'] = 'delivery_id';
  $handler->display->display_options['fields']['delivery_id']['table'] = 'commerce_delivery';
  $handler->display->display_options['fields']['delivery_id']['field'] = 'delivery_id';
  $handler->display->display_options['fields']['delivery_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['delivery_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['delivery_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['delivery_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['delivery_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['delivery_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['delivery_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['delivery_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['delivery_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['delivery_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['delivery_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['delivery_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['delivery_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['delivery_id']['empty_zero'] = 0;
  /* Field: Commerce Delivery: Delivery status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'commerce_delivery';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['status']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['status']['empty_zero'] = 0;
  /* Field: Commerce Delivery: Order ID */
  $handler->display->display_options['fields']['order_id']['id'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['table'] = 'commerce_delivery';
  $handler->display->display_options['fields']['order_id']['field'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['order_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['order_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['order_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['order_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['order_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['order_id']['empty_zero'] = 0;
  /* Filter: Commerce Delivery: Delivery status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'commerce_delivery';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Delivery status';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['single'] = TRUE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'admin/commerce/deliveries/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Deliveries';
  $handler->display->display_options['tab_options']['description'] = 'Manage deliveries in the store.';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';
  $translatables['commerce_delivery'] = array(
    t('Defaults'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort By'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('<a href="/admin/commerce/deliveries/add">+ add delivery</a>'),
    t('Delivery id'),
    t('Delivery status'),
    t('Order ID'),
    t('Page'),
  );
  
  $views[$view->name] = $view;
  
  // shippable items view
  $view = new view;
  $view->name = 'shippable_items';
  $view->description = 'Select shippable items in a order';
  $view->tag = 'commerce';
  $view->base_table = 'commerce_line_item';
  $view->human_name = 'Shippable items';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Fields: Referenced product */
  $handler->display->display_options['relationships']['commerce_product_product_id']['id'] = 'commerce_product_product_id';
  $handler->display->display_options['relationships']['commerce_product_product_id']['table'] = 'field_data_commerce_product';
  $handler->display->display_options['relationships']['commerce_product_product_id']['field'] = 'commerce_product_product_id';
  $handler->display->display_options['relationships']['commerce_product_product_id']['required'] = 0;
  /* Field: Commerce Line Item: Line item ID */
  $handler->display->display_options['fields']['line_item_id']['id'] = 'line_item_id';
  $handler->display->display_options['fields']['line_item_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['line_item_id']['field'] = 'line_item_id';
  $handler->display->display_options['fields']['line_item_id']['label'] = '';
  $handler->display->display_options['fields']['line_item_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['line_item_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['line_item_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['line_item_id']['element_type'] = '0';
  $handler->display->display_options['fields']['line_item_id']['element_label_type'] = '0';
  $handler->display->display_options['fields']['line_item_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['line_item_id']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['line_item_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['line_item_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['line_item_id']['empty_zero'] = 0;
  /* Argument: Commerce Line Item: Order ID */
  $handler->display->display_options['arguments']['order_id']['id'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['arguments']['order_id']['field'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['style_plugin'] = 'default_summary';
  $handler->display->display_options['arguments']['order_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['order_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['order_id']['not'] = 0;
  /* Filter: Fields: Shippable (field_shippable) */
  $handler->display->display_options['filters']['field_shippable_value']['id'] = 'field_shippable_value';
  $handler->display->display_options['filters']['field_shippable_value']['table'] = 'field_data_field_shippable';
  $handler->display->display_options['filters']['field_shippable_value']['field'] = 'field_shippable_value';
  $handler->display->display_options['filters']['field_shippable_value']['relationship'] = 'commerce_product_product_id';
  $handler->display->display_options['filters']['field_shippable_value']['value']['value'] = '1';
  $translatables['shippable_items'] = array(
    t('Defaults'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort By'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Product'),
    t('All'),
  );
  
  $views[$view->name] = $view;
  
  $view = new view;
  $view->name = 'commerce_delivery_by_order';
  $view->description = '';
  $view->tag = 'commerce';
  $view->base_table = 'commerce_line_item';
  $view->human_name = 'Commerce delivery by order';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer orders';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = 'delivery_ref';
  $handler->display->display_options['style_options']['columns'] = array(
    'delivery_ref' => 'delivery_ref',
    'order_id' => 'order_id',
    'sku' => 'sku',
    'line_item_label' => 'line_item_label',
    'quantity' => 'quantity',
    'set_delivery' => 'set_delivery',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'delivery_ref' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'order_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'sku' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'line_item_label' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'quantity' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'set_delivery' => array(
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['order'] = 'desc';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No results for this case.';
  /* Relationship: Fields: Referenced product */
  $handler->display->display_options['relationships']['commerce_product_product_id']['id'] = 'commerce_product_product_id';
  $handler->display->display_options['relationships']['commerce_product_product_id']['table'] = 'field_data_commerce_product';
  $handler->display->display_options['relationships']['commerce_product_product_id']['field'] = 'commerce_product_product_id';
  $handler->display->display_options['relationships']['commerce_product_product_id']['required'] = 1;
  /* Field: Fields: Delivery id */
  $handler->display->display_options['fields']['delivery_ref']['id'] = 'delivery_ref';
  $handler->display->display_options['fields']['delivery_ref']['table'] = 'field_data_delivery_ref';
  $handler->display->display_options['fields']['delivery_ref']['field'] = 'delivery_ref';
  $handler->display->display_options['fields']['delivery_ref']['exclude'] = TRUE;
  $handler->display->display_options['fields']['delivery_ref']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['delivery_ref']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['delivery_ref']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['delivery_ref']['alter']['external'] = 0;
  $handler->display->display_options['fields']['delivery_ref']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['delivery_ref']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['delivery_ref']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['delivery_ref']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['delivery_ref']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['delivery_ref']['alter']['html'] = 0;
  $handler->display->display_options['fields']['delivery_ref']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['delivery_ref']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['delivery_ref']['hide_empty'] = 0;
  $handler->display->display_options['fields']['delivery_ref']['empty_zero'] = 0;
  $handler->display->display_options['fields']['delivery_ref']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['fields']['delivery_ref']['field_api_classes'] = 0;
  /* Field: Commerce Line Item: Order ID */
  $handler->display->display_options['fields']['order_id']['id'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['order_id']['field'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['order_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['order_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['order_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['order_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['order_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['order_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['order_id']['empty_zero'] = 0;
  /* Field: Commerce Product: SKU */
  $handler->display->display_options['fields']['sku']['id'] = 'sku';
  $handler->display->display_options['fields']['sku']['table'] = 'commerce_product';
  $handler->display->display_options['fields']['sku']['field'] = 'sku';
  $handler->display->display_options['fields']['sku']['relationship'] = 'commerce_product_product_id';
  $handler->display->display_options['fields']['sku']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['external'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['sku']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['sku']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['html'] = 0;
  $handler->display->display_options['fields']['sku']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['sku']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['sku']['hide_empty'] = 0;
  $handler->display->display_options['fields']['sku']['empty_zero'] = 0;
  $handler->display->display_options['fields']['sku']['link_to_product'] = 0;
  /* Field: Commerce Line Item: Label */
  $handler->display->display_options['fields']['line_item_label']['id'] = 'line_item_label';
  $handler->display->display_options['fields']['line_item_label']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['line_item_label']['field'] = 'line_item_label';
  $handler->display->display_options['fields']['line_item_label']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['external'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['line_item_label']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['line_item_label']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['html'] = 0;
  $handler->display->display_options['fields']['line_item_label']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['line_item_label']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['line_item_label']['hide_empty'] = 0;
  $handler->display->display_options['fields']['line_item_label']['empty_zero'] = 0;
  /* Field: Commerce Line Item: Quantity */
  $handler->display->display_options['fields']['quantity']['id'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['quantity']['field'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['external'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['quantity']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['quantity']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['html'] = 0;
  $handler->display->display_options['fields']['quantity']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['quantity']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['quantity']['hide_empty'] = 0;
  $handler->display->display_options['fields']['quantity']['empty_zero'] = 0;
  $handler->display->display_options['fields']['quantity']['set_precision'] = 0;
  $handler->display->display_options['fields']['quantity']['precision'] = '0';
  $handler->display->display_options['fields']['quantity']['format_plural'] = 0;
  /* Field: Commerce Line Item: Move item to delivery */
  $handler->display->display_options['fields']['set_delivery']['id'] = 'set_delivery';
  $handler->display->display_options['fields']['set_delivery']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['set_delivery']['field'] = 'set_delivery';
  /* Contextual filter: Commerce Line Item: Order ID */
  $handler->display->display_options['arguments']['order_id']['id'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['arguments']['order_id']['field'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['order_id']['title_enable'] = 1;
  $handler->display->display_options['arguments']['order_id']['title'] = 'Order %1';
  $handler->display->display_options['arguments']['order_id']['breadcrumb'] = 'Title';
  $handler->display->display_options['arguments']['order_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['order_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['order_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['order_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['order_id']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['order_id']['validate']['type'] = 'numeric';
  $handler->display->display_options['arguments']['order_id']['validate']['fail'] = 'empty';
  $handler->display->display_options['arguments']['order_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['order_id']['not'] = 0;
  /* Filter criterion: Fields: Shippable (field_shippable) */
  $handler->display->display_options['filters']['field_shippable_value']['id'] = 'field_shippable_value';
  $handler->display->display_options['filters']['field_shippable_value']['table'] = 'field_data_field_shippable';
  $handler->display->display_options['filters']['field_shippable_value']['field'] = 'field_shippable_value';
  $handler->display->display_options['filters']['field_shippable_value']['relationship'] = 'commerce_product_product_id';
  $handler->display->display_options['filters']['field_shippable_value']['value'] = array(
    1 => '1',
  );
  $translatables['commerce_delivery_by_order'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('No results for this case.'),
    t('Product'),
    t('Delivery id'),
    t('Order ID'),
    t('SKU'),
    t('Label'),
    t('Quantity'),
    t('.'),
    t(','),
    t('Move item to delivery'),
    t('All'),
    t('Order %1'),
    t('Title'),
  );

   $views[$view->name] = $view;
 
  return $views;
}

