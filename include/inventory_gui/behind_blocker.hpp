#pragma once



#include <allegro_flare/gui/widget.h>



class InventoryGUIBehindBlocker : public UIWidget
{
public:
  InventoryGUIBehindBlocker(UIWidget *parent);

  void on_click() override;
  void on_draw() override;
  void show();
  void hide();
};



