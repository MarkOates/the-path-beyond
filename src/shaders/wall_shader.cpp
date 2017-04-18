


#include <shaders/wall_shader.hpp>

#include <allegro_flare/vec3d.h>
#include <entity.hpp>
#include <entity_collection_helper.hpp>



WallShader::WallShader(ALLEGRO_BITMAP *diffuse_texture)
   : Shader2(
      "data/shaders/simple_map_vertex_with_light.glsl",
      "data/shaders/simple_map_fragment_with_light.glsl"
     )
   , diffuse_texture(diffuse_texture)
{}



WallShader::~WallShader()
{}



void WallShader::use(ElementID *scene_root, Entity *object)
{
   if (!object || !scene_root) throw std::runtime_error("can not use shader without object or scene");

   EntityCollectionHelper entity_collection_helper(scene_root);
   ALLEGRO_TRANSFORM transform;

   Entity *camera = entity_collection_helper.get_camera();
   Entity *light_1 = entity_collection_helper.get_light_1();
   if (object) object->place.build_transform(&transform);

   if (!camera) throw std::runtime_error("camera not found!");
   if (!light_1) throw std::runtime_error("light not found!");
   if (!diffuse_texture) throw std::runtime_error("diffuse_texture not found!");

   Shader::use();
   set_vec3("camera_position", camera->place.position);
   set_vec3("light_position", light_1->place.position);
   set_mat4("position_transform", &transform);
   set_sampler("diffuse_texture", diffuse_texture, 0);
}



