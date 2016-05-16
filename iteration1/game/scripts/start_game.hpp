

class StartGame: public Script, public ScriptHelper
{
public:
  StartGame() : Script("StartGame()") {}
  void activate() override
  {
    world_navigation_gui->set_usability_mode(1);
    inventory_gui->set_visibility_mode(1);
    start_screen_gui->hide(2.0);

    // clean up all the previous game's assets here
    // (hahahaha!)

    // load game assets
    Entity *e = new Entity(
        world_render->manager,
        "Station",
        af::models["space_station-04.obj"],
        af::bitmaps["floor_texture.jpeg"]);
        //af::bitmaps["uv.png"]);

    // create our triggerable entities
    Entity *entity = new Entity(world_render->manager,
        "Ring1",
        af::models["coin_ring-01.obj"],
        af::bitmaps["uv.png"]);
    entity->place.position = vec3d(-4, 2, 0);

    // create the card key
    create_entity("CardKey", vec3d(5, 0, 4), 0.4, "card_key-02.obj", "sci_fi_panel2.jpg");

    // create the card key decrypter
    create_entity("CardKeyDecrypter", vec3d(-2, 0, 3), 0.3, "card_key_decrypter-02.obj", "tech_device_texture.jpg");

    // goto the starting point
    Script::run("goto1");
  }
};


