


#include <entity_collection_helper.hpp>

#include <entity.hpp>
#include <global_constants.hpp>



EntityCollectionHelper::EntityCollectionHelper(ElementID *root)
   : root(root)
{}



Entity *EntityCollectionHelper::get_camera()
{
   return static_cast<Entity *>(root->find_first(CAMERA_ENTITY_NAME));
}



Entity *EntityCollectionHelper::get_light_1()
{
   return static_cast<Entity *>(root->find_first(LIGHT_1_ENTITY_NAME));
}



std::vector<Entity *> EntityCollectionHelper::get_all_entities()
{
   return root->get_children<Entity>();
}



