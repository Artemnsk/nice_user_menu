<div class="nice-user-menu-mobile-wrapper">
	<div class="nice-user-menu-mobile mobile-menu-collapse">
		<button type="button" class="mobile-menu-toggle navbar-toggle" data-toggle="mobile-menu-collapse" data-target=".nice-user-menu-mobile">
			<i class="fa fa-bars" aria-hidden="true"></i>
		</button>

		<div class="mobile-user-menu">
			<div class="current-item" current-item-id="root"></div>
			<?php foreach($menu_panels as $menu_panel): ?>
				<div class="menu-panel" item-id="<?php print $menu_panel['menu_panel_id'];?>">
						<ul>
							<?php foreach($menu_panel['items'] as $menu_panel_item): ?>
								<li <?php if ($menu_panel_item['parent_id']) print "parent-id='" . $menu_panel_item['parent_id'] . "'";?> <?php if ($menu_panel_item['item_title']) print "item-title='" . $menu_panel_item['item_title'] . "'";?> <?php if ($menu_panel_item['item_id']) print "item-id='" . $menu_panel_item['item_id'] . "'";?>>
									<?php print $menu_panel_item['link']; ?>
								</li>
							<?php endforeach; ?>
						</ul>
					</div>
			<?php endforeach; ?>
			</div>
	</div>
</div>