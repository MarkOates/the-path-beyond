
#include <allegro_flare/allegro_flare.h>

#define SCREEN_W 1920
#define SCREEN_H 1080

#include "inventory.hpp"
#include "start_screen.hpp"
#include "navigation.hpp"


////////////////////////////////////////////////////////////////



class Project : public FGUIScreen
{
public:
  WorldNavigationGUIScreen *world_navigation_screen;
  InventoryGUIScreen *inventory_screen;
  StartScreenGUIScreen *start_screen;

  Project(Display *display)
    : FGUIScreen(display)
    , world_navigation_screen(new WorldNavigationGUIScreen(display))
    , inventory_screen(new InventoryGUIScreen(display))
    , start_screen(new StartScreenGUIScreen(this, display))
  {
    world_navigation_screen->set_usability_mode(0);
    inventory_screen->set_visibility_mode(0);
    start_screen->hide(0);
    start_screen->show(8.0);
  }
  void on_message(FGUIWidget *sender, std::string message)
  {
    std::string trigger_id;
    if (TargetID::extract_trigger_id(message, &trigger_id))
    {
      // TODO: find and call the script here
      std::cout << "Project running script \"" << trigger_id << "\"" << std::endl;
    }
    else if (message == "start_game_please()") start_game();
  }
  void start_game()
  {
    world_navigation_screen->set_usability_mode(1);
    inventory_screen->set_visibility_mode(1);
    start_screen->hide(2.0);
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


