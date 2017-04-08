#pragma once



#include <string>

#include <allegro5/allegro.h>
#include <allegro_flare/placement2d.h>



namespace Style
{
   enum BUTTON_STATE
   {
      NORMAL = 0,
      SELECTED,
      ERROR,
   };

   ALLEGRO_COLOR get_state_color(BUTTON_STATE state);

   void draw_button(BUTTON_STATE state, float x, float y, float w, float h, std::string text="", ALLEGRO_BITMAP *bitmap=NULL);

   void draw_text_box(float x, float y, float w, float h, std::string text="");

   void draw_button(BUTTON_STATE state, const placement2d &place, std::string text="", ALLEGRO_BITMAP *bitmap=NULL);
};



