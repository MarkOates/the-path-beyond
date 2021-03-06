


#include <inventory_gui/screen.hpp>

#include <inventory_gui/inventory_toggle_button.hpp>
#include <inventory_gui/item_button.hpp>
#include <inventory_gui/current_item_showcase.hpp>
#include <inventory_gui/notification.hpp>
#include <inventory_gui/behind_blocker.hpp>
#include <global_constants.hpp>



InventoryGUI::Screen::Screen(Display *display)
   : UIScreen(display)
   , NUM_INVENTORY_ITEM_BUTTONS(2)
   , toggle_button(NULL)
   , current_item_showcase(NULL)
   , behind_blocker(NULL)
   , notification(NULL)
   , item_buttons()
   , current_mode(1)
{
   notification = new InventoryGUI::Notification(this);

   // create our Inventory GUI Widgets
   for (unsigned i=0; i<NUM_INVENTORY_ITEM_BUTTONS; i++)
   {
      InventoryGUI::ItemButton *button = new InventoryGUI::ItemButton(this, SCREEN_W-100, 200+90*i);
      item_buttons.push_back(button);
   }

   current_item_showcase = new InventoryGUI::CurrentItemShowcase(this);
   toggle_button = new InventoryGUI::InventoryToggleButton(this);
   behind_blocker = new InventoryGUI::BehindBlocker(this);

   // set our current GUI mode
   set_visibility_mode(current_mode);
}



void InventoryGUI::Screen::on_message(UIWidget *sender, std::string message)
{
   if (message == "") return;
   else if (message == "toggle_visibility_mode()")
   {
      if (current_mode == 1) set_visibility_mode(2);
      else if (current_mode == 2) set_visibility_mode(1);
   }
   else if (message == "set_visibility_mode(0)") set_visibility_mode(0);
   else if (message == "set_visibility_mode(1)") set_visibility_mode(1);
   else if (message == "set_visibility_mode(2)") set_visibility_mode(2);
   else if (message == "feature_my_item()")
   {
      // deselect all the other buttons
      for (auto &item : item_buttons)
         if (item != sender) static_cast<InventoryGUI::ItemButton *>(item)->deselect();

      // set the item in the showcase
      InventoryGUI::ItemButton *button = static_cast<InventoryGUI::ItemButton *>(sender);
      current_item_showcase->set_item(button->item);
      button->select();

      // set the item in the inventory toggle button
      toggle_button->set_shown_item(button->item);
   }
   else if (message == "attempt_to_combine()")
   {
      InventoryGUI::ItemButton *combining_button = static_cast<InventoryGUI::ItemButton *>(sender);
      InventoryItem combined_item = attempt_combination(current_item_showcase->item, combining_button->item);
      if (!combined_item.is_empty())
      {
         // combination was successful
         std::cout << "Combination was successful" << std::endl;

         // clear the item on both selected button
         InventoryGUI::ItemButton *selected_item_button = get_selected_item_button();
         selected_item_button->clear_item();
         selected_item_button->deselect();

         // set the new combined_item item on the combining_button
         combining_button->set_item(combined_item);
         combining_button->select();
         combining_button->send_message_to_parent("feature_my_item()");

         notification->show("You decrypted the Card Key");
      }
      else
      {
         // combination failed
         std::cout << "Combination failed" << std::endl;
      }
   }
}



bool InventoryGUI::Screen::symmetric_yes(InventoryItem itemA, InventoryItem itemB, InventoryItem::Type type1, InventoryItem::Type type2)
   // ^ nice 3AM name for a function
{
   if (itemA.type == type1 && itemB.type == type2) return true;
   if (itemB.type == type1 && itemA.type == type2) return true;
   return false;
}



InventoryItem InventoryGUI::Screen::attempt_combination(InventoryItem itemA, InventoryItem itemB)
{
   if (symmetric_yes(itemA, itemB, InventoryItem::Type::ENCRYPTED_CARD_KEY, InventoryItem::Type::CARD_KEY_DECRYPTER))
   {
      return InventoryItem(InventoryItem::Type::DECRYPTED_CARD_KEY);
   }

   // TODO: process possible combinations here
   // return the item that is created when combining two other items
   // a failed combination will return an item that is EMPTY
   return InventoryItem(InventoryItem::Type::EMPTY);
}



bool InventoryGUI::Screen::has_item(InventoryItem::Type item_type)
{
   for (auto &button : item_buttons)
      if (button->item.type == item_type) return true;
   return false;
}



InventoryGUI::ItemButton *InventoryGUI::Screen::get_selected_item_button()
{
   for (auto &button : item_buttons) if (button->selected) return button;
   return NULL;
}



InventoryGUI::ItemButton *InventoryGUI::Screen::find_first_empty_inventory_button()
{
   for (auto &button : item_buttons) if (button->is_empty()) return button;
   return NULL;
}



bool InventoryGUI::Screen::add_item(InventoryItem item)
{
   InventoryGUI::ItemButton *empty_button = find_first_empty_inventory_button();
   if (!empty_button) return false;
   empty_button->set_item(item);
   return true;
}



void InventoryGUI::Screen::set_visibility_mode(int mode)
{
   std::cout << " === setting GUI mode " << mode << " ===" << std::endl;
   switch(mode)
   {
   case 0:
      behind_blocker->hide();
      toggle_button->hide();
      current_item_showcase->hide();
      for (auto &button : item_buttons) button->hide();
      current_mode = 0;
      break;
   case 1:
      behind_blocker->hide();
      toggle_button->show();
      current_item_showcase->hide();
      for (auto &button : item_buttons) button->hide();
      current_mode = 1;
      break;
   case 2:
      behind_blocker->show();
      toggle_button->show();
      current_item_showcase->show();
      for (auto &button : item_buttons) button->show();
      current_mode = 2;
      break;
   default:
      // Undefined Mode
      std::cout << "undefined InventoryGUI::Screen mode " << mode << std::endl;
      break;
   }
}



