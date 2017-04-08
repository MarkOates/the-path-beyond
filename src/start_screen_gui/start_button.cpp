


#include <start_screen_gui/start_button.hpp>

#include <allegro_flare/gui/surface_areas/box.h>
#include <global_constants.hpp>
#include <logging.hpp>
#include <style_assets.hpp>
#include <target_id.hpp>



StartScreenGUI::StartButton::StartButton(UIWidget *parent)
   : UIWidget(parent, "StartScreenGUI::StartButton", new UISurfaceAreaBox(SCREEN_W/2, SCREEN_H/3*2, 240, 90))
{}



void StartScreenGUI::StartButton::on_click()
{
   if (Logging::at_least(L_NORMAL)) std::cout << "StartScreeGUI::StartButton" << std::endl;
   send_message_to_parent(TargetID("StartGame()").get_trigger_message());
}



void StartScreenGUI::StartButton::on_draw()
{
   Style::draw_button(Style::NORMAL, place, "start");
}




