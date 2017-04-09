


#include <script.hpp>

#include <global_constants.hpp>
#include <script_collection.hpp>



Script::Script(std::string name)
   : ElementID(ScriptCollection::get_instance())
{
   set(SCRIPT_NAME_ATTRIBUTE, name);
   set(SCRIPT_ID_ATTRIBUTE, name);
}



