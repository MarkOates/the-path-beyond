


#include <script_collection.hpp>

#include <allegro_flare/console_color.h>
#include <global_constants.hpp>
#include <logging.hpp>
#include <script.hpp>



ElementID *ScriptCollection::instance = nullptr;



Script *ScriptCollection::find_by_unique_id(int unique_id)
{
   return static_cast<Script *>(get_instance()->find_descendant_by_id(unique_id));
}



Script *ScriptCollection::find_by_id(std::string id)
{
   ElementID *element = get_instance()->find_first(SCRIPT_ID_ATTRIBUTE, id);
   if (element) return static_cast<Script *>(element);
   return NULL;
}



void ScriptCollection::run_script(Script *script)
{
   if (!script) throw std::runtime_error("Can not run a null script");
   std::cout << "{{{ Activating script \"" << script->get_id() << "\"" << std::endl;
   script->activate();
   std::cout << "}}} ScriptCollection \"" << script->get_id() << "\" finished" << std::endl;
}



ElementID *ScriptCollection::get_instance()
{
   if (!instance) instance = new ElementID(nullptr);
   return instance;
}



