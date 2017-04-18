#pragma once



#include <allegro_flare/shader.h>



class ElementID;
class Entity;



class Shader2 : public Shader
{
public:
   Shader2(const char *vertex_src_filename, const char *fragment_src_filename);
   ~Shader2();

   virtual void use(ElementID *scene_root, Entity *object) = 0;
};



