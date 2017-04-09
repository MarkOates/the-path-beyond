


class goto1: public Script, public ScriptHelper
{
public:
   goto1() : Script("goto1") {}
   void activate() override
   {
      clear_attached_scripts();
      simple_camera_to(0, 0, 0.25);
      set_nav_buttons("", "", "goto5", "goto2");

      attach("MainDoorDoor", "goto18");
   }
};



class goto2: public Script, public ScriptHelper
{
public:
   goto2() : Script("goto2") {}
   void activate() override
   {
      clear_attached_scripts();
      simple_camera_to(0, 0, 0.124);
      set_nav_buttons("", "", "goto1", "goto3");
   }
};



class goto3: public Script, public ScriptHelper
{
public:
   goto3() : Script("goto3") {}
   void activate() override
   {
      clear_attached_scripts();
      simple_camera_to(0, 0, 0.9);
      set_nav_buttons("", "", "goto2", "goto4");
   }
};



class goto4: public Script, public ScriptHelper
{
public:
   goto4() : Script("goto4") {}
   void activate() override
   {
      clear_attached_scripts();
      simple_camera_to(0, 0, 0.7);
      set_nav_buttons("", "", "goto3", "goto5");

      attach("EncryptedCardKey", "PickupEncryptedCardKey");
      attach("SnowPoster", "goto23");
   }
};



class goto5: public Script, public ScriptHelper
{
public:
   goto5() : Script("goto5") {}
   void activate() override
   {
      clear_attached_scripts();
      simple_camera_to(0, 0, 0.5);
      set_nav_buttons("", "", "goto4", "goto1");

      attach("PoetryPoster", "goto8");
   }
};



class goto8: public Script, public ScriptHelper
{
public:
   goto8() : Script("goto8") {}
   void activate() override
   {
      clear_attached_scripts();
      simple_camera_to(0, 24, 0.45);
      set_nav_buttons("", "goto5", "", "");

      attach("CardKeyDecrypter", "PickupCardKeyDecrypter");
   }
};


////


class goto18: public Script, public ScriptHelper
{
public:
   goto18() : Script("goto18") {}
   void activate() override
   {
      clear_attached_scripts();
      simple_camera_to(-7, 0, 0.25);
      set_nav_buttons("", "goto1", "", "");

      attach("MainDoorTerminal", "OpenMainDoor");
   }
};



class goto23: public Script, public ScriptHelper
{
public:
   goto23() : Script("goto23") {}
   void activate() override
   {
      clear_attached_scripts();
      simple_camera_to(16, 0, 0.75);
      set_nav_buttons("", "goto4", "", "");
   }
};



