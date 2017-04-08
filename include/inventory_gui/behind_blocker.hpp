#pragma once



#include <allegro_flare/gui/widget.h>



namespace InventoryGUI
{
   class BehindBlocker : public UIWidget
   {
   public:
      BehindBlocker(UIWidget *parent);

      void on_click() override;
      void on_draw() override;
      void show();
      void hide();
   };
}



