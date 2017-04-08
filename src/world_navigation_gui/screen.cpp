


#include <world_navigation_gui/screen.hpp>

#include <logging.hpp>
#include <global_constants.hpp>
#include <target_id.hpp>



WorldNavigationGUIScreen::WorldNavigationGUIScreen(UIScreen *project_screen, Display *display)
   : UIScreen(display)
   , project_screen(project_screen)
   , nav_up_button(NULL)
   , nav_down_button(NULL)
   , nav_left_button(NULL)
   , nav_right_button(NULL)
     , nav_view(NULL)
{
   nav_up_button = new WorldNavigationGUINavButton(this, SCREEN_W/2, 100, 300, 30);
   nav_down_button = new WorldNavigationGUINavButton(this, SCREEN_W/2, SCREEN_H-100, 300, 30);
   nav_left_button = new WorldNavigationGUINavButton(this, 100, SCREEN_H/2, 30, 300);
   nav_right_button = new WorldNavigationGUINavButton(this, SCREEN_W-100, SCREEN_H/2, 30, 300);
   nav_view = new WorldNavigationGUINavView(this);
}



void WorldNavigationGUIScreen::on_message(UIWidget *sender, std::string message)
{
   int unique_trigger_id = 0;
   std::string trigger_id = "";
   if (TargetID::extract_trigger_id(message, &trigger_id))
   {
      if (Logging::at_least(L_VERBOSE)) std::cout << "WorldNavigationGUIScreen sending on_message for script \"" << trigger_id << "\"" << std::endl;
      project_screen->on_message(this, message);
   }
   else if (TargetID::extract_unique_trigger_id(message, &unique_trigger_id))
   {
      // we have a recieved trigger message
      if (Logging::at_least(L_VERBOSE)) std::cout << "WorldNavigationGUIScreen sending on_message for script id \"" << unique_trigger_id << "\"" << std::endl;
      project_screen->on_message(this, message);
   }
}



void WorldNavigationGUIScreen::set_usability_mode(int mode, float speed)
{
   if (Logging::at_least(L_VERBOSE)) std::cout << " === setting WorldNavigation mode " << mode << " ===" << std::endl;
   switch(mode)
   {
   case 0:
      nav_view->hide();
      nav_up_button->hide(speed);
      nav_down_button->hide(speed);
      nav_left_button->hide(speed);
      nav_right_button->hide(speed);
      break;
   case 1:
      nav_view->show();
      nav_up_button->show_if_has_target(speed);
      nav_down_button->show_if_has_target(speed);
      nav_left_button->show_if_has_target(speed);
      nav_right_button->show_if_has_target(speed);
      break;
   default:
      // Undefined Mode
      if (Logging::at_least(L_NORMAL))
         std::cout
            << CONSOLE_COLOR_YELLOW
            << "undefined InventoryGUIScreen mode " << mode
            << CONSOLE_COLOR_DEFAULT
            << std::endl;
      break;
   }
}



