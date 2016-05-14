
#include <allegro_flare/allegro_flare.h>

#define SCREEN_W 1920
#define SCREEN_H 1080

#include "inventory.hpp"
#include "start_screen.hpp"


////////////////////////////////////////////////////////////////


class TargetID
{
public:
  std::string id;
  TargetID(std::string id)
    : id(id)
  {}
  std::string get_trigger_message() { return tostring("trigger_target_id ") + id; }
  static bool extract_trigger_id(std::string message, std::string *extracted_id)
  {
    if (strncmp(message.c_str(), "trigger_target_id ", 18) == 0)
    {
      // we have a valid trigger message
      *extracted_id = message.substr(18);
      return true;
    }
    return false;
  }
};


class WorldScreenGUINavView : public FGUIWidget
{
public:
  ALLEGRO_BITMAP *render;

  WorldScreenGUINavView(FGUIWidget *parent)
    : FGUIWidget(parent, new FGUISurfaceAreaBox(SCREEN_W/2, SCREEN_H/2, SCREEN_W, SCREEN_H))
    , render(NULL)
  {
    // initialize our rendering surface
    render = al_create_bitmap(place.size.x, place.size.y);

    ALLEGRO_STATE state;
    al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
    al_set_target_bitmap(render);
    al_clear_to_color(color::skyblue);
    al_restore_state(&state);
  }
  void on_click() override
  {
    // TODO: sample the render for mouse clicks on colors
    // match the pixel color to a target ID, and send a trigger message
    // to the parent
  }
};


class WorldScreenGUINavButton : public FGUIWidget
{
public:
  TargetID target_id;

  WorldScreenGUINavButton(FGUIWidget *parent, float x, float y, float w, float h)
    : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
    , target_id("")
  {}
  void set_target_id(TargetID target_id) { this->target_id = target_id; }
  void on_click() override { send_message_to_parent(target_id.get_trigger_message()); }
};


class WorldScreenGUIScreen : public FGUIScreen
{
public:
  WorldScreenGUINavView *nav_view;
  WorldScreenGUINavButton *nav_up_button;
  WorldScreenGUINavButton *nav_down_button;
  WorldScreenGUINavButton *nav_left_button;
  WorldScreenGUINavButton *nav_right_button;

  WorldScreenGUIScreen(Display *display)
    : FGUIScreen(display)
    , nav_view(NULL)
    , nav_up_button(NULL)
    , nav_down_button(NULL)
    , nav_left_button(NULL)
    , nav_right_button(NULL)
  {
    nav_view = new WorldScreenGUINavView(this);
    nav_up_button = new WorldScreenGUINavButton(this, SCREEN_W/2, 100, 300, 30);
    nav_down_button = new WorldScreenGUINavButton(this, SCREEN_W/2, SCREEN_H-100, 300, 30);
    nav_left_button = new WorldScreenGUINavButton(this, 100, SCREEN_H/2, 30, 300);
    nav_right_button = new WorldScreenGUINavButton(this, SCREEN_W-100, SCREEN_H/2, 30, 300);
  }
  void trigger_target_with_id(std::string id)
  {
    std::cout << "Triggering TargetID " << id << std::endl;
    // TODO: send out a message to activate a target by id
  }
  void on_message(FGUIWidget *sender, std::string message)
  {
    std::string trigger_id;
    if (TargetID::extract_trigger_id(message, &trigger_id))
      trigger_target_with_id(trigger_id);
  }
};



////////////////////////////////////////////////////////////////



class Project : public FGUIScreen
{
public:
  WorldScreenGUIScreen *world_screen;
  InventoryGUIScreen *inventory_screen;
  StartScreenGUIScreen *start_screen;

  Project(Display *display)
    : FGUIScreen(display)
    , world_screen(new WorldScreenGUIScreen(display))
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


