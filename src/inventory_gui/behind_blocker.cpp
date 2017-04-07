


#include <inventory_gui/behind_blocker.hpp>

#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro5/allegro_primitives.h>
#include <global_constants.hpp>



InventoryGUIBehindBlocker::InventoryGUIBehindBlocker(UIWidget *parent)
   : UIWidget(parent, "InventoryGUIBehindBlocker", new UISurfaceAreaBox(SCREEN_W/2, SCREEN_H/2, SCREEN_W, SCREEN_H))
{}



void InventoryGUIBehindBlocker::on_click()
{
   send_message_to_parent("set_visibility_mode(1)");
}



void InventoryGUIBehindBlocker::on_draw()
{
   al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, color::color(color::black, 0.3));
}



void InventoryGUIBehindBlocker::show()
{
   place.scale.x = 1.0;
   place.scale.y = 1.0;
}



void InventoryGUIBehindBlocker::hide()
{
   place.scale.x = 0;
   place.scale.y = 0;
}

