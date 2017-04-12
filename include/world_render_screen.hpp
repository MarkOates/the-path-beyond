#pragma once



#include <allegro_flare/screen.h>
#include <allegro_flare/placement3d.h>



class ElementID;
class Entity;



class WorldRenderScreen : public Screen
{
private:
   void primary_timer_func() override;
   void set_projection(ALLEGRO_BITMAP *bitmap, ALLEGRO_TRANSFORM *t);

public:
   ElementID *manager;
   Entity *camera;
   Entity *light_1;

   ALLEGRO_BITMAP *scene_targets_render_surface_ref;

   WorldRenderScreen(Display *display);

   void set_scene_targets_render_surface(ALLEGRO_BITMAP *surface);
   void update_scene();
   void prep_render(ALLEGRO_BITMAP *surface, placement3d &camera_view);
   void draw_scene();
   void draw_scene_targets(ALLEGRO_BITMAP *surface);
};



