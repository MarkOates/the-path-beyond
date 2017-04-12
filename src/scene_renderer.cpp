


#include <scene_renderer.hpp>

#include <allegro_flare/model3d.h>
#include <allegro_flare/shader.h>
#include <entity_collection_helper.hpp>
#include <entity.hpp>
#include <global_constants.hpp>



SceneRenderer::SceneRenderer(ElementID *scene_root)
   : scene_root(scene_root)
{}



void SceneRenderer::render()
{
   EntityCollectionHelper entity_collection_helper(scene_root);

   std::vector<Entity *> all_entities = entity_collection_helper.get_all_entities();

   Entity *camera = entity_collection_helper.get_camera();
   Entity *light_1 = entity_collection_helper.get_light_1();

   for (auto &entity : all_entities) draw_entity(entity, camera, light_1);
}



void SceneRenderer::draw_entity(Entity *entity, Entity *camera, Entity *light_1)
{
   if (!entity->model) return;

   if (entity->shader)
   {
      entity->shader->use();

         ALLEGRO_TRANSFORM transform;
         entity->place.build_transform(&transform);
         //Shader::set_vec3("camera_position", camera->place.position);
         //Shader::set_vec3("light_position", light_1->place.position);
         Shader::set_mat4("position_transform", &transform);


         //Shader::set_bool("reflecting", cube_map_reflecting);

         Shader::set_sampler("diffuse_texture", entity->texture, 0);

         //if (shadow_map_depth_pass_transform && shadow_map_depth_pass_surface)
         //{
         //Shader::set_sampler("depth_pass_surface", shadow_map_depth_pass_surface, 1);
         //Shader::set_mat4("depth_pass_transform", shadow_map_depth_pass_transform);
         //Shader::set_float("texture_offset_x", texture_offset.x);
         //Shader::set_float("texture_offset_y", texture_offset.y);
         //}
         //Shader::set_sampler("specular_texture", specular_texture, 3);
         //Shader::set_sampler("normal_texture", normal_texture, 4);
         //Shader::set_sampler_cube("cube_map_A", cube_map_A, 5);
         //Shader::set_sampler_cube("cube_map_B", cube_map_B, 6);
         if (entity->texture) entity->model->set_texture(entity->texture);

      entity->model->draw();
   }
   else
   {
      Shader::stop();

      if (entity->texture) entity->model->set_texture(entity->texture);

      entity->place.start_transform();
      entity->model->draw();
      entity->place.restore_transform();
   }
}



