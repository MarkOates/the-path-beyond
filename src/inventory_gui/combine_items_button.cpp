


#include <inventory_gui/combine_items_button.hpp>

#include <allegro_flare/gui/surface_areas/box.h>
#include <logging.hpp>
#include <style_assets.hpp>



InventoryGUI::CombineButton::CombineButton(UIWidget *parent)
   : UIWidget(parent, "InventoryGUI::CombineButton", new UISurfaceAreaBox(-30, parent->place.size.y/2, 40, 50))
{}



void InventoryGUI::CombineButton::on_click()
{
   if (Logging::at_least(L_VERBOSE)) std::cout << "CombineButton.on_click()" << std::endl;
   send_message_to_parent("attempt_to_combine()");
}



void InventoryGUI::CombineButton::on_draw()
{
   Style::draw_button(Style::NORMAL, place, "<");
}



