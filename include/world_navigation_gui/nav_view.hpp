#pragma once



#include <allegro_flare/gui/widget.h>
#include <allegro5/allegro.h>



class WorldNavigationGUINavView : public UIWidget
{
public:
  ALLEGRO_BITMAP *render;
  int mouse_x, mouse_y;

  WorldNavigationGUINavView(UIWidget *parent);
  void on_mouse_move(float x, float y, float dx, float dy) override;
  void on_click() override;
  void on_draw() override;
  void show();
  void hide();
};




