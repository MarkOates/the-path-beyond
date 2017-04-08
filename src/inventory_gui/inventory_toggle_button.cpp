


#include <inventory_gui/inventory_toggle_button.hpp>

#include <allegro_flare/framework.h>
#include <allegro_flare/gui/surface_areas/box.h>
#include <global_constants.hpp>
#include <logging.hpp>
#include <style_assets.hpp>



InventoryGUI::InventoryToggleButton::InventoryToggleButton(UIWidget *parent)
   : UIWidget(parent, "InventoryGUI::InventoryToggleButton", new UISurfaceAreaBox(SCREEN_W-80, 60, 120, 80))
   , shown_item(InventoryItem::Type::EMPTY)
{}



void InventoryGUI::InventoryToggleButton::on_click()
{
   if (Logging::at_least(L_VERBOSE)) std::cout << "InventoryGUI::InventoryToggleButton" << std::endl;
   send_message_to_parent("toggle_visibility_mode()");
}



void InventoryGUI::InventoryToggleButton::set_shown_item(InventoryItem item)
{
   shown_item = item;
}



void InventoryGUI::InventoryToggleButton::on_draw()
{
   Style::draw_button(Style::NORMAL, place, shown_item.is_empty() ? "0" : "", shown_item.get_image());
}



void InventoryGUI::InventoryToggleButton::show(float speed)
{
   if (Logging::at_least(L_VERBOSE)) std::cout << "InventoryGUI::InventoryToggleButton.show()" << std::endl;
   Framework::motion().cmove_to(&place.position.x, SCREEN_W-80, speed);
}



void InventoryGUI::InventoryToggleButton::hide(float speed)
{
   if (Logging::at_least(L_VERBOSE)) std::cout << "InventoryGUI::InventoryToggleButton.hide()" << std::endl;
   Framework::motion().cmove_to(&place.position.x, SCREEN_W+60, speed);
}



