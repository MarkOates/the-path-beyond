
#include <allegro_flare/allegro_flare.h>




class InventoryItem
{
public:
  std::string name;
  std::string description;
  ALLEGRO_BITMAP *image;

  InventoryItem(std::string name, std::string description, ALLEGRO_BITMAP *image)
    : name(name)
    , description(description)
    , image(image)
  {}
};



class InventoryGUIScreen : public FGUIScreen
{
public:
  std::vector<InventoryItem *> items;
  int current_mode;

  InventoryGUIScreen(Display *display)
    : FGUIScreen(display)
  {}

  void show() {}
  void hide() {}
  void set_mode(int mode) {}
};



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


