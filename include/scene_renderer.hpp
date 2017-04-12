#pragma once



class ElementID;
class Entity;



class SceneRenderer
{
private:
   ElementID *scene_root;

public:
   SceneRenderer(ElementID *scene_root);
   void render();
   void draw_entity(Entity *entity, Entity *camera, Entity *light_1);
};



