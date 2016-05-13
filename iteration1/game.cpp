
#include <allegro_flare/allegro_flare.h>

#define SCREEN_W 1920
#define SCREEN_H 1080

#include "inventory.hpp"




class StartScreenGUIScreen : public FGUIScreen
{
private:
  class StartScreenGUIStartButton : public FGUIWidget
  {
  public:
    StartScreenGUIStartButton(FGUIWidget *parent)
      : FGUIWidget(parent, new FGUISurfaceAreaBox(SCREEN_W/2, SCREEN_H/3*2, 200, 90))
    {}
    void on_click() override
    {
      std::cout << "StartScreeGUIStartButton" << std::endl;
    }
  };

public:
  FGUIText *title_text;
  StartScreenGUIStartButton *start_screen_button;

  StartScreenGUIScreen(Display *display)
    : FGUIScreen(display)
    , title_text(NULL)
    , start_screen_button(NULL)
  {
    title_text = new FGUIText(this, SCREEN_W/2, SCREEN_H/3, "- THE PATH -");
    title_text->place.align.x = 0.5;
    start_screen_button = new StartScreenGUIStartButton(this);
  }
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
  Display *display = af::create_display(SCREEN_W, SCREEN_H, ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
  Project *project = new Project(display);
  af::run_loop();
  return 0;
}


