


#include <script_helper.hpp>

#include <allegro_flare/framework.h>
#include <inventory_gui/notification.hpp>
#include <cmath>
#include <script_collection.hpp>
#include <global_constants.hpp>



float ScriptHelper::normalize_rotation(float *rotation)
{
   while (*rotation > 0.0) *rotation -= 1.0;
   while (*rotation < 0.0) *rotation += 1.0;
   return *rotation;
}



void ScriptHelper::fix_least_distance_rotation_theta(float *from, float *to)
{
   // worst. algorithm. ever.
   if (*to > *from) { if (fabs(*to-*from) > 0.5) *to = *to-1.0; }
   else { if (fabs(*from-*to) > 0.5) *to = *to+1.0; }
}



void ScriptHelper::fix_least_distance_rotation(placement3d *from, placement3d *to)
{
   normalize_rotation(&from->rotation.x);
   normalize_rotation(&from->rotation.y);
   normalize_rotation(&from->rotation.z);

   normalize_rotation(&to->rotation.x);
   normalize_rotation(&to->rotation.y);
   normalize_rotation(&to->rotation.z);

   fix_least_distance_rotation_theta(&from->rotation.x, &to->rotation.x);
   fix_least_distance_rotation_theta(&from->rotation.y, &to->rotation.y);
   fix_least_distance_rotation_theta(&from->rotation.z, &to->rotation.z);
}



void ScriptHelper::move_to(placement3d *from, placement3d to, float speed)
{
   Framework::motion().cmove_to(&from->position.x, to.position.x, speed);
   Framework::motion().cmove_to(&from->position.y, to.position.y, speed);
   Framework::motion().cmove_to(&from->position.z, to.position.z, speed);

   fix_least_distance_rotation(from, &to);

   Framework::motion().cmove_to(&from->rotation.x, to.rotation.x, speed);
   Framework::motion().cmove_to(&from->rotation.y, to.rotation.y, speed);
   Framework::motion().cmove_to(&from->rotation.z, to.rotation.z, speed);

   Framework::motion().cmove_to(&from->anchor.x, to.anchor.x, speed);
   Framework::motion().cmove_to(&from->anchor.y, to.anchor.y, speed);
   Framework::motion().cmove_to(&from->anchor.z, to.anchor.z, speed);
}



void ScriptHelper::simple_camera_to(float x, float y, float rotation, float speed)
{
   placement3d place = placement3d();
   place.position = vec3d(x, 2, y);
   place.rotation = vec3d(0, rotation, 0);
   place.anchor = vec3d(0, 0, 1);

   move_to(&world_render->camera->place, place, speed);
}



void ScriptHelper::clear_attached_scripts()
{
   for (auto &e : world_render->manager->get_children())
   {
      Entity *entity = static_cast<Entity *>(e);
      entity->attach_script_id(0);
   }
}



void ScriptHelper::delete_entity(std::string entity_name)
{
   Entity *e = entity_by_name(entity_name);
   // god save us all...
   delete e; 
}



int ScriptHelper::get_script_id(std::string script_name)
{
   Script *script = ScriptCollection::find_by_name(script_name);
   if (script) return script->get_id();
   //if (script) return script->get_id_num();

   std::cout << CONSOLE_COLOR_RED << "could not locate script by name \"" << script_name << "\"" << CONSOLE_COLOR_DEFAULT << std::endl;
   return 0;
}



void ScriptHelper::attach_script_to_entity(std::string entity_name, std::string script_name)
{
   Entity *e = entity_by_name(entity_name);
   int script_id = get_script_id(script_name);
   if (e && (script_id != 0))
   {
      e->attach_script_id(script_id);
   }
   else
   {
      std::cout << CONSOLE_COLOR_RED << "attachment failed" << CONSOLE_COLOR_DEFAULT << std::endl;
   }
}



Entity *ScriptHelper::entity_by_name(std::string entity_name)
{
   //Entity *e = static_cast<Entity *>(world_render->manager->get_element_by_id(entity_id));
   Entity *e = static_cast<Entity *>(world_render->manager->find_first(ENTITY_ID_ATTRIBUTE, entity_name));
   if (!e)
   {
      std::cout << CONSOLE_COLOR_RED << "could not locate entity by name \"" << entity_name << "\"" << CONSOLE_COLOR_DEFAULT << std::endl;
   }
   return e;
}



void ScriptHelper::show_notification(std::string message)
{
   inventory_gui->notification->show(message);
}



void ScriptHelper::camera_to(vec3d position, vec3d rotation, vec3d anchor, float speed)
{
   placement3d place = placement3d();
   place.position = position;
   place.rotation = rotation;
   place.anchor = anchor;

   move_to(&world_render->camera->place, place, speed);
}



void ScriptHelper::set_nav_buttons(std::string up_target, std::string down_target, std::string left_target, std::string right_target)
{
   world_navigation_gui->set_usability_mode(0);

   world_navigation_gui->nav_up_button->set_script_by_name(up_target);
   world_navigation_gui->nav_down_button->set_script_by_name(down_target);
   world_navigation_gui->nav_left_button->set_script_by_name(left_target);
   world_navigation_gui->nav_right_button->set_script_by_name(right_target);

   world_navigation_gui->set_usability_mode(1);
}



Entity *ScriptHelper::create_entity(std::string id, vec3d position, float rotation, std::string obj_filename, std::string texture_filename)
{
   Entity *e = new Entity(
         world_render->manager,
         id,
         Framework::model(obj_filename),
         Framework::bitmap(texture_filename));
   e->place.position = position;
   e->place.rotation.y = rotation;

   return e;
}



void ScriptHelper::initialize(WorldRenderScreen *wrs, WorldNavigationGUI::Screen *wnguis, InventoryGUI::Screen *iguis, StartScreenGUI::Screen *ssgui)
{
   if (initialized) return;

   world_render = wrs;
   world_navigation_gui = wnguis;
   start_screen_gui = ssgui;
   inventory_gui = iguis;

   load_game_scripts();

   initialized = true;
}



WorldNavigationGUI::Screen *ScriptHelper::world_navigation_gui = NULL;



InventoryGUI::Screen *ScriptHelper::inventory_gui = NULL;



StartScreenGUI::Screen *ScriptHelper::start_screen_gui = NULL;



WorldRenderScreen *ScriptHelper::world_render = NULL;



bool ScriptHelper::initialized = false;




