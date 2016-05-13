
#include <allegro_flare/allegro_flare.h>




class InventoryItem
{
public:
  std::string name;
  std::string description;
  ALLEGRO_BITMAP *image;

  InventoryItem(std::string name, std::string description, ALLEGRO_BITMAP *image)
    : name(name)
    , description(description)
    , image(image)
  {}
};


class InventoryGUIInventoryToggleButton : public FGUIWidget
{
public:
  InventoryGUIInventoryToggleButton(FGUIWidget *parent)
    : FGUIWidget(parent, new FGUISurfaceAreaBox(740, 60, 100, 80))
  {}
  void on_click()
  {
    std::cout << "InventoryGUIInventoryToggleButton" << std::endl;
    send_message_to_parent("set_mode(1)");
  }
  void show() { std::cout << "InventoryGUIInventoryToggleButton.show()" << std::endl; }
  void hide() { std::cout << "InventoryGUIInventoryToggleButton.hide()" << std::endl; }
};


class InventoryGUICurrentItemShowcase : public FGUIWidget
{
public:
  InventoryGUICurrentItemShowcase(FGUIWidget *parent)
    : FGUIWidget(parent, new FGUISurfaceAreaBox(400, 300, 600, 400))
  {}
  void show() { std::cout << "InventoryGUICurrentItemShowcase.show()" << std::endl; }
  void hide() { std::cout << "InventoryGUICurrentItemShowcase.hide()" << std::endl; }
};


class InventoryGUIItemButton : public FGUIWidget
{
public:
  InventoryItem *item;

  InventoryGUIItemButton(FGUIWidget *parent, float x, float y)
    : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, 80, 80))
    , item(NULL)
  {}
  void on_click()
  {
    std::cout << "InventoryGUIItemButton" << std::endl;
  }
  void show() { std::cout << "InventoryGUIItemButton.show()" << std::endl; }
  void hide() { std::cout << "InventoryGUIItemButton.hide()" << std::endl; }
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

  std::vector<InventoryItem *> items;
  int current_mode;

  InventoryGUIScreen(Display *display)
    : FGUIScreen(display)
    , NUM_INVENTORY_ITEM_BUTTONS(9)
    , toggle_button(NULL)
    , current_item_showcase(NULL)
    , item_buttons()
  {
    // create our Inventory GUI Widgets
    toggle_button = new InventoryGUIInventoryToggleButton(this);
    current_item_showcase = new InventoryGUICurrentItemShowcase(this);
    for (unsigned i=0; i<NUM_INVENTORY_ITEM_BUTTONS; i++)
    {
      InventoryGUIItemButton *button = new InventoryGUIItemButton(this, 700, 150+90*i);
      item_buttons.push_back(button);
    }
  }

  void on_message(FGUIWidget *sender, std::string message) override
  {
    if (message == "") return;
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
        break;
      case 1:
        toggle_button->show();
        current_item_showcase->hide();
        for (auto &button : item_buttons) button->hide();
        break;
      case 2:
        toggle_button->show();
        current_item_showcase->show();
        for (auto &button : item_buttons) button->show();
        break;
      default:
        // Undefined Mode
        std::cout << "undefined InventoryGUIScreen mode " << mode << std::endl;
        break;
    }
  }
};



////////////////////////////////////////////////////////////////



class Project : public FGUIScreen
{
public:
  InventoryGUIScreen *inventory_screen;

  Project(Display *display)
    : FGUIScreen(display)
    , inventory_screen(new InventoryGUIScreen(display))
  {}
};


int main(int argc, char **argv)
{
  af::initialize();
  Display *display = af::create_display(800, 600, ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
  Project *project = new Project(display);
  af::run_loop();
  return 0;
}


