


#include <inventory_gui/item_button.hpp>

#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/framework.h>
#include <logging.hpp>
#include <style_assets.hpp>



InventoryGUIItemButton::GUICombineButton::GUICombineButton(UIWidget *parent)
   : UIWidget(parent, "InventoryGUIItemButton::GUICombineButton", new UISurfaceAreaBox(-30, parent->place.size.y/2, 40, 50))
{}



void InventoryGUIItemButton::GUICombineButton::on_click()
{
   if (Logging::at_least(L_VERBOSE)) std::cout << "GUICombineButton.on_click()" << std::endl;
   send_message_to_parent("attempt_to_combine()");
}



void InventoryGUIItemButton::GUICombineButton::on_draw()
{
   Style::draw_button(Style::NORMAL, place, "<");
}



InventoryGUIItemButton::InventoryGUIItemButton(UIWidget *parent, float x, float y)
   : UIWidget(parent, "InventoryGUIItemButton", new UISurfaceAreaBox(x, y, 80, 80))
   , item(InventoryItem::Type::EMPTY)
   , show_x_pos(x)
   , selected(false)
     , combine_button(NULL)
{
   combine_button = new GUICombineButton(this);
}



void InventoryGUIItemButton::set_item(InventoryItem item)
{
   this->item = item;
}



void InventoryGUIItemButton::clear_item()
{
   this->item = InventoryItem(InventoryItem::Type::EMPTY);
}



bool InventoryGUIItemButton::is_empty()
{
   return (item.type == InventoryItem::Type::EMPTY);
}



void InventoryGUIItemButton::on_click()
{
   if (Logging::at_least(L_VERBOSE)) std::cout << "InventoryGUIItemButton" << std::endl;
   send_message_to_parent("feature_my_item()");
}



void InventoryGUIItemButton::select()
{
   selected = true;
}



void InventoryGUIItemButton::deselect()
{
   selected = false;
}



void InventoryGUIItemButton::on_message(UIWidget *sender, std::string message)
{
   // message will always be attempt_to_combine()
   if (sender == combine_button) send_message_to_parent("attempt_to_combine()");
}



void InventoryGUIItemButton::on_draw()
{
   Style::draw_button(selected ? Style::SELECTED : Style::NORMAL, place, item.is_empty() ? "-" : "", item.get_image());
}



void InventoryGUIItemButton::show(float speed)
{
   if (Logging::at_least(L_VERBOSE)) std::cout << "InventoryGUIItemButton.show()" << std::endl;
   Framework::motion().cmove_to(&place.position.x, show_x_pos, speed);
}



void InventoryGUIItemButton::hide(float speed)
{
   if (Logging::at_least(L_VERBOSE)) std::cout << "InventoryGUIItemButton.hide()" << std::endl;
   Framework::motion().cmove_to(&place.position.x, show_x_pos+200, speed);
}



