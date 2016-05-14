
#include <allegro_flare/allegro_flare.h>

#define SCREEN_W 1920
#define SCREEN_H 1080

#include "target_id.hpp"
#include "inventory.hpp"
#include "start_screen.hpp"
#include "world_render.hpp"
#include "navigation.hpp"
#include "script.hpp"

#include "game/scripts/start_title_screen.hpp"
#include "game/scripts/start_game.hpp"



////////////////////////////////////////////////////////////////



class Project : public FGUIScreen
{
public:
  WorldNavigationGUIScreen *world_navigation_gui;
  InventoryGUIScreen *inventory_gui;
  StartScreenGUIScreen *start_screen_gui;

  Project(Display *display)
    : FGUIScreen(display)
    , world_navigation_gui(new WorldNavigationGUIScreen(this, display))
    , inventory_gui(new InventoryGUIScreen(display))
    , start_screen_gui(new StartScreenGUIScreen(this, display))
  {
    Script::initialize(world_navigation_gui, inventory_gui, start_screen_gui);
    load_scripts();

    Script::run("StartTitleScreen()");
  }
  void on_message(FGUIWidget *sender, std::string message)
  {
    std::string trigger_id;
    if (TargetID::extract_trigger_id(message, &trigger_id))
    {
      std::cout << "Project running script \"" << trigger_id << "\"" << std::endl;
      Script::run(trigger_id);
    }
  }
  void load_scripts()
  {
    // load the individual scripts
    new StartTitleScreen();
    new StartGame();
  }
};


int main(int argc, char **argv)
{
  af::initialize();
  Display *display = af::create_display(SCREEN_W, SCREEN_H, ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
  Project *project = new Project(display);
  af::run_loop();
  return 0;
}


