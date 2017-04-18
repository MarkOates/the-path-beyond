#pragma once



#include <allegro_flare/shader.h>



class Shader2;



class ShaderCollection
{
private:
   static ShaderCollection *instance;
   static ShaderCollection *get_instance();
   ShaderCollection();
   ~ShaderCollection();

   Shader *flat_color_shader;
   Shader *simple_map_shader;
   Shader2 *wall_shader;

public:
   static Shader *get_flat_color_shader();
   static Shader *get_simple_map_shader();
   static Shader2 *get_wall_shader();
};



