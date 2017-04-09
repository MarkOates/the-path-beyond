#pragma once



#include <allegro_flare/gui/gui_screen.h>
#include <start_screen_gui/start_button.hpp>
#include <world_navigation_gui/nav_view.hpp>



class UIText;



namespace StartScreenGUI
{
   class Screen : public UIScreen
   {
   public:
      UIText *title_text;
      UIText *instructions;
      StartButton *start_screen_button;

      Screen(Display *display);
      void show(float speed=2.0);
      void hide(float speed=2.0);
   };
}



