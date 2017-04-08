#pragma once



#include <allegro_flare/gui/widget.h>
#include <target_id.hpp>



namespace WorldNavigationGUI
{
   class NavButton : public UIWidget
   {
   public:
      TargetID target_id;
      float show_pos_y;

      NavButton(UIWidget *parent, float x, float y, float w, float h);
      void set_target_id(TargetID target_id);
      void on_click() override;
      void on_draw() override;
      void show(float speed=0.4);
      void hide(float speed=0.4);
      void show_if_has_target(float speed=0.4);
   };
}



