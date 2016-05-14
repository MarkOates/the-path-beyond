
#include <allegro_flare/allegro_flare.h>

#define SCREEN_W 1920
#define SCREEN_H 1080

#include "target_id.hpp"
#include "inventory.hpp"
#include "start_screen.hpp"
#include "navigation.hpp"
#include "script.hpp"

#include "game/scripts/start_title_screen.hpp"
#include "game/scripts/start_game.hpp"



////////////////////////////////////////////////////////////////


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

  void draw_scene()
  {
    // setup the render settings
    al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
    al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
    al_clear_depth_buffer(1);

    ALLEGRO_TRANSFORM t;
    camera->place.build_reverse_transform(&t);
    set_projection(backbuffer_sub_bitmap, &t);

    // draw our entities
    for (auto &elem : manager->elements)
    {
      Entity *entity = static_cast<Entity *>(elem);
      entity->draw();
    }
  }
};




////////////////////////////////////////////////////////////////



class Project : public FGUIScreen
{
public:
  WorldNavigationGUIScreen *world_navigation_gui;
  InventoryGUIScreen *inventory_gui;
  StartScreenGUIScreen *start_screen_gui;

  Project(Display *display)
    : FGUIScreen(display)
    , world_navigation_gui(new WorldNavigationGUIScreen(this, display))
    , inventory_gui(new InventoryGUIScreen(display))
    , start_screen_gui(new StartScreenGUIScreen(this, display))
  {
    Script::initialize(world_navigation_gui, inventory_gui, start_screen_gui);
    load_scripts();

    Script::run("StartTitleScreen()");
  }
  void on_message(FGUIWidget *sender, std::string message)
  {
    std::string trigger_id;
    if (TargetID::extract_trigger_id(message, &trigger_id))
    {
      std::cout << "Project running script \"" << trigger_id << "\"" << std::endl;
      Script::run(trigger_id);
    }
  }
  void load_scripts()
  {
    // load the individual scripts
    new StartTitleScreen();
    new StartGame();
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


