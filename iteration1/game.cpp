
#include <allegro_flare/allegro_flare.h>


class Project : public FGUIScreen
{
public:
  Project(Display *display)
    : FGUIScreen(display)
  {}
  void primary_timer_func() override
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


