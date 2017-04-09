#pragma once



#include <allegro_flare/element_id.h>



class Script : public ElementID
{
public:
   Script(std::string name);
   virtual void activate() = 0;
};



