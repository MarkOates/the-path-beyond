#pragma once



#include <allegro_flare/gui/widgets/image.h>
#include <allegro_flare/gui/widgets/text.h>
#include <allegro_flare/gui/widgets/text_box.h>
#include <allegro_flare/gui/widget.h>
#include <inventory_item.hpp>



namespace InventoryGUI
{
   class CurrentItemShowcase : public UIWidget
   {
   public:
     InventoryItem item;
     UIImage *featured_image;
     UIText *title_text;
     UITextBox *description_textbox;

     CurrentItemShowcase(UIWidget *parent);

     void on_draw() override;
     void set_item(InventoryItem item);
     void show(float speed=0.5);
     void hide(float speed=0.5);
   };
}



