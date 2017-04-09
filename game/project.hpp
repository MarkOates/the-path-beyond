

#include "./script_helper.hpp"

#include "./scripts/start_title_screen.hpp"
#include "./scripts/start_game.hpp"

#include "logging.hpp"



class Project : public UIScreen
{
public:
   WorldRenderScreen *world_render;
   WorldNavigationGUI::Screen *world_navigation_gui;
   InventoryGUI::Screen *inventory_gui;
   StartScreenGUI::Screen *start_screen_gui;

   Project(Display *display)
      : UIScreen(display)
      , world_render(new WorldRenderScreen(display))
      , world_navigation_gui(new WorldNavigationGUI::Screen(this, display))
      , inventory_gui(new InventoryGUI::Screen(display))
      , start_screen_gui(new StartScreenGUI::Screen(this, display))
   {
      // link nav render surface
      world_render->set_scene_targets_render_surface(world_navigation_gui->nav_view->render);

      ScriptHelper::initialize(world_render, world_navigation_gui, inventory_gui, start_screen_gui);

      ScriptCollection::run("StartTitleScreen()");
   }
   void on_message(UIWidget *sender, std::string message)
   {
      std::string trigger_id = "";
      int unique_trigger_id = 0;
      if (TargetID::extract_trigger_id(message, &trigger_id))
      {
         std::cout << "Project running script \"" << trigger_id << "\"" << std::endl;
         ScriptCollection::run(trigger_id);
      }
      else if (TargetID::extract_unique_trigger_id(message, &unique_trigger_id))
      {
         if (Logging::at_least(L_VERBOSE)) std::cout << "Project running script ID\"" << unique_trigger_id << "\"" << std::endl;
         ScriptCollection::run_by_unique_id(unique_trigger_id);
      }
   }
};

