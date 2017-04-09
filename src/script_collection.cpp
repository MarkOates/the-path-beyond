


#include <script_collection.hpp>

#include <allegro_flare/console_color.h>
#include <global_constants.hpp>
#include <logging.hpp>
#include <script.hpp>



ElementID *ScriptCollection::instance = nullptr;



Script *ScriptCollection::find_by_unique_id(int unique_id)
{
   return static_cast<Script *>(get_instance()->find_descendant_by_id(unique_id));
   //return static_cast<ScriptCollection *>(get_instance()->get_element_by_unique_id(unique_id));
}



Script *ScriptCollection::find_by_id(std::string id)
{
   ElementID *element = get_instance()->find_first(SCRIPT_ID_ATTRIBUTE, id);
   //ElementID *element = get_instance()->get_element_by_id(id);
   if (element) return static_cast<Script *>(element);
   return NULL;
}



void ScriptCollection::run_script(Script *script)
{
   std::cout << "{{{ Activating script \"" << script->get_id() << "\"" << std::endl;
   script->activate();
   std::cout << "}}} ScriptCollection \"" << script->get_id() << "\" finished" << std::endl;
}



bool ScriptCollection::run_by_unique_id(int unique_id)
{
   Script *script = find_by_unique_id(unique_id);
   if (!script)
   {
      if (Logging::at_least(L_ERRORS))
         std::cout
            << CONSOLE_COLOR_RED
            << "Could not run script: ScriptCollection with unique_id [" << unique_id << "] not foud."
            << CONSOLE_COLOR_DEFAULT
            << std::endl;

      return false;
   }
   run_script(script);
   return true;
}



bool ScriptCollection::run(std::string id)
{
   Script *script = find_by_id(id);
   if (!script)
   {
      if (Logging::at_least(L_ERRORS))
         std::cout
            << CONSOLE_COLOR_RED
            << "Could not run script: ScriptCollection \"" << id << "\" not foud."
            << CONSOLE_COLOR_DEFAULT
            << std::endl;

      return false;
   }
   run_script(script);
   return true;
}



ElementID *ScriptCollection::get_instance()
{
   if (!instance) instance = new ElementID(nullptr);
   return instance;
}



