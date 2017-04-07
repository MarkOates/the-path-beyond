#pragma once



#include <string>

#include <allegro_flare/gui/widget.h>



class InventoryGUINotification : public UIWidget
{
public:
  std::string notification_text;
  float visibility_timer;

  InventoryGUINotification(UIWidget *parent);
  void on_timer() override;
  void mouse_down_func() override;
  void on_draw() override;
  void show(std::string text);
};



