


#include <world_navigation_gui/nav_button.hpp>

#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/framework.h>
#include <allegro_flare/user_event_emitter.h>
#include <global_constants.hpp>
#include <style_assets.hpp>
#include <script_collection.hpp>
#include <script.hpp>



WorldNavigationGUI::NavButton::NavButton(UIWidget *parent, float x, float y, float w, float h)
   : UIWidget(parent, "WorldNavigationGUI::NavButton", new UISurfaceAreaBox(x, y, w, h))
   , script_name("")
   , show_pos_y(y)
{}



void WorldNavigationGUI::NavButton::set_script_by_name(std::string script_name)
{
   this->script_name = script_name;
}



void WorldNavigationGUI::NavButton::on_click()
{
   Script *found_script = ScriptCollection::find_by_name(script_name);
   if (found_script) UserEventEmitter::emit_event(RUN_SCRIPT_EVENT, found_script->get_id());
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
   if (!script_name.empty()) show(speed);
}



