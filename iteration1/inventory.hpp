

class InventoryItem
{
public:
  enum Type
  {
    EMPTY = 0
  };

  Type type;

  InventoryItem(InventoryItem::Type type)
    : type(type)
  {}

  bool is_empty()
  {
    return type == EMPTY;
  }

  std::string get_name() { return std::string("Item ") + tostring(type); }
  std::string get_description() { return std::string("description for item ") + tostring(type); }
  ALLEGRO_BITMAP *get_image() { return NULL; }
};


class InventoryGUIInventoryToggleButton : public FGUIWidget
{
public:
  InventoryItem shown_item;

  InventoryGUIInventoryToggleButton(FGUIWidget *parent)
    : FGUIWidget(parent, new FGUISurfaceAreaBox(SCREEN_W-80, 60, 120, 80))
    , shown_item(InventoryItem::Type::EMPTY)
  {}
  void on_click()
  {
    std::cout << "InventoryGUIInventoryToggleButton" << std::endl;
    send_message_to_parent("toggle_visibility_mode()");
  }
  void set_shown_item(InventoryItem item)
  {
    shown_item = item;
  }
  void on_draw()
  {
    if (shown_item.is_empty())
    {
      al_draw_text(af::fonts["DroidSans.ttf 20"], color::white, place.size.x/2, place.size.y/2-14, ALLEGRO_ALIGN_CENTER, "Inventory");
    }
    else
    {
      BitmapObject image(shown_item.get_image());
      image.scale_to_fit(place.size.x, place.size.y);
      image.align(0.5, 0.5);
      image.position(place.size.x/2, place.size.y/2);
      image.draw();
    }

    FGUIWidget::on_draw();
  }
  void show(float speed=0.5)
  {
    std::cout << "InventoryGUIInventoryToggleButton.show()" << std::endl;
    af::motion.cmove_to(&place.position.x, SCREEN_W-80, speed);
  }
  void hide(float speed=0.5)
  {
    std::cout << "InventoryGUIInventoryToggleButton.hide()" << std::endl;
    af::motion.cmove_to(&place.position.x, SCREEN_W+60, speed);
  }
};


class InventoryGUIItemButton : public FGUIWidget
{
private:
  class GUICombineButton : public FGUIWidget
  {
  public:
    GUICombineButton(FGUIWidget *parent)
      : FGUIWidget(parent, new FGUISurfaceAreaBox(-30, parent->place.size.y/2, 40, 50))
    {}
    void on_click()
    {
      std::cout << "GUICombineButton.on_click()" << std::endl;
      send_message_to_parent("attempt_to_combine()");
    }
  };

public:
  InventoryItem item;
  int show_x_pos;
  bool selected;

  GUICombineButton *combine_button;

  InventoryGUIItemButton(FGUIWidget *parent, float x, float y)
    : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, 80, 80))
    , item(InventoryItem::Type::EMPTY)
    , show_x_pos(x)
    , selected(false)
    , combine_button(NULL)
  {
    combine_button = new GUICombineButton(this);
  }
  void set_item(InventoryItem item)
  {
    this->item = item;
  }
  bool is_empty()
  {
    return (item.type == InventoryItem::Type::EMPTY);
  }
  void on_click()
  {
    std::cout << "InventoryGUIItemButton" << std::endl;
    send_message_to_parent("feature_my_item()");
  }
  void select()
  {
    selected = true;
  }
  void deselect()
  {
    selected = false;
  }
  void on_message(FGUIWidget *sender, std::string message)
  {
    // message will always be attempt_to_combine()
    if (sender == combine_button) send_message_to_parent("attempt_to_combine()");
  }
  void on_draw()
  {
    FGUIWidget::on_draw();
    if (selected) al_draw_rounded_rectangle(0, 0, place.size.x, place.size.y, 5, 5, color::orange, 3.0);
  }
  void show(float speed=0.5)
  {
    std::cout << "InventoryGUIItemButton.show()" << std::endl;
    af::motion.cmove_to(&place.position.x, show_x_pos, speed);
  }
  void hide(float speed=0.5)
  {
    std::cout << "InventoryGUIItemButton.hide()" << std::endl;
    af::motion.cmove_to(&place.position.x, show_x_pos+200, speed);
  }
};


class InventoryGUICurrentItemShowcase : public FGUIWidget
{
public:
  InventoryItem item;
  FGUIImage *featured_image;
  FGUIText *title_text;
  FGUITextBox *description_textbox;

