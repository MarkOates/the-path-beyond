#pragma once



#include <vector>



class ElementID;
class Entity;



class EntityCollectionHelper
{
private:
   ElementID *root;

public:
   EntityCollectionHelper(ElementID *root);

   Entity *get_camera();
   Entity *get_light_1();
   std::vector<Entity *> get_all_entities();
};



