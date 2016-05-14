
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
  bool is_empty()
  {
    return id == "";
  }
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


class WorldNavigationGUINavView : public FGUIWidget
{
public:
  ALLEGRO_BITMAP *render;

  WorldNavigationGUINavView(FGUIWidget *parent)
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
  void on_draw() override
  {
    al_draw_rectangle(0, 0, place.size.x, place.size.y, color::green, 8);
    al_draw_bitmap(render, 0, 0, 0);
  }
  void show()
  {
    af::motion.cmove_to(&place.scale.x, 1.0, 0);
  }
  void hide()
  {
    af::motion.cmove_to(&place.scale.x, 0.0, 0);
  }
};


class WorldNavigationGUINavButton : public FGUIWidget
{
public:
  TargetID target_id;
  float show_pos_y;

  WorldNavigationGUINavButton(FGUIWidget *parent, float x, float y, float w, float h)
    : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
    , target_id("")
    , show_pos_y(y)
  {}
  void set_target_id(TargetID target_id) { this->target_id = target_id; }
  void on_click() override { send_message_to_parent(target_id.get_trigger_message()); }
  void show(float speed=0.4)
  {
    af::motion.cmove_to(&place.position.y, show_pos_y, speed);
  }
  void hide(float speed=0.4)
  {
    af::motion.cmove_to(&place.position.y, -200, speed);
  }
  void show_if_has_target(float speed=0.4)
  {
    if (!target_id.is_empty()) show(speed);
  }
};


class WorldNavigationGUIScreen : public FGUIScreen
{
public:
  WorldNavigationGUINavView *nav_view;
  WorldNavigationGUINavButton *nav_up_button;
  WorldNavigationGUINavButton *nav_down_button;
  WorldNavigationGUINavButton *nav_left_button;
  WorldNavigationGUINavButton *nav_right_button;

  WorldNavigationGUIScreen(Display *display)
    : FGUIScreen(display)
    , nav_view(NULL)
    , nav_up_button(NULL)
    , nav_down_button(NULL)
    , nav_left_button(NULL)
    , nav_right_button(NULL)
  {
    nav_view = new WorldNavigationGUINavView(this);
    nav_up_button = new WorldNavigationGUINavButton(this, SCREEN_W/2, 100, 300, 30);
    nav_down_button = new WorldNavigationGUINavButton(this, SCREEN_W/2, SCREEN_H-100, 300, 30);
    nav_left_button = new WorldNavigationGUINavButton(this, 100, SCREEN_H/2, 30, 300);
    nav_right_button = new WorldNavigationGUINavButton(this, SCREEN_W-100, SCREEN_H/2, 30, 300);
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
  void set_usability_mode(int mode)
  {
    std::cout << " === setting WorldNavigation mode " << mode << " ===" << std::endl;
    switch(mode)
    {
      case 0:
        nav_view->hide();
        nav_up_button->hide();
        nav_down_button->hide();
        nav_left_button->hide();
        nav_right_button->hide();
        break;
      case 1:
        nav_view->show();
        nav_up_button->show_if_has_target();
        nav_down_button->show_if_has_target();
        nav_left_button->show_if_has_target();
        nav_right_button->show_if_has_target();
        break;
      default:
        // Undefined Mode
        std::cout << "undefined InventoryGUIScreen mode " << mode << std::endl;
        break;
    }
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
    if (message == "start_game_please()") start_game();
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


