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
      UIScreen *project_screen;
      UIText *title_text;
      UIText *instructions;
      StartButton *start_screen_button;

      Screen(UIScreen *project_screen, Display *display);
      void on_message(UIWidget *sender, std::string message) override;
      void show(float speed=2.0);
      void hide(float speed=2.0);
   };
}



