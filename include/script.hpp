#pragma once


#include <allegro_flare/element_id.h>


class Script : public ElementID
{
private:
  static ElementID *manager;
  static bool initialized;

public:
  Script(std::string id);
  virtual void activate() = 0;

  static Script *find_by_unique_id(int unique_id);
  static Script *find_by_id(std::string id);
  static void run_script(Script *script);
  static bool run_by_unique_id(int unique_id);
  static bool run(std::string id);
  static void initialize();
  static ElementID *get_manager();
};


