


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

   for (auto &entity : all_entities) draw_entity(entity);
}



void SceneRenderer::draw_entity(Entity *entity)
{
   if (!entity->model) return;
   if (entity->texture) entity->model->set_texture(entity->texture);

   if (entity->shader) entity->shader->use();
   else Shader::stop();

   entity->place.start_transform();
   entity->model->draw();
   entity->place.restore_transform();
}



