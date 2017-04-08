#pragma once



#include <allegro_flare/gui/gui_screen.h>
#include <inventory_item.hpp>



class InventoryGUIInventoryToggleButton;
class InventoryGUICurrentItemShowcase;
namespace InventoryGUI
{
   class BehindBlocker;
};
class InventoryGUIItemButton;
class InventoryGUINotification;



class InventoryGUIScreen : public UIScreen
{
public:
  const int NUM_INVENTORY_ITEM_BUTTONS;

  // MODE 1 Widget
  InventoryGUIInventoryToggleButton *toggle_button;

  // MODE 2 Widgets
  InventoryGUICurrentItemShowcase *current_item_showcase;
  InventoryGUI::BehindBlocker *behind_blocker;
  std::vector<InventoryGUIItemButton *> item_buttons;

  InventoryGUINotification *notification;

  int current_mode;

  InventoryGUIScreen(Display *display);

  void on_message(UIWidget *sender, std::string message);
  bool symmetric_yes(InventoryItem itemA, InventoryItem itemB, InventoryItem::Type type1, InventoryItem::Type type2);
   InventoryItem attempt_combination(InventoryItem itemA, InventoryItem itemB);
  bool has_item(InventoryItem::Type item_type);
  InventoryGUIItemButton *get_selected_item_button();
  InventoryGUIItemButton *find_first_empty_inventory_button();
  bool add_item(InventoryItem item);
  void set_visibility_mode(int mode);
};



