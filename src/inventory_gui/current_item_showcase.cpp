


#include <inventory_gui/current_item_showcase.hpp>

#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/framework.h>
#include <global_constants.hpp>
#include <style_assets.hpp>
#include <logging.hpp>



InventoryGUI::CurrentItemShowcase::CurrentItemShowcase(UIWidget *parent)
   : UIWidget(parent, "InventoryGUI::CurrentItemShowcase", new UISurfaceAreaBox(SCREEN_W-500, SCREEN_H/2, 600, 400))
   , item(InventoryItem::Type::EMPTY)
   , title_text(NULL)
   , description_textbox(NULL)
     , featured_image(NULL)
{
   featured_image = new UIImage(this, place.size.x/2, place.size.y/2, item.get_image());
   title_text = new UIText(this, 20, 20, item.get_name());
   title_text->place.align.y = 0;
   title_text->set_font(Framework::font("space age.otf 34"));
   description_textbox = new UITextBox(this, place.size.x/2, place.size.y*0.75, place.size.x*0.8, place.size.y*0.25, item.get_description()) ;
   description_textbox->set_text_color(color::black);
   description_textbox->place.align.x = 0.5;
   description_textbox->place.align.y = 0;
}



void InventoryGUI::CurrentItemShowcase::on_draw()
{
   Style::draw_button(Style::NORMAL, place, item.is_empty() ? "- EMPTY -" : "");
}



void InventoryGUI::CurrentItemShowcase::set_item(InventoryItem item)
{
   this->item = item;
   featured_image->set_bitmap(item.get_image());
   title_text->set_text(item.get_name());
   description_textbox->set_text(item.get_description());
}



void InventoryGUI::CurrentItemShowcase::show(float speed)
{
   if (Logging::at_least(L_VERBOSE)) std::cout << "InventoryGUI::CurrentItemShowcase.show()" << std::endl;
   Framework::motion().cmove_to(&place.position.x, SCREEN_W-500, speed);
}



void InventoryGUI::CurrentItemShowcase::hide(float speed)
{
   if (Logging::at_least(L_VERBOSE)) std::cout << "InventoryGUI::CurrentItemShowcase.hide()" << std::endl;
   Framework::motion().cmove_to(&place.position.x, SCREEN_W+500, speed);
}



