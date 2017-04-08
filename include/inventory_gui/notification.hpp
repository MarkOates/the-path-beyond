#pragma once



#include <string>

#include <allegro_flare/gui/widget.h>



namespace InventoryGUI
{
   class Notification : public UIWidget
   {
   public:
     std::string notification_text;
     float visibility_timer;

     Notification(UIWidget *parent);
     void on_timer() override;
     void mouse_down_func() override;
     void on_draw() override;
     void show(std::string text);
   };
}



