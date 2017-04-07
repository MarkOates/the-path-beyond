#pragma once



#include <allegro_flare/gui/widget.h>
#include <inventory_item.hpp>



class InventoryGUIInventoryToggleButton : public UIWidget
{
public:
   InventoryItem shown_item;

   InventoryGUIInventoryToggleButton(UIWidget *parent);

   void on_click();
   void set_shown_item(InventoryItem item);
   void on_draw();
   void show(float speed=0.5);
   void hide(float speed=0.5);
};



