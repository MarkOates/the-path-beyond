


class StartScreenGUIScreen : public FGUIScreen
{
private:
  class StartScreenGUIStartButton : public FGUIWidget
  {
  public:
    StartScreenGUIStartButton(FGUIWidget *parent)
      : FGUIWidget(parent, new FGUISurfaceAreaBox(SCREEN_W/2, SCREEN_H/3*2, 200, 90))
    {}
    void on_click() override
    {
      send_message_to_parent("start_game_please()");
      std::cout << "StartScreeGUIStartButton" << std::endl;
    }
  };

public:
  FGUIScreen *project_screen;
  FGUIText *title_text;
  StartScreenGUIStartButton *start_screen_button;

  StartScreenGUIScreen(FGUIScreen *project_screen, Display *display)
    : FGUIScreen(display)
    , project_screen(project_screen)
    , title_text(NULL)
    , start_screen_button(NULL)
  {
    title_text = new FGUIText(this, SCREEN_W/2, SCREEN_H/3, "- THE PATH -");
    title_text->place.align.x = 0.5;
    start_screen_button = new StartScreenGUIStartButton(this);
  }
  void on_message(FGUIWidget *sender, std::string message) override
  {
    if (message == "start_game_please()") project_screen->on_message(this, message); // bubbles it up
  }
  void show(float speed=2.0)
  {
    af::motion.cmove_to(&title_text->place.position.x, SCREEN_W/2, 1.0 * speed);
    af::motion.cmove_to(&start_screen_button->place.position.x, SCREEN_W/2, 1.0 * speed);
  }
  void hide(float speed=2.0)
  {
    af::motion.cmove_to(&title_text->place.position.x, -100, 1.0 * speed);
    af::motion.cmove_to(&start_screen_button->place.position.x, SCREEN_W+200, 1.0 * speed);
  }
};



