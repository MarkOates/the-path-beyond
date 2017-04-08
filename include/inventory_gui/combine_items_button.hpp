#pragma once



#include <allegro_flare/gui/widget.h>



namespace InventoryGUI
{
   class CombineButton : public UIWidget
   {
   public:
      CombineButton(UIWidget *parent);
      void on_click() override;
      void on_draw() override;
   };
};



