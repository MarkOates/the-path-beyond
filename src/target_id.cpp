


#include <target_id.hpp>

#include <allegro_flare/converters/color_id_converter.h>
#include <allegro_flare/useful.h>
#include <allegro5/allegro_color.h>



TargetID::TargetID(std::string id)
   : id(id)
{}



bool TargetID::is_empty()
{
   return id == "";
}



int TargetID::color_to_id(ALLEGRO_COLOR color)
{
   return ColorIDConverter::decode_id(color);
}



ALLEGRO_COLOR TargetID::id_to_color(int id)
{
   return ColorIDConverter::encode_id(id);
}



