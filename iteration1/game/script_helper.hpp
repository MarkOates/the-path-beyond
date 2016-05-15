

class ScriptHelper
{
protected:
  static WorldRenderScreen *world_render;
  static WorldNavigationGUIScreen *world_navigation_gui;
  static InventoryGUIScreen *inventory_gui;
  static StartScreenGUIScreen *start_screen_gui;
  static bool initialized;

public:
  // helper methods
  static float normalize_rotation(float *rotation)
  {
    while (*rotation > 0.0) *rotation -= 1.0;
    while (*rotation < 0.0) *rotation += 1.0;
    return *rotation;
  }
  static void fix_least_distance_rotation_theta(float *from, float *to)
  {
    // worst. algorithm. ever.
    if (*to > *from) { if (fabs(*to-*from) > 0.5) *to = *to-1.0; }
    else { if (fabs(*from-*to) > 0.5) *to = *to+1.0; }
  }
  static void fix_least_distance_rotation(placement3d *from, placement3d *to)
  {
    normalize_rotation(&from->rotation.x);
    normalize_rotation(&from->rotation.y);
    normalize_rotation(&from->rotation.z);

    normalize_rotation(&to->rotation.x);
    normalize_rotation(&to->rotation.y);
    normalize_rotation(&to->rotation.z);

    fix_least_distance_rotation_theta(&from->rotation.x, &to->rotation.x);
    fix_least_distance_rotation_theta(&from->rotation.y, &to->rotation.y);
    fix_least_distance_rotation_theta(&from->rotation.z, &to->rotation.z);
  }
  static void move_to(placement3d *from, placement3d to, float speed=0.4)
  {
    af::motion.cmove_to(&from->position.x, to.position.x, speed);
    af::motion.cmove_to(&from->position.y, to.position.y, speed);
    af::motion.cmove_to(&from->position.z, to.position.z, speed);

    fix_least_distance_rotation(from, &to);

    af::motion.cmove_to(&from->rotation.x, to.rotation.x, speed);
    af::motion.cmove_to(&from->rotation.y, to.rotation.y, speed);
    af::motion.cmove_to(&from->rotation.z, to.rotation.z, speed);

    af::motion.cmove_to(&from->anchor.x, to.anchor.x, speed);
    af::motion.cmove_to(&from->anchor.y, to.anchor.y, speed);
    af::motion.cmove_to(&from->anchor.z, to.anchor.z, speed);
  }
  static void camera_to(vec3d position, vec3d rotation, vec3d anchor, float speed=0.4)
  {
    placement3d place = placement3d();
    place.position = position;
    place.rotation = rotation;
    place.anchor = anchor;

    move_to(&world_render->camera->place, place, speed);
  }
  static void set_nav_buttons
    ( std::string up_target
    , std::string down_target
    , std::string left_target
    , std::string right_target
    )
  {
    world_navigation_gui->nav_up_button->set_target_id(TargetID(up_target));
    world_navigation_gui->nav_down_button->set_target_id(TargetID(down_target));
    world_navigation_gui->nav_left_button->set_target_id(TargetID(left_target));
    world_navigation_gui->nav_right_button->set_target_id(TargetID(right_target));

    world_navigation_gui->set_usability_mode(1);
  }
  static void initialize(
      WorldRenderScreen *wrs,
      WorldNavigationGUIScreen *wnguis,
      InventoryGUIScreen *iguis,
      StartScreenGUIScreen *ssgui
      )
  {
    if (initialized) return;

    world_render = wrs;
    world_navigation_gui = wnguis;
    start_screen_gui = ssgui;
    inventory_gui = iguis;

    initialized = true;
  }
};
WorldNavigationGUIScreen *ScriptHelper::world_navigation_gui = NULL;
InventoryGUIScreen *ScriptHelper::inventory_gui = NULL;
StartScreenGUIScreen *ScriptHelper::start_screen_gui = NULL;
WorldRenderScreen *ScriptHelper::world_render = NULL;
bool ScriptHelper::initialized = false;


