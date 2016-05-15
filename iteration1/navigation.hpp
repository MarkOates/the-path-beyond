

class WorldNavigationGUINavView : public FGUIWidget
{
public:
  ALLEGRO_BITMAP *render;
  int mouse_x, mouse_y;

  WorldNavigationGUINavView(FGUIWidget *parent)
    : FGUIWidget(parent, new FGUISurfaceAreaBox(SCREEN_W/2, SCREEN_H/2, SCREEN_W, SCREEN_H))
    , render(NULL)
    , mouse_x(0)
    , mouse_y(0)
  {
    // initialize our rendering surface
    render = al_create_bitmap(place.size.x, place.size.y);

    ALLEGRO_STATE state;
    al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
    al_set_target_bitmap(render);
    al_clear_to_color(color::transparent);
    al_restore_state(&state);
  }
  void on_mouse_move(float x, float y, float dx, float dy) override
  {
    mouse_x = x;
    mouse_y = y;
  }
  void on_click() override
  {
    if (render)
    {
      if (mouse_x < 0 || mouse_x > al_get_bitmap_width(render)) return;
      if (mouse_y < 0 || mouse_y > al_get_bitmap_height(render)) return;
      if (Logging::at_least(L_VERBOSE)) std::cout << "sampling bitmap at " << mouse_x << ", " << mouse_y << std::endl;
      send_message_to_parent(tostring("clicked_on_id ") + tostring(decode_id(al_get_pixel(render, mouse_x, mouse_y))));
    }
  }
  void on_draw() override
  {
    al_draw_rectangle(0, 0, place.size.x, place.size.y, color::green, 8);
    al_draw_bitmap(render, 0, 0, 0);
  }
  void show()
  {
    af::motion.cmove_to(&place.scale.x, 1.0, 0);
  }
  void hide()
  {
    af::motion.cmove_to(&place.scale.x, 0.0, 0);
  }
};


class WorldNavigationGUINavButton : public FGUIWidget
{
public:
  TargetID target_id;
  float show_pos_y;

  WorldNavigationGUINavButton(FGUIWidget *parent, float x, float y, float w, float h)
    : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
    , target_id("")
    , show_pos_y(y)
  {}
  void set_target_id(TargetID target_id) { this->target_id = target_id; }
  void on_click() override { send_message_to_parent(target_id.get_trigger_message()); }
  void show(float speed=0.4)
  {
    af::motion.cmove_to(&place.position.y, show_pos_y, speed);
  }
  void hide(float speed=0.4)
  {
    af::motion.cmove_to(&place.position.y, -200, speed);
  }
  void show_if_has_target(float speed=0.4)
  {
    if (!target_id.is_empty()) show(speed);
  }
};


class WorldNavigationGUIScreen : public FGUIScreen
{
public:
  FGUIScreen *project_screen;

  WorldNavigationGUINavView *nav_view;
  WorldNavigationGUINavButton *nav_up_button;
  WorldNavigationGUINavButton *nav_down_button;
  WorldNavigationGUINavButton *nav_left_button;
  WorldNavigationGUINavButton *nav_right_button;

  WorldNavigationGUIScreen(FGUIScreen *project_screen, Display *display)
    : FGUIScreen(display)
    , project_screen(project_screen)
    , nav_view(NULL)
    , nav_up_button(NULL)
    , nav_down_button(NULL)
    , nav_left_button(NULL)
    , nav_right_button(NULL)
  {
    nav_view = new WorldNavigationGUINavView(this);
    nav_up_button = new WorldNavigationGUINavButton(this, SCREEN_W/2, 100, 300, 30);
    nav_down_button = new WorldNavigationGUINavButton(this, SCREEN_W/2, SCREEN_H-100, 300, 30);
    nav_left_button = new WorldNavigationGUINavButton(this, 100, SCREEN_H/2, 30, 300);
    nav_right_button = new WorldNavigationGUINavButton(this, SCREEN_W-100, SCREEN_H/2, 30, 300);
  }

  void on_message(FGUIWidget *sender, std::string message)
  {
    std::string trigger_id;
    if (TargetID::extract_trigger_id(message, &trigger_id))
    {
      if (Logging::at_least(L_VERBOSE)) std::cout << "WorldNavigationGUIScreen sending on_message for script \"" << trigger_id << "\"" << std::endl;
      project_screen->on_message(this, message);
    }
    else if (strncmp(message.c_str(), "clicked_on_id ", 14) == 0)
    {
      // we have a recieved trigger message
      std::string id_clicked_on = message.substr(14);
      std::cout << "clicked on id " << id_clicked_on << std::endl;
    }
  }
  void set_usability_mode(int mode)
  {
    if (Logging::at_least(L_VERBOSE)) std::cout << " === setting WorldNavigation mode " << mode << " ===" << std::endl;
    switch(mode)
    {
      case 0:
        nav_view->hide();
        nav_up_button->hide();
        nav_down_button->hide();
        nav_left_button->hide();
        nav_right_button->hide();
        break;
      case 1:
        nav_view->show();
        nav_up_button->show_if_has_target();
        nav_down_button->show_if_has_target();
        nav_left_button->show_if_has_target();
        nav_right_button->show_if_has_target();
        break;
      default:
        // Undefined Mode
        if (Logging::at_least(L_NORMAL))
          std::cout
            << CONSOLE_COLOR_YELLOW
            << "undefined InventoryGUIScreen mode " << mode
            << CONSOLE_COLOR_DEFAULT
            << std::endl;
        break;
    }
  }
};



