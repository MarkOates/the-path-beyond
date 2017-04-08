


#include <inventory_gui/item_button.hpp>

#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/framework.h>
#include <inventory_gui/combine_items_button.hpp>
#include <logging.hpp>
#include <style_assets.hpp>



InventoryGUI::ItemButton::ItemButton(UIWidget *parent, float x, float y)
   : UIWidget(parent, "InventoryGUI::ItemButton", new UISurfaceAreaBox(x, y, 80, 80))
   , item(InventoryItem::Type::EMPTY)
   , show_x_pos(x)
   , selected(false)
     , combine_button(NULL)
{
   combine_button = new InventoryGUI::CombineButton(this);
}



void InventoryGUI::ItemButton::set_item(InventoryItem item)
{
   this->item = item;
}



void InventoryGUI::ItemButton::clear_item()
{
   this->item = InventoryItem(InventoryItem::Type::EMPTY);
}



bool InventoryGUI::ItemButton::is_empty()
{
   return (item.type == InventoryItem::Type::EMPTY);
}



void InventoryGUI::ItemButton::on_click()
{
   if (Logging::at_least(L_VERBOSE)) std::cout << "InventoryGUI::ItemButton" << std::endl;
   send_message_to_parent("feature_my_item()");
}



void InventoryGUI::ItemButton::select()
{
   selected = true;
}



void InventoryGUI::ItemButton::deselect()
{
   selected = false;
}



void InventoryGUI::ItemButton::on_message(UIWidget *sender, std::string message)
{
   // message will always be attempt_to_combine()
   if (sender == combine_button) send_message_to_parent("attempt_to_combine()");
}



void InventoryGUI::ItemButton::on_draw()
{
   Style::draw_button(selected ? Style::SELECTED : Style::NORMAL, place, item.is_empty() ? "-" : "", item.get_image());
}



void InventoryGUI::ItemButton::show(float speed)
{
   if (Logging::at_least(L_VERBOSE)) std::cout << "InventoryGUI::ItemButton.show()" << std::endl;
   Framework::motion().cmove_to(&place.position.x, show_x_pos, speed);
}



void InventoryGUI::ItemButton::hide(float speed)
{
   if (Logging::at_least(L_VERBOSE)) std::cout << "InventoryGUI::ItemButton.hide()" << std::endl;
   Framework::motion().cmove_to(&place.position.x, show_x_pos+200, speed);
}



