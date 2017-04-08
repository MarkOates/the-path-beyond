#pragma once



#include <allegro_flare/gui/gui_screen.h>
#include <world_navigation_gui/nav_button.hpp>
#include <world_navigation_gui/nav_view.hpp>



class WorldNavigationGUIScreen : public UIScreen
{
public:
  UIScreen *project_screen;

  WorldNavigationGUI::NavButton *nav_up_button;
  WorldNavigationGUI::NavButton *nav_down_button;
  WorldNavigationGUI::NavButton *nav_left_button;
  WorldNavigationGUI::NavButton *nav_right_button;
  WorldNavigationGUI::NavView *nav_view;

  WorldNavigationGUIScreen(UIScreen *project_screen, Display *display);

  void on_message(UIWidget *sender, std::string message);
  void set_usability_mode(int mode, float speed=0.4);
};



