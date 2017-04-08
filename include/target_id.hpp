#pragma once



#include <string>
#include <allegro5/allegro.h>



ALLEGRO_COLOR encode_id(int id);
int decode_id(ALLEGRO_COLOR color);


class TargetID
{
public:
   std::string id;

   TargetID(std::string id);

   bool is_empty();
   std::string get_trigger_message();
   static bool extract_trigger_id(std::string message, std::string *extracted_id);
   static std::string compose_unique_trigger_id_message(int unique_id);
   static bool extract_unique_trigger_id(std::string message, int *extracted_unique_id);
};



