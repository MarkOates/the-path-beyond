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
   std::string get_trigger_message();
   static bool extract_trigger_id(std::string message, std::string *extracted_id);
   static std::string compose_unique_trigger_id_message(int unique_id);
   static bool extract_unique_trigger_id(std::string message, int *extracted_unique_id);
};



