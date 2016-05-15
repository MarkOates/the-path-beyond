

class StartTitleScreen: public Script, public ScriptHelper
{
public:
  StartTitleScreen() : Script("StartTitleScreen()") {}
  void activate() override
  {
    world_navigation_gui->set_usability_mode(0);
    inventory_gui->set_visibility_mode(0);
    start_screen_gui->hide(0);
    start_screen_gui->show(8.0);
  }
};


