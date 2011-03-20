<?php
// $Id: commerce_order_handler_field_order_operations.inc,v 1.3 2010/12/02 06:27:32 rszrama Exp $

/**
 * Field handler to present an order's operations links.
 */
class commerce_delivery_handler_delivery_action_links extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['delivery_id'] = 'delivery_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $delivery_id = $values->{$this->aliases['delivery_id']};

    $links = menu_contextual_links('commerce-delivery', 'admin/commerce/deliveries/do', array($delivery_id));

    if (!empty($links)) {
//      drupal_add_css(drupal_get_path('module', 'commerce_order') . '/theme/commerce_order_views.css');

      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
