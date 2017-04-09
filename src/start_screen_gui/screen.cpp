


#include <start_screen_gui/screen.hpp>

#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/gui/widgets/text.h>
#include <allegro_flare/framework.h>
#include <global_constants.hpp>
#include <logging.hpp>
#include <style_assets.hpp>



StartScreenGUI::Screen::Screen(UIScreen *project_screen, Display *display)
   : UIScreen(display)
   , project_screen(project_screen)
   , title_text(NULL)
   , instructions(NULL)
   , start_screen_button(NULL)
{
   title_text = new UIText(this, SCREEN_W/2, SCREEN_H/2, "- THE PATH -");
   title_text->set_font(Framework::font("space age.otf 100"));
   title_text->place.align.x = 0.5;

   start_screen_button = new StartScreenGUI::StartButton(this);

   instructions = new UIText(this, SCREEN_W/2, SCREEN_H/2 + 60, "use only mouse clicks to play");
   instructions->set_font(Framework::font("space age.otf 40"));
   instructions->set_font_color(color::gray);
   instructions->place.align.x = 0.5;
}



void StartScreenGUI::Screen::show(float speed)
{
   Framework::motion().cmove_to(&title_text->place.position.x, SCREEN_W/2, 1.0 * speed);
   Framework::motion().cmove_to(&start_screen_button->place.position.x, SCREEN_W/2, 1.0 * speed);
   Framework::motion().cmove_to(&title_text->place.scale.x, 1.05, 2.0 * speed);
   Framework::motion().cmove_to(&title_text->place.scale.y, 1.05, 2.0 * speed);
   instructions->place.scale.x = 1;
}



void StartScreenGUI::Screen::hide(float speed)
{
   Framework::motion().cmove_to(&title_text->place.position.x, -1000, 1.0 * speed);
   Framework::motion().cmove_to(&start_screen_button->place.position.x, SCREEN_W+200, 1.0 * speed);
   instructions->place.scale.x = 0;
}



