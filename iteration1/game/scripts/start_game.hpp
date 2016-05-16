

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
        af::models["space_station-01.obj"],
        af::bitmaps["uv.png"]);

    Script::run("goto1");
  }
};


