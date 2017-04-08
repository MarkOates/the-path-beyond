


#include <world_render_screen.hpp>

#include <allegro_flare/color.h>
#include <allegro_flare/element_id.h>
#include <entity.hpp>
#include <target_id.hpp>



void WorldRenderScreen::primary_timer_func()
{
   update_scene();
   if (scene_targets_render_surface_ref) draw_scene_targets(scene_targets_render_surface_ref);
   draw_scene();
}



void WorldRenderScreen::set_projection(ALLEGRO_BITMAP *bitmap, ALLEGRO_TRANSFORM *t)
{
   float aspect_ratio = (float)al_get_bitmap_height(bitmap) / al_get_bitmap_width(bitmap);
   al_perspective_transform(t, -1, aspect_ratio, 1, 1, -aspect_ratio, 100);
   al_use_projection_transform(t);
}



WorldRenderScreen::WorldRenderScreen(Display *display)
   : Screen(display)
   , manager(new ElementID(nullptr))
   , camera(NULL)
   , scene_targets_render_surface_ref(NULL)
{
   // create the camera
   camera = new Entity(manager, "Camera", NULL, NULL);
}



void WorldRenderScreen::set_scene_targets_render_surface(ALLEGRO_BITMAP *surface)
{
   scene_targets_render_surface_ref = surface;
}



void WorldRenderScreen::update_scene()
{
   for (auto &elem : manager->get_children())
   {
      Entity *entity = static_cast<Entity *>(elem);
      entity->place += entity->velocity;
   }
}



void WorldRenderScreen::prep_render(ALLEGRO_BITMAP *surface, placement3d &camera_view)
{
   // setup the render settings
   al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
   al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
   al_clear_depth_buffer(1);

   ALLEGRO_TRANSFORM t;
   camera_view.build_reverse_transform(&t);
   set_projection(surface, &t);
}



void WorldRenderScreen::draw_scene()
{
   al_clear_to_color(color::black);
   prep_render(backbuffer_sub_bitmap, camera->place);

   // draw our entities
   for (auto &elem : manager->get_children())
   {
      Entity *entity = static_cast<Entity *>(elem);
      entity->draw();
   }
}



void WorldRenderScreen::draw_scene_targets(ALLEGRO_BITMAP *surface)
{
   ALLEGRO_STATE state;
   al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
   al_set_target_bitmap(surface);

   prep_render(surface, camera->place);
   al_clear_to_color(color::transparent);

   // draw our entities
   for (auto &elem : manager->get_children())
   {
      Entity *entity = static_cast<Entity *>(elem);
      entity->draw_flat_color(encode_id(entity->get_attached_script_id()));
   }

   al_restore_state(&state);
}



