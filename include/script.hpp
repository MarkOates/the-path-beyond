#pragma once



#include <allegro_flare/element_id.h>



#define SCRIPT_NAME_ATTRIBUTE "name"



class Script : public ElementID
{
public:
   Script(std::string name);
   virtual void activate() = 0;
};



