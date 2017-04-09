#pragma once



#include <allegro_flare/gui/widget.h>



namespace WorldNavigationGUI
{
   class NavButton : public UIWidget
   {
   public:
      std::string script_name;
      float show_pos_y;

      NavButton(UIWidget *parent, float x, float y, float w, float h);
      void set_script_by_name(std::string script_name);
      void on_click() override;
      void on_draw() override;
      void show(float speed=0.4);
      void hide(float speed=0.4);
      void show_if_has_target(float speed=0.4);
   };
}



