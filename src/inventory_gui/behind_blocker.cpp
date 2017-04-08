


#include <inventory_gui/behind_blocker.hpp>

#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro5/allegro_primitives.h>
#include <global_constants.hpp>



InventoryGUI::BehindBlocker::BehindBlocker(UIWidget *parent)
   : UIWidget(parent, "InventoryGUI::BehindBlocker", new UISurfaceAreaBox(SCREEN_W/2, SCREEN_H/2, SCREEN_W, SCREEN_H))
{}



void InventoryGUI::BehindBlocker::on_click()
{
   send_message_to_parent("set_visibility_mode(1)");
}



void InventoryGUI::BehindBlocker::on_draw()
{
   al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, color::color(color::black, 0.3));
}



void InventoryGUI::BehindBlocker::show()
{
   place.scale.x = 1.0;
   place.scale.y = 1.0;
}



void InventoryGUI::BehindBlocker::hide()
{
   place.scale.x = 0;
   place.scale.y = 0;
}

