(function ($, Drupal, window, document, undefined) {
	Drupal.behaviors.MobileUserMenu = {
		attach: function (context, settings) {
			$(document).ready(function() {
				var mobile_menu = $('.nice-user-menu-mobile');
				// Initialization.
				mobile_menu.find('.menu-panel').hide();
				mobile_menu.find('.menu-panel[item-id="root"]').show();

				$('.mobile-menu-toggle').on('click', function () {
					var target = $(this).attr('data-target');
					var toggle_class = $(this).attr('data-toggle');
					// Close menu.
					if (!$(target).hasClass(toggle_class)) {
						// Set default item on close.
						set_menu_panel('root');
						set_current_item('root');
						// Fire close event.
						mobile_menu.trigger('niceUserMenuMobileClose');
					} else {
						// Fire open event.
						mobile_menu.trigger('niceUserMenuMobileOpen');
					}
					$(target).toggleClass(toggle_class);
					// Move page content right.
					$('.mobile-left').toggleClass(toggle_class);
				});

				mobile_menu.find('li[item-id] a').on('click', function (e) {
					e.preventDefault();
				});

				mobile_menu.find('li[item-id]').on('click', function (e) {
					var new_item_id =  $(this).attr('item-id');
					set_menu_panel(new_item_id);
					set_current_item(new_item_id);
				});

				mobile_menu.find('.current-item').on('click', function (e) {
					var current_item_id = get_current_menu_panel_id();
					// Find link with this item_id and use it's parent.
					var parent_item_id = mobile_menu.find('li[item-id="' + current_item_id + '"]').attr('parent-id');
					if (parent_item_id) {
						set_menu_panel(parent_item_id);
						set_current_item(parent_item_id);
					}
				});

				var get_current_menu_panel_id = function() {
					return mobile_menu.find('.current-item').attr('current-item-id');
				};

				var set_menu_panel = function(panel_id) {
					var old_menu_panel_id = get_current_menu_panel_id();
					hide_menu_panel(old_menu_panel_id);
					show_menu_panel(panel_id);
				};

				var hide_menu_panel = function(panel_id) {
					mobile_menu.find('.menu-panel[item-id="' + panel_id + '"]').hide();
				};

				var show_menu_panel = function(panel_id) {
					mobile_menu.find('.menu-panel[item-id="' + panel_id + '"]').show();
				};

				var set_current_item = function(item_to_set) {
					mobile_menu.find('.current-item').attr('current-item-id', item_to_set);
					// Set title.
					var title = mobile_menu.find('li[item-id="' + item_to_set + '"]').attr('item-title');
					// In case of root menu panel.
					if (!title) {
						title = "";
					}
					mobile_menu.find('.current-item').html(title);
				};
			});
		}
	};
})(jQuery, Drupal, this, this.document);