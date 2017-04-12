


#include <shader_collection.hpp>

#include <allegro_flare/framework.h>




ShaderCollection *ShaderCollection::get_instance()
{
   if (!instance) instance = new ShaderCollection();
   return instance;
}



ShaderCollection::ShaderCollection()
   : flat_color_shader(nullptr)
   , simple_map_shader(nullptr)
{
   if (!Framework::is_initialized()) throw std::runtime_error("Framework is not initialized");

   flat_color_shader = new Shader("data/shaders/flat_color_vertex.glsl", "data/shaders/flat_color_fragment.glsl");
   simple_map_shader = new Shader("data/shaders/simple_map_vertex_with_light.glsl", "data/shaders/simple_map_fragment_with_light.glsl");
}



ShaderCollection::~ShaderCollection()
{
   delete flat_color_shader;
   delete simple_map_shader;
}



Shader *ShaderCollection::get_flat_color_shader()
{
   return get_instance()->flat_color_shader;
}



Shader *ShaderCollection::get_simple_map_shader()
{
   return get_instance()->simple_map_shader;
}



ShaderCollection *ShaderCollection::instance = nullptr;



