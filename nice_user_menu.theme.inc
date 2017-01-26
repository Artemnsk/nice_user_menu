<?php

/**
 * Preprocess callback for theme_nice_user_menu_mobile().
 */
function nice_user_menu_mobile_preprocess(&$variables) {
	// Collect menus.
	$mobile_menu_menus = variable_get('nice_user_menu_mobile_menus', array());
	// Alter menus.
	drupal_alter('nice_user_menu_mobile_menus', $mobile_menu_menus);
	if ($mobile_menu_menus) {
		$mobile_menu = array();
		foreach ($mobile_menu_menus as $menu_name) {
			if ($menu = menu_build_tree($menu_name)) {
				$mobile_menu = drupal_array_merge_deep($mobile_menu, $menu);
			}
		}
		$variables['menu_panels'] = _nice_user_menu_mobile_preprocess_recursive($mobile_menu, 'root');
	}
}

function _nice_user_menu_mobile_preprocess_recursive($below, $current_menu_panel_id) {
	$response = array();
	$menu_panels_to_process = array();
	if (!empty($below)) {
		$new_menu_panel = array(
			'menu_panel_id' => $current_menu_panel_id,
			'items' => array(),
		);
		foreach ($below as $key => $menu_item) {
			// Check access.
			if (empty($menu_item['link']['access']) || $menu_item['link']['access'] == FALSE || $menu_item['link']['hidden']) {
				continue;
			}
			// Set item id.
			$current_item_id = $menu_item['link']['mlid'];
			// If there is no 'below' arr for this link or it contains of no accessible links - render it as simple link.
			if (empty($menu_item['below']) && !_nice_user_menu_mobile_preprocess_at_least_one_accessible_or_visible_link_exists($menu_item['below'])) {
				$options = $menu_item['link']['options'];
				$options['html'] = TRUE;
				$new_menu_panel['items'][] = array(
					'link' => l($menu_item['link']['title'], $menu_item['link']['link_path'], $options),
					'parent_id' => $current_menu_panel_id,
					'item_id' => FALSE,
					'item_title' => FALSE,
				);
			} else {
				// Else render this link as link to new menu panel.
				// After this loop we will process this link's 'below' items and add menu panels.
				$menu_panels_to_process[] = array(
					'below' => $menu_item['below'],
					'item_id' => $current_item_id,
				);
				$options = $menu_item['link']['options'];
				$options['html'] = TRUE;
				$new_menu_panel['items'][] = array(
					'link' => l($menu_item['link']['title'], $menu_item['link']['link_path'], $options),
					'parent_id' => $current_menu_panel_id,
					'item_id' => $current_item_id,
					'item_title' => $menu_item['link']['title'],
				);
			}
		}
		$response[] = $new_menu_panel;
		// Process all 'sub'menu panels of links which have 'below' items.
		foreach ($menu_panels_to_process as $menu_panels_to_process) {
			$response = array_merge($response, _nice_user_menu_mobile_preprocess_recursive($menu_panels_to_process['below'], $menu_panels_to_process['item_id']));
		}
	}
	return $response;
}

function _nice_user_menu_mobile_preprocess_at_least_one_accessible_or_visible_link_exists($below) {
	foreach ($below as $menu_item) {
		if ($menu_item['link']['access'] == TRUE && !$menu_item['link']['hidden']) {
			return TRUE;
		}
	}
	return FALSE;
}