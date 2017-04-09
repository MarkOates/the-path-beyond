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
   static Script *find_by_unique_id(int unique_id);
   static Script *find_by_id(std::string id);
   static void run_script(Script *script);
   static bool run(std::string id);
};


