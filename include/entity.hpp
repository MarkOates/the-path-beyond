#pragma once



#include <allegro_flare/element_id.h>
#include <allegro_flare/placement3d.h>
#include <allegro5/allegro.h>



class Shader2;
class Model3D;



class Entity : public ElementID
{
public:
   placement3d place;
   placement3d velocity;
   Model3D *model;
   Shader2 *shader;
   ALLEGRO_BITMAP *texture;
   int attached_script_id;

   Entity(ElementID *manager, std::string name, Model3D *model=NULL, ALLEGRO_BITMAP *texture=NULL);
   void attach_script_id(int script_unique_id);
   int get_attached_script_id();
   bool is_script_attached();
   void draw_flat_color(ALLEGRO_COLOR color);
};



