

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

      Script *start_title_screen_script = ScriptCollection::find_by_name("StartTitleScreen()");
      ScriptCollection::run_script(start_title_screen_script);
   }
   void on_message(UIWidget *sender, std::string message)
   {
      std::string script_name = "";
      int script_id = 0;
      if (TargetID::extract_script_name(message, &script_name))
      {
         std::cout << "Project running script \"" << script_name << "\"" << std::endl;

         Script *found_script = ScriptCollection::find_by_name(script_name);
         ScriptCollection::run_script(found_script);
      }
      else if (TargetID::extract_script_id(message, &script_id))
      {
         if (Logging::at_least(L_VERBOSE)) std::cout << "Project running script ID\"" << script_id << "\"" << std::endl;

         Script *script = ScriptCollection::find_by_id(script_id);
         if (!script)
         {
            if (Logging::at_least(L_ERRORS))
               std::cout
                  << CONSOLE_COLOR_RED
                  << "Could not run script: ScriptCollection with script_id [" << script_id << "] not foud."
                  << CONSOLE_COLOR_DEFAULT
                  << std::endl;
         }
         else
         {
            ScriptCollection::run_script(script);
         }
      }
   }
};

