#pragma once



#include <allegro_flare/gui/widget.h>

#include <inventory_item.hpp>



class InventoryGUIItemButton : public UIWidget
{
private:
  class GUICombineButton : public UIWidget
  {
  public:
    GUICombineButton(UIWidget *parent);
    void on_click() override;
    void on_draw() override;
  };

public:
  InventoryItem item;
  int show_x_pos;
  bool selected;

  GUICombineButton *combine_button;

  InventoryGUIItemButton(UIWidget *parent, float x, float y);

  void set_item(InventoryItem item);
  void clear_item();
  bool is_empty();
  void on_click();
  void select();
  void deselect();
  void on_message(UIWidget *sender, std::string message);
  void on_draw();
  void show(float speed=0.5);
  void hide(float speed=0.5);
};



