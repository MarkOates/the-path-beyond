
#include <allegro_flare/allegro_flare.h>


#include "inventory.hpp"


////////////////////////////////////////////////////////////////



class Project : public FGUIScreen
{
public:
  InventoryGUIScreen *inventory_screen;

  Project(Display *display)
    : FGUIScreen(display)
    , inventory_screen(new InventoryGUIScreen(display))
  {}
};


int main(int argc, char **argv)
{
  af::initialize();
  Display *display = af::create_display(800, 600, ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
  Project *project = new Project(display);
  af::run_loop();
  return 0;
}


