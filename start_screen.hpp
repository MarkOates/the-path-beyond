


class StartScreenGUIScreen : public UIScreen
{
private:
  class StartScreenGUIStartButton : public UIWidget
  {
  public:
    StartScreenGUIStartButton(UIWidget *parent)
      : UIWidget(parent, "StartScreenGUIScreen::StartScreenGUIStartButton", new UISurfaceAreaBox(SCREEN_W/2, SCREEN_H/3*2, 240, 90))
    {}
    void on_click() override
    {
      if (Logging::at_least(L_NORMAL)) std::cout << "StartScreeGUIStartButton" << std::endl;
      send_message_to_parent(TargetID("StartGame()").get_trigger_message());
    }
    void on_draw() override
    {
      Style::draw_button(Style::NORMAL, place, "start");
    }
  };

public:
  UIScreen *project_screen;
  UIText *title_text;
  UIText *instructions;
  StartScreenGUIStartButton *start_screen_button;

  StartScreenGUIScreen(UIScreen *project_screen, Display *display)
    : UIScreen(display)
    , project_screen(project_screen)
    , title_text(NULL)
    , instructions(NULL)
    , start_screen_button(NULL)
  {
    title_text = new UIText(this, SCREEN_W/2, SCREEN_H/2, "- THE PATH -");
    title_text->set_font(Framework::font("space age.otf 100"));
    title_text->place.align.x = 0.5;

    start_screen_button = new StartScreenGUIStartButton(this);

    instructions = new UIText(this, SCREEN_W/2, SCREEN_H/2 + 60, "use only mouse clicks to play");
    instructions->set_font(Framework::font("space age.otf 40"));
    instructions->set_font_color(color::gray);
    instructions->place.align.x = 0.5;
  }
  void on_message(UIWidget *sender, std::string message) override
  {
    std::string trigger_id;
    if (TargetID::extract_trigger_id(message, &trigger_id)) project_screen->on_message(this, message); // bubbles it up
  }
  void show(float speed=2.0)
  {
    Framework::motion().cmove_to(&title_text->place.position.x, SCREEN_W/2, 1.0 * speed);
    Framework::motion().cmove_to(&start_screen_button->place.position.x, SCREEN_W/2, 1.0 * speed);
    Framework::motion().cmove_to(&title_text->place.scale.x, 1.05, 2.0 * speed);
    Framework::motion().cmove_to(&title_text->place.scale.y, 1.05, 2.0 * speed);
    instructions->place.scale.x = 1;
  }
  void hide(float speed=2.0)
  {
    Framework::motion().cmove_to(&title_text->place.position.x, -1000, 1.0 * speed);
    Framework::motion().cmove_to(&start_screen_button->place.position.x, SCREEN_W+200, 1.0 * speed);
    instructions->place.scale.x = 0;
  }
};



