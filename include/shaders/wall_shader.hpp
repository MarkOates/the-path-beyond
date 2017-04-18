#pragma once



#include <shader2.hpp>



class ElementID;
class Entity;



class WallShader : public Shader2
{
private:
   ALLEGRO_BITMAP *diffuse_texture;

public:
   WallShader(ALLEGRO_BITMAP *diffuse_texture);
   ~WallShader();

   void use(ElementID *scene_root, Entity *object) override;
};



