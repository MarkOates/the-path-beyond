


#include <entity_collection_helper.hpp>

#include <entity.hpp>
#include <global_constants.hpp>



EntityCollectionHelper::EntityCollectionHelper(ElementID *root)
   : root(root)
{}



Entity *EntityCollectionHelper::get_by_name(const std::string &name)
{
   return static_cast<Entity *>(root->find_first(ENTITY_NAME_ATTRIBUTE, name));
}



Entity *EntityCollectionHelper::get_camera()
{
   return get_by_name(CAMERA_ENTITY_NAME);
}



Entity *EntityCollectionHelper::get_light_1()
{
   return get_by_name(LIGHT_1_ENTITY_NAME);
}



std::vector<Entity *> EntityCollectionHelper::get_all_entities()
{
   return root->get_children<Entity>();
}



