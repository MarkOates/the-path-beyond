#pragma once



#include <allegro_flare/element_id.h>
#include <allegro_flare/placement3d.h>
#include <allegro5/allegro.h>



class Shader;
class Model3D;



class Entity : public ElementID
{
private:
   static Shader *flat_color_shader;
   static bool shaders_initialized;

   void initialize_shaders();

public:
   placement3d place;
   placement3d velocity;
   Model3D *model;
   ALLEGRO_BITMAP *texture;
   int attached_script_id;

   Entity(ElementID *manager, std::string id, Model3D *model=NULL, ALLEGRO_BITMAP *texture=NULL);
   void attach_script_id(int script_unique_id);
   int get_attached_script_id();
   bool is_script_attached();
   void draw();
   void draw_flat_color(ALLEGRO_COLOR color);
};



