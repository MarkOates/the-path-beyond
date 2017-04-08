#pragma once


#include <allegro_flare/gui/widget.h>



namespace StartScreenGUI
{
   class StartButton : public UIWidget
   {
   public:
      StartButton(UIWidget *parent);
      void on_click() override;
      void on_draw() override;
   };
}



