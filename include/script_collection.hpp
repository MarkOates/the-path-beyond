#pragma once


#include <allegro_flare/element_id.h>


class Script;


class ScriptCollection : public ElementID
{
   friend class Script;

private:
   static ElementID *instance;
   static ElementID *get_instance();

public:
   static Script *find_by_id(int id);
   static Script *find_by_name(std::string name);
};


