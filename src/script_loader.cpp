


#include <script_loader.hpp>

#include <allegro_flare/json.h>
#include <allegro_flare/useful_php.h>



ScriptLoader::ScriptLoader(std::string json_filename)
   : json_filename(json_filename)
{}



Script *ScriptLoader::create_script()
{
   std::string file_contents = php::file_get_contents(json_filename);
   JSON::Object root = json_object(file_contents);

   return nullptr;
}



