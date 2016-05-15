

class ScriptHelper
{
protected:
  static WorldRenderScreen *world_render;
  static WorldNavigationGUIScreen *world_navigation_gui;
  static InventoryGUIScreen *inventory_gui;
  static StartScreenGUIScreen *start_screen_gui;
  static bool initialized;

public:
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


