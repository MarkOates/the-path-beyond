


#include <entity.hpp>

#include <allegro_flare/shader.h>
#include <allegro_flare/model3d.h>
#include <global_constants.hpp>
#include <shader_collection.hpp>



Entity::Entity(ElementID *manager, std::string id, Model3D *model, ALLEGRO_BITMAP *texture)
   : ElementID(manager)
   , place()
   , velocity()
   , model(model)
   , shader(nullptr)
   , texture(texture)
   , attached_script_id(0)
{
   //set_id(id);
   set(ENTITY_ID_ATTRIBUTE, id);
   velocity.align = vec3d(0, 0, 0);
   velocity.scale = vec3d(0, 0, 0);
}



void Entity::attach_script_id(int script_unique_id)
{
   attached_script_id = script_unique_id;
}



int Entity::get_attached_script_id()
{
   return attached_script_id;
}



bool Entity::is_script_attached()
{
   return attached_script_id != 0;
}



void Entity::draw()
{
   if (!model) return;
   if (texture) model->set_texture(texture);

   if (shader) shader->use();
   else Shader::stop();

   place.start_transform();
   model->draw();
   place.restore_transform();
}



void Entity::draw_flat_color(ALLEGRO_COLOR color)
{
   if (!model) return;

   ShaderCollection::get_flat_color_shader()->use();
   if (is_script_attached()) Shader::set_vec4("tint", color.r, color.g, color.b, color.a);
   else Shader::set_vec4("tint", 0, 0, 0, 0);

   place.start_transform();
   model->draw();
   place.restore_transform();
}



