#pragma once



#include <allegro_flare/gui/widget.h>
#include <inventory_item.hpp>



namespace InventoryGUI
{
   class InventoryToggleButton : public UIWidget
   {
   public:
      InventoryItem shown_item;

      InventoryToggleButton(UIWidget *parent);

      void on_click();
      void set_shown_item(InventoryItem item);
      void on_draw();
      void show(float speed=0.5);
      void hide(float speed=0.5);
   };
}



