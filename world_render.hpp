#include <entity.hpp>


class WorldRenderScreen : public Screen
{
private:
  void primary_timer_func() override
  {
    update_scene();
    if (scene_targets_render_surface_ref) draw_scene_targets(scene_targets_render_surface_ref);
    draw_scene();
  }

  void set_projection(ALLEGRO_BITMAP *bitmap, ALLEGRO_TRANSFORM *t)
  {
    float aspect_ratio = (float)al_get_bitmap_height(bitmap) / al_get_bitmap_width(bitmap);
    al_perspective_transform(t, -1, aspect_ratio, 1, 1, -aspect_ratio, 100);
    al_use_projection_transform(t);
  }

public:
  ElementID *manager;
  Entity *camera;

  ALLEGRO_BITMAP *scene_targets_render_surface_ref;

  WorldRenderScreen(Display *display)
    : Screen(display)
    , manager(new ElementID(nullptr))
    , camera(NULL)
    , scene_targets_render_surface_ref(NULL)
  {
    // create the camera
    camera = new Entity(manager, "Camera", NULL, NULL);
  }

  void set_scene_targets_render_surface(ALLEGRO_BITMAP *surface)
  {
    scene_targets_render_surface_ref = surface;
  }

  void update_scene()
  {
    for (auto &elem : manager->get_children())
    {
      Entity *entity = static_cast<Entity *>(elem);
      entity->place += entity->velocity;
    }
  }

  void prep_render(ALLEGRO_BITMAP *surface, placement3d &camera_view)
  {
    // setup the render settings
    al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
    al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
    al_clear_depth_buffer(1);

    ALLEGRO_TRANSFORM t;
    camera_view.build_reverse_transform(&t);
    set_projection(surface, &t);
  }

  void draw_scene()
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

  void draw_scene_targets(ALLEGRO_BITMAP *surface)
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
};



