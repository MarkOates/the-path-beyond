


class Entity : public ElementID
{
public:
  placement3d place;
  placement3d velocity;
  ModelNew *model;
  ALLEGRO_BITMAP *texture;

  Entity(ElementIDManager *manager, std::string id, ModelNew *model=NULL, ALLEGRO_BITMAP *texture=NULL)
    : ElementID(manager)
    , place()
    , velocity()
    , model(model)
    , texture(texture)
  {
    set_id(id);
    velocity.align = vec3d(0, 0, 0);
    velocity.scale = vec3d(0, 0, 0);
  }

  void draw()
  {
    if (!model) return;
    if (texture) model->set_texture(texture);

    place.start_transform();
    model->draw();
    place.restore_transform();
  }
};



class WorldRenderScreen : public Screen
{
private:
  void primary_timer_func() override
  {
    update_scene();
    draw_scene();
  }

  void set_projection(ALLEGRO_BITMAP *bitmap, ALLEGRO_TRANSFORM *t)
  {
    float aspect_ratio = (float)al_get_bitmap_height(bitmap) / al_get_bitmap_width(bitmap);
    al_perspective_transform(t, -1, aspect_ratio, 1, 1, -aspect_ratio, 100);
    al_use_projection_transform(t);
  }

public:
  ElementIDManager *manager;
  Entity *camera;

  WorldRenderScreen(Display *display)
    : Screen(display)
    , manager(new ElementIDManager())
    , camera(NULL)
  {
    // create the camera
    camera = new Entity(manager, "Camera", NULL, NULL);
  }

  void update_scene()
  {
    for (auto &elem : manager->elements)
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
    prep_render(backbuffer_sub_bitmap, camera->place);

    // draw our entities
    for (auto &elem : manager->elements)
    {
      Entity *entity = static_cast<Entity *>(elem);
      entity->draw();
    }
  }
};





