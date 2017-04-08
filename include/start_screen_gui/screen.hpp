#pragma once



#include <allegro_flare/gui/gui_screen.h>



class UIText;



namespace StartScreenGUI
{
   class Screen : public UIScreen
   {
   private:
     class StartScreenGUIStartButton : public UIWidget
     {
     public:
       StartScreenGUIStartButton(UIWidget *parent);
       void on_click() override;
       void on_draw() override;
     };

   public:
     UIScreen *project_screen;
     UIText *title_text;
     UIText *instructions;
     StartScreenGUIStartButton *start_screen_button;

     Screen(UIScreen *project_screen, Display *display);
     void on_message(UIWidget *sender, std::string message) override;
     void show(float speed=2.0);
     void hide(float speed=2.0);
   };
};



