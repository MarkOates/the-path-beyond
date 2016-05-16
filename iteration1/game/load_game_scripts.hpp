

#include "./scripts/gotos.hpp"

void ScriptHelper::load_game_scripts()
{
  // load the individual scripts
  new StartTitleScreen();
  new StartGame();

  new goto1();
  new goto2();
  new goto3();
  new goto4();
  new goto5();
}


