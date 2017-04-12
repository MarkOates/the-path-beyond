


#include <scene_renderer.hpp>

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

   for (auto &entity : all_entities) entity->draw();
}



