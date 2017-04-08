


#define ALLEGRO_UNSTABLE

#include <world_navigation_gui/nav_view.hpp>

#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/framework.h>
#include <allegro5/allegro_primitives.h>
#include <global_constants.hpp>
#include <logging.hpp>
#include <target_id.hpp>



WorldNavigationGUINavView::WorldNavigationGUINavView(UIWidget *parent)
   : UIWidget(parent, "WorldNavigationGUINavView", new UISurfaceAreaBox(SCREEN_W/2, SCREEN_H/2, SCREEN_W, SCREEN_H))
   , render(NULL)
   , mouse_x(0)
   , mouse_y(0)
{
   // initialize our rendering surface
   al_set_new_bitmap_depth(32);
   render = al_create_bitmap(place.size.x, place.size.y);
   al_set_new_bitmap_depth(0);

   ALLEGRO_STATE state;
   al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
   al_set_target_bitmap(render);
   al_clear_to_color(color::transparent);
   al_restore_state(&state);
}



void WorldNavigationGUINavView::on_mouse_move(float x, float y, float dx, float dy)
{
   mouse_x = x;
   mouse_y = y;
}



void WorldNavigationGUINavView::on_click()
{
   if (render)
   {
      if (mouse_x < 0 || mouse_x > al_get_bitmap_width(render)) return;
      if (mouse_y < 0 || mouse_y > al_get_bitmap_height(render)) return;
      if (Logging::at_least(L_VERBOSE)) std::cout << "sampling bitmap at " << mouse_x << ", " << mouse_y << std::endl;

      int clicked_id = decode_id(al_get_pixel(render, mouse_x, mouse_y));
      send_message_to_parent(TargetID::compose_unique_trigger_id_message(clicked_id));
   }
}



void WorldNavigationGUINavView::on_draw()
{
   al_draw_rectangle(0, 0, place.size.x, place.size.y, color::green, 8);
   al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, color::mix(color::red, color::transparent, 0.4));
   al_draw_bitmap(render, 0, 0, 0);
}



void WorldNavigationGUINavView::show()
{
   Framework::motion().cmove_to(&place.scale.x, 1.0, 0);
}



void WorldNavigationGUINavView::hide()
{
   Framework::motion().cmove_to(&place.scale.x, 0.0, 0);
}



