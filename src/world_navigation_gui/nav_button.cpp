


#include <world_navigation_gui/nav_button.hpp>

#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/framework.h>
#include <style_assets.hpp>



WorldNavigationGUI::NavButton::NavButton(UIWidget *parent, float x, float y, float w, float h)
   : UIWidget(parent, "WorldNavigationGUI::NavButton", new UISurfaceAreaBox(x, y, w, h))
   , target_id("")
   , show_pos_y(y)
{}



void WorldNavigationGUI::NavButton::set_target_id(TargetID target_id)
{
   this->target_id = target_id;
}



void WorldNavigationGUI::NavButton::on_click()
{
   send_message_to_parent(target_id.get_trigger_message());
}



void WorldNavigationGUI::NavButton::on_draw()
{
   StyleAssets::draw_button(StyleAssets::NORMAL, place, "•");
}



void WorldNavigationGUI::NavButton::show(float speed)
{
   Framework::motion().cmove_to(&place.position.y, show_pos_y, speed);
}



void WorldNavigationGUI::NavButton::hide(float speed)
{
   Framework::motion().cmove_to(&place.position.y, -200, speed);
}



void WorldNavigationGUI::NavButton::show_if_has_target(float speed)
{
   if (!target_id.is_empty()) show(speed);
}



