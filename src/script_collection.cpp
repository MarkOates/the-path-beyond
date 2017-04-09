


#include <script_collection.hpp>

#include <global_constants.hpp>
#include <script.hpp>



ElementID *ScriptCollection::instance = nullptr;



Script *ScriptCollection::find_by_id(int id)
{
   return static_cast<Script *>(get_instance()->find_descendant_by_id(id));
}



Script *ScriptCollection::find_by_name(std::string name)
{
   return static_cast<Script *>(get_instance()->find_first(SCRIPT_NAME_ATTRIBUTE, name));
}



ElementID *ScriptCollection::get_instance()
{
   if (!instance) instance = new ElementID(nullptr);
   return instance;
}



