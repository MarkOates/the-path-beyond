#pragma once


#include <allegro_flare/element_id.h>


class ScriptCollection : public ElementID
{
private:
   static ElementID *manager;
   static bool initialized;

public:
   ScriptCollection(std::string id);
   virtual void activate() = 0;

   static ScriptCollection *find_by_unique_id(int unique_id);
   static ScriptCollection *find_by_id(std::string id);
   static void run_script(ScriptCollection *script);
   static bool run_by_unique_id(int unique_id);
   static bool run(std::string id);
   static void initialize();
   static ElementID *get_manager();
};


