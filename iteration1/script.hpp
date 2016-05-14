


class Script : public ElementID
{
public:
  static ElementIDManager *manager;
  static WorldRenderScreen *world_render;
  static WorldNavigationGUIScreen *world_navigation_gui;
  static InventoryGUIScreen *inventory_gui;
  static StartScreenGUIScreen *start_screen_gui;
  static bool initialized;

  static void initialize(
      WorldRenderScreen *wrs,
      WorldNavigationGUIScreen *wnguis,
      InventoryGUIScreen *iguis,
      StartScreenGUIScreen *ssgui
      )
  {
    if (initialized) return;

    manager = new ElementIDManager();
    world_render = wrs;
    world_navigation_gui = wnguis;
    start_screen_gui = ssgui;
    inventory_gui = iguis;

    initialized = true;
  }
  static Script *find_by_id(std::string id)
  {
    ElementID *element = manager->get_element_by_id(id);
    if (element) return static_cast<Script *>(element);
    return NULL;
  }
  static bool run(std::string id)
  {
    Script *script = find_by_id(id);
    if (!script)
    {
      std::cout << "Could not run script: Script \"" << id << "\" not foud." << std::endl;
      return false;
    }
    std::cout << "{{{ Activating script \"" << script->get_id() << "\"" << std::endl;
    script->activate();
    std::cout << "}}} Script \"" << script->get_id() << "\" finished" << std::endl;
    return true;
  }

  Script(std::string id) : ElementID(manager)
  {
    set_id(id);
  }
  virtual void activate() = 0;
};
ElementIDManager *Script::manager = NULL;
WorldNavigationGUIScreen *Script::world_navigation_gui = NULL;
InventoryGUIScreen *Script::inventory_gui = NULL;
StartScreenGUIScreen *Script::start_screen_gui = NULL;
WorldRenderScreen *Script::world_render = NULL;
bool Script::initialized = false;


