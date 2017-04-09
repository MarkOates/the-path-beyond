


#include <inventory_gui/notification.hpp>

#include <allegro_flare/gui/surface_areas/box.h>
#include <global_constants.hpp>
#include <style_assets.hpp>



InventoryGUI::Notification::Notification(UIWidget *parent)
   : UIWidget(parent, "InventoryGUI::Notification", new UISurfaceAreaBox(SCREEN_W/2, SCREEN_H/4*3, 900, 100))
   , visibility_timer(-1)
{
}



void InventoryGUI::Notification::on_timer()
{
   visibility_timer -= 1.0/60.0;
   if (visibility_timer < 0) visibility_timer = -1.0;
}



void InventoryGUI::Notification::mouse_down_func()
{
   UIWidget::mouse_down_func();
   visibility_timer = -1.0;
}



void InventoryGUI::Notification::on_draw()
{
   if (visibility_timer < 0) return;
   StyleAssets::draw_button(StyleAssets::NORMAL, 0, 0, place.size.x, place.size.y, notification_text);
}



void InventoryGUI::Notification::show(std::string text)
{
   notification_text = text;
   visibility_timer = 5.0;
}



