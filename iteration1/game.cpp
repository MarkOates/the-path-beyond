
#include <allegro_flare/allegro_flare.h>

#define SCREEN_W 1920
#define SCREEN_H 1080

#include "target_id.hpp"
#include "inventory.hpp"
#include "start_screen.hpp"
#include "navigation.hpp"


////////////////////////////////////////////////////////////////



class Script : public ElementID
{
public:
  static ElementIDManager *manager;
  static WorldNavigationGUIScreen *world_navigation_gui;
  static InventoryGUIScreen *inventory_gui;
  static StartScreenGUIScreen *start_screen_gui;
  static bool initialized;

  static void initialize(
      WorldNavigationGUIScreen *wnguis,
      InventoryGUIScreen *iguis,
      StartScreenGUIScreen *ssgui
      )
  {
    if (initialized) return;

    manager = new ElementIDManager();
    world_navigation_gui = wnguis;
    start_screen_gui = ssgui;
    inventory_gui = iguis;

    initialized = true;
  }
  static Script *find_by_id(std::string id)
  {
    ElementID *element = manager->get_element_by_id(id);
    if (element) return static_cast<Script *>(element);
    return NULL;
  }
  static bool run(std::string id)
  {
    Script *script = find_by_id(id);
    if (!script)
    {
      std::cout << "Could not run script: Script \"" << id << "\" not foud." << std::endl;
      return false;
    }
    std::cout << "{{{ Activating script \"" << script->get_id() << "\"" << std::endl;
    script->activate();
    std::cout << "}}} Script \"" << script->get_id() << "\" finished" << std::endl;
    return true;
  }

  Script(std::string id) : ElementID(manager)
  {
    set_id(id);
  }
  virtual void activate() = 0;
};
ElementIDManager *Script::manager = NULL;
WorldNavigationGUIScreen *Script::world_navigation_gui = NULL;
InventoryGUIScreen *Script::inventory_gui = NULL;
StartScreenGUIScreen *Script::start_screen_gui = NULL;
bool Script::initialized = false;



class StartTitleScreen: public Script
{
public:
  StartTitleScreen() : Script("StartTitleScreen()") {}
  void activate() override
  {
    world_navigation_gui->set_usability_mode(0);
    inventory_gui->set_visibility_mode(0);
    start_screen_gui->hide(0);
    start_screen_gui->show(8.0);
  }
};



class StartGame: public Script
{
public:
  StartGame() : Script("StartGame()") {}
  void activate() override
  {
    world_navigation_gui->set_usability_mode(1);
    inventory_gui->set_visibility_mode(1);
    start_screen_gui->hide(2.0);
  }
};



////////////////////////////////////////////////////////////////



class Project : public FGUIScreen
{
public:
  WorldNavigationGUIScreen *world_navigation_screen;
  InventoryGUIScreen *inventory_screen;
  StartScreenGUIScreen *start_screen;

  Project(Display *display)
    : FGUIScreen(display)
    , world_navigation_screen(new WorldNavigationGUIScreen(this, display))
    , inventory_screen(new InventoryGUIScreen(display))
    , start_screen(new StartScreenGUIScreen(this, display))
  {
    Script::initialize(world_navigation_screen, inventory_screen, start_screen);
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


