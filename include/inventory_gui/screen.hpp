#pragma once



#include <allegro_flare/gui/gui_screen.h>
#include <inventory_item.hpp>



namespace InventoryGUI
{
   class BehindBlocker;
   class CurrentItemShowcase;
   class InventoryToggleButton;
   class ItemButton;
   class Notification;

   class Screen : public UIScreen
   {
   public:
      const int NUM_INVENTORY_ITEM_BUTTONS;

      InventoryGUI::InventoryToggleButton *toggle_button;
      InventoryGUI::CurrentItemShowcase *current_item_showcase;
      InventoryGUI::BehindBlocker *behind_blocker;
      std::vector<InventoryGUI::ItemButton *> item_buttons;

      InventoryGUI::Notification *notification;

      int current_mode;

      Screen(Display *display);

      void on_message(UIWidget *sender, std::string message);
      bool symmetric_yes(InventoryItem itemA, InventoryItem itemB, InventoryItem::Type type1, InventoryItem::Type type2);
      InventoryItem attempt_combination(InventoryItem itemA, InventoryItem itemB);
      bool has_item(InventoryItem::Type item_type);
      InventoryGUI::ItemButton *get_selected_item_button();
      InventoryGUI::ItemButton *find_first_empty_inventory_button();
      bool add_item(InventoryItem item);
      void set_visibility_mode(int mode);
   };
}



