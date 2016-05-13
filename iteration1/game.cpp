
#include <allegro_flare/allegro_flare.h>

#define SCREEN_W 1920
#define SCREEN_H 1080

#include "inventory.hpp"
#include "start_screen.hpp"



////////////////////////////////////////////////////////////////



class Project : public FGUIScreen
{
public:
  InventoryGUIScreen *inventory_screen;
  StartScreenGUIScreen *start_screen;

  Project(Display *display)
    : FGUIScreen(display)
    , inventory_screen(new InventoryGUIScreen(display))
    , start_screen(new StartScreenGUIScreen(this, display))
  {
    inventory_screen->set_visibility_mode(0);
    start_screen->hide(0);
    start_screen->show(8.0);
  }
  void on_message(FGUIWidget *sender, std::string message)
  {
    if (message == "start_game_please()") start_game();
  }
  void start_game()
  {
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


