#pragma once



#include <string>
#include <allegro5/allegro.h>



class TargetID
{
public:
   std::string id;

   TargetID(std::string id);

   bool is_empty();
   static int color_to_id(ALLEGRO_COLOR color);
   static ALLEGRO_COLOR id_to_color(int id);
};



