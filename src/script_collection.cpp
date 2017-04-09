


#include <script.hpp>

#include <allegro_flare/console_color.h>
#include <global_constants.hpp>
#include <logging.hpp>



Script::Script(std::string id)
   : ElementID(get_manager())
{
   set(SCRIPT_ID_ATTRIBUTE, id);
}



ElementID *Script::manager = nullptr;



bool Script::initialized = false;



Script *Script::find_by_unique_id(int unique_id)
{
   return static_cast<Script *>(manager->find_descendant_by_id(unique_id));
   //return static_cast<Script *>(manager->get_element_by_unique_id(unique_id));
}



Script *Script::find_by_id(std::string id)
{
   ElementID *element = manager->find_first(SCRIPT_ID_ATTRIBUTE, id);
   //ElementID *element = manager->get_element_by_id(id);
   if (element) return static_cast<Script *>(element);
   return NULL;
}



void Script::run_script(Script *script)
{
   std::cout << "{{{ Activating script \"" << script->get_id() << "\"" << std::endl;
   script->activate();
   std::cout << "}}} Script \"" << script->get_id() << "\" finished" << std::endl;
}



bool Script::run_by_unique_id(int unique_id)
{
   Script *script = find_by_unique_id(unique_id);
   if (!script)
   {
      if (Logging::at_least(L_ERRORS))
         std::cout
            << CONSOLE_COLOR_RED
            << "Could not run script: Script with unique_id [" << unique_id << "] not foud."
            << CONSOLE_COLOR_DEFAULT
            << std::endl;

      return false;
   }
   run_script(script);
   return true;
}



bool Script::run(std::string id)
{
   Script *script = find_by_id(id);
   if (!script)
   {
      if (Logging::at_least(L_ERRORS))
         std::cout
            << CONSOLE_COLOR_RED
            << "Could not run script: Script \"" << id << "\" not foud."
            << CONSOLE_COLOR_DEFAULT
            << std::endl;

      return false;
   }
   run_script(script);
   return true;
}



void Script::initialize()
{
   if (initialized) return;
   manager = new ElementID(nullptr);
   initialized = true;
}



ElementID *Script::get_manager()
{
   if (!initialized) initialize();
   return manager;
}