  InventoryGUICurrentItemShowcase(FGUIWidget *parent)
    : FGUIWidget(parent, new FGUISurfaceAreaBox(SCREEN_W-500, SCREEN_H/2, 600, 400))
    , item(InventoryItem::Type::EMPTY)
    , title_text(NULL)
    , description_textbox(NULL)
    , featured_image(NULL)
  {
    featured_image = new FGUIImage(this, place.size.x/2, place.size.y/2, item.get_image());
    title_text = new FGUIText(this, 0, 0, item.get_name());
    title_text->place.align.y = 0;
    description_textbox = new FGUITextBox(this, place.size.x/2, place.size.y*0.75, place.size.x*0.8, place.size.y*0.25, item.get_description()) ;
    description_textbox->set_text_color(color::white);
    description_textbox->place.align.x = 0.5;
    description_textbox->place.align.y = 0;
  }
  void set_item(InventoryItem item)
  {
    this->item = item;
    featured_image->set_bitmap(item.get_image());
    title_text->set_text(item.get_name());
    description_textbox->set_text(item.get_description());
  }
  void show(float speed=0.5)
  {
    std::cout << "InventoryGUICurrentItemShowcase.show()" << std::endl;
    af::motion.cmove_to(&place.position.x, SCREEN_W-500, speed);
  }
  void hide(float speed=0.5)
  {
    std::cout << "InventoryGUICurrentItemShowcase.hide()" << std::endl;
    af::motion.cmove_to(&place.position.x, SCREEN_W+500, speed);
  }
};


class InventoryGUIScreen : public FGUIScreen
{
public:
  const int NUM_INVENTORY_ITEM_BUTTONS;

  // MODE 1 Widget
  InventoryGUIInventoryToggleButton *toggle_button;

  // MODE 2 Widgets
  InventoryGUICurrentItemShowcase *current_item_showcase;
  std::vector<InventoryGUIItemButton *> item_buttons;

  int current_mode;

  InventoryGUIScreen(Display *display)
    : FGUIScreen(display)
    , NUM_INVENTORY_ITEM_BUTTONS(9)
    , toggle_button(NULL)
    , current_item_showcase(NULL)
    , item_buttons()
    , current_mode(1)
  {
    // create our Inventory GUI Widgets
    toggle_button = new InventoryGUIInventoryToggleButton(this);
    current_item_showcase = new InventoryGUICurrentItemShowcase(this);
    for (unsigned i=0; i<NUM_INVENTORY_ITEM_BUTTONS; i++)
    {
      InventoryGUIItemButton *button = new InventoryGUIItemButton(this, SCREEN_W-100, 200+90*i);
      item_buttons.push_back(button);
    }

    // set our current GUI mode
    set_visibility_mode(current_mode);
  }

  void on_message(FGUIWidget *sender, std::string message) override
  {
    if (message == "") return;
    else if (message == "toggle_visibility_mode()")
    {
      if (current_mode == 1) set_visibility_mode(2);
      else if (current_mode == 2) set_visibility_mode(1);
    }
    else if (message == "set_visibility_mode(0)") set_visibility_mode(0);
    else if (message == "set_visibility_mode(1)") set_visibility_mode(1);
    else if (message == "set_visibility_mode(2)") set_visibility_mode(2);
    else if (message == "feature_my_item()")
    {
      // deselect all the other buttons
      for (auto &item : item_buttons)
        if (item != sender) static_cast<InventoryGUIItemButton *>(item)->deselect();

      // set the item in the showcase
      InventoryGUIItemButton *button = static_cast<InventoryGUIItemButton *>(sender);
      current_item_showcase->set_item(button->item);
      button->select();

      // set the item in the inventory toggle button
      toggle_button->set_shown_item(button->item);
    }
  }

  InventoryGUIItemButton *find_first_empty_inventory_button()
  {
    for (auto &button : item_buttons) if (button->is_empty()) return button;
    return NULL;
  }

  bool add_item(InventoryItem item)
  {
    InventoryGUIItemButton *empty_button = find_first_empty_inventory_button();
    if (!empty_button) return false;
    empty_button->set_item(item);
    return true;
  }

  void set_visibility_mode(int mode)
  {
    std::cout << " === setting GUI mode " << mode << " ===" << std::endl;
    switch(mode)
    {
      case 0:
        toggle_button->hide();
        current_item_showcase->hide();
        for (auto &button : item_buttons) button->hide();
        current_mode = 0;
        break;
      case 1:
        toggle_button->show();
        current_item_showcase->hide();
        for (auto &button : item_buttons) button->hide();
        current_mode = 1;
        break;
      case 2:
        toggle_button->show();
        current_item_showcase->show();
        for (auto &button : item_buttons) button->show();
        current_mode = 2;
        break;
      default:
        // Undefined Mode
        std::cout << "undefined InventoryGUIScreen mode " << mode << std::endl;
        break;
    }
  }
};



