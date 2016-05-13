
#include <allegro_flare/allegro_flare.h>

#define SCREEN_W 1920
#define SCREEN_H 1080

#include "inventory.hpp"
#include "start_screen.hpp"


////////////////////////////////////////////////////////////////



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
};


class WorldScreenGUINavButton : public FGUIWidget
{
public:
  WorldScreenGUINavButton(FGUIWidget *parent, float x, float y, float w, float h)
    : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
  {}
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


