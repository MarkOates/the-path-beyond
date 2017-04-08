


#include <world_navigation_gui/nav_button.hpp>

#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/framework.h>
#include <style_assets.hpp>



WorldNavigationGUINavButton::WorldNavigationGUINavButton(UIWidget *parent, float x, float y, float w, float h)
   : UIWidget(parent, "WorldNavigationGUINavButton", new UISurfaceAreaBox(x, y, w, h))
   , target_id("")
   , show_pos_y(y)
{}



void WorldNavigationGUINavButton::set_target_id(TargetID target_id)
{
   this->target_id = target_id;
}



void WorldNavigationGUINavButton::on_click()
{
   send_message_to_parent(target_id.get_trigger_message());
}



void WorldNavigationGUINavButton::on_draw()
{
   Style::draw_button(Style::NORMAL, place, "•");
}



void WorldNavigationGUINavButton::show(float speed)
{
   Framework::motion().cmove_to(&place.position.y, show_pos_y, speed);
}



void WorldNavigationGUINavButton::hide(float speed)
{
   Framework::motion().cmove_to(&place.position.y, -200, speed);
}



void WorldNavigationGUINavButton::show_if_has_target(float speed)
{
   if (!target_id.is_empty()) show(speed);
}



