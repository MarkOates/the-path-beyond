#pragma once



#include <string>
#include <allegro5/allegro.h>



class TargetID
{
public:
   std::string id;

   TargetID(std::string id);

   bool is_empty();
};



