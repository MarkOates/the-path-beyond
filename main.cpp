#include <allegro_flare/allegro_flare.h>
#include <cmath>

#include <global_constants.hpp>

#include <style_assets.hpp>
#include <logging.hpp>
#include <target_id.hpp>
#include <inventory_gui/screen.hpp>
#include <start_screen_gui/screen.hpp>
#include <world_render_screen.hpp>
#include <world_navigation_gui/screen.hpp>
#include <script.hpp>

#include "game/project.hpp"
#include "game/load_game_scripts.hpp"


////////////////////////////////////////////////////////////////


int main(int argc, char **argv)
{
  Framework::initialize();
  Display *display = Framework::create_display(SCREEN_W, SCREEN_H, ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
  Project *project = new Project(display);
  Framework::run_loop();
  return 0;
}


