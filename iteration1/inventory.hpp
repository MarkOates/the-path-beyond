

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

  std::string get_name() { return std::string("Item ") + tostring(type); }
  std::string get_description() { return std::string("description for item ") + tostring(type); }
  ALLEGRO_BITMAP *get_image() { return NULL; }
};


class InventoryGUIInventoryToggleButton : public FGUIWidget
{
public:
  InventoryGUIInventoryToggleButton(FGUIWidget *parent)
    : FGUIWidget(parent, new FGUISurfaceAreaBox(SCREEN_W-80, 60, 120, 80))
  {}
  void on_click()
  {
    std::cout << "InventoryGUIInventoryToggleButton" << std::endl;
    send_message_to_parent("toggle_mode()");
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


class InventoryGUICurrentItemShowcase : public FGUIWidget
{
public:
  InventoryGUICurrentItemShowcase(FGUIWidget *parent)
    : FGUIWidget(parent, new FGUISurfaceAreaBox(SCREEN_W-500, SCREEN_H/2, 600, 400))
  {}
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


class InventoryGUIItemButton : public FGUIWidget
{
public:
  InventoryItem item;
  int show_x_pos;

  InventoryGUIItemButton(FGUIWidget *parent, float x, float y)
    : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, 80, 80))
    , item(InventoryItem::Type::EMPTY)
    , show_x_pos(x)
  {}
  void on_click()
  {
    std::cout << "InventoryGUIItemButton" << std::endl;
  }
  void show(float speed=0.5)
  {
    std::cout << "InventoryGUIItemButton.show()" << std::endl;
    af::motion.cmove_to(&place.position.x, show_x_pos, speed);
  }
  void hide(float speed=0.5)
  {
    std::cout << "InventoryGUIItemButton.hide()" << std::endl;
    af::motion.cmove_to(&place.position.x, show_x_pos+150, speed);
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

  std::vector<InventoryItem> items;
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
    set_mode(current_mode);
  }

  void on_message(FGUIWidget *sender, std::string message) override
  {
    if (message == "") return;
    else if (message == "toggle_mode()")
    {
      if (current_mode == 1) set_mode(2);
      else if (current_mode == 2) set_mode(1);
    }
    else if (message == "set_mode(0)") set_mode(0);
    else if (message == "set_mode(1)") set_mode(1);
    else if (message == "set_mode(2)") set_mode(2);
  }

  void set_mode(int mode)
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



