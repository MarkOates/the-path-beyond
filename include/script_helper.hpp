#pragma once



#include <allegro_flare/placement3d.h>
#include <inventory_gui/screen.hpp>
#include <start_screen_gui/screen.hpp>
#include <world_navigation_gui/screen.hpp>
#include <entity.hpp>
#include <script.hpp>
#include <world_render_screen.hpp>



class ScriptHelper
{
protected:
   static WorldRenderScreen *world_render;
   static WorldNavigationGUI::Screen *world_navigation_gui;
   static InventoryGUI::Screen *inventory_gui;
   static StartScreenGUI::Screen *start_screen_gui;
   static bool initialized;

public:
   static void load_game_scripts();

   // helper methods
   static float normalize_rotation(float *rotation);
   static void fix_least_distance_rotation_theta(float *from, float *to);
   static void fix_least_distance_rotation(placement3d *from, placement3d *to);
   static void move_to(placement3d *from, placement3d to, float speed=0.4);
   static void simple_camera_to(float x, float y, float rotation, float speed=1.0);
   static void clear_attached_scripts();
   static void delete_entity(std::string entity_id);
   static int get_script_id(std::string script_name);
   static void attach(std::string entity_id, std::string script_name);
   static Entity *entity_by_id(std::string entity_id);
   static void show_notification(std::string message);
   static void camera_to(vec3d position, vec3d rotation, vec3d anchor, float speed=0.4);
   void set_nav_buttons(std::string up_target, std::string down_target, std::string left_target, std::string right_target);
   static Entity *create_entity(std::string id, vec3d position, float rotation, std::string obj_filename, std::string texture_filename);
   static void initialize(WorldRenderScreen *wrs, WorldNavigationGUI::Screen *wnguis, InventoryGUI::Screen *iguis, StartScreenGUI::Screen *ssgui);
};



