


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



std::string TargetID::get_trigger_message()
{
   return tostring("trigger_target_id ") + id;
}



bool TargetID::extract_script_name(std::string message, std::string *extracted_script_name)
{
   if (strncmp(message.c_str(), "trigger_target_id ", 18) == 0)
   {
      // we have a valid trigger message
      *extracted_script_name = message.substr(18);
      return true;
   }
   return false;
}



std::string TargetID::compose_trigger_script_id_message(int unique_id)
{
   return tostring("trigger_unique_target_id ") + tostring(unique_id);
}



bool TargetID::extract_script_id(std::string message, int *extracted_unique_id)
{
   if (strncmp(message.c_str(), "trigger_unique_target_id ", 25) == 0)
   {
      // we have a valid trigger message
      *extracted_unique_id = atoi(message.substr(25).c_str());
      return true;
   }
   return false;
}



int TargetID::color_to_id(ALLEGRO_COLOR color)
{
   return ColorIDConverter::decode_id(color);
}



ALLEGRO_COLOR TargetID::id_to_color(int id)
{
   return ColorIDConverter::encode_id(id);
}



