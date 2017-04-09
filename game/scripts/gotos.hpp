


class goto1: public ScriptCollection, public ScriptHelper
{
public:
   goto1() : ScriptCollection("goto1") {}
   void activate() override
   {
      clear_attached_scripts();
      simple_camera_to(0, 0, 0.25);
      set_nav_buttons("", "", "goto5", "goto2");

      attach("MainDoorDoor", "goto18");
   }
};



class goto2: public ScriptCollection, public ScriptHelper
{
public:
   goto2() : ScriptCollection("goto2") {}
   void activate() override
   {
      clear_attached_scripts();
      simple_camera_to(0, 0, 0.124);
      set_nav_buttons("", "", "goto1", "goto3");
   }
};



class goto3: public ScriptCollection, public ScriptHelper
{
public:
   goto3() : ScriptCollection("goto3") {}
   void activate() override
   {
      clear_attached_scripts();
      simple_camera_to(0, 0, 0.9);
      set_nav_buttons("", "", "goto2", "goto4");
   }
};



class goto4: public ScriptCollection, public ScriptHelper
{
public:
   goto4() : ScriptCollection("goto4") {}
   void activate() override
   {
      clear_attached_scripts();
      simple_camera_to(0, 0, 0.7);
      set_nav_buttons("", "", "goto3", "goto5");

      attach("EncryptedCardKey", "PickupEncryptedCardKey");
      attach("SnowPoster", "goto23");
   }
};



class goto5: public ScriptCollection, public ScriptHelper
{
public:
   goto5() : ScriptCollection("goto5") {}
   void activate() override
   {
      clear_attached_scripts();
      simple_camera_to(0, 0, 0.5);
      set_nav_buttons("", "", "goto4", "goto1");

      attach("PoetryPoster", "goto8");
   }
};



class goto8: public ScriptCollection, public ScriptHelper
{
public:
   goto8() : ScriptCollection("goto8") {}
   void activate() override
   {
      clear_attached_scripts();
      simple_camera_to(0, 24, 0.45);
      set_nav_buttons("", "goto5", "", "");

      attach("CardKeyDecrypter", "PickupCardKeyDecrypter");
   }
};


////


class goto18: public ScriptCollection, public ScriptHelper
{
public:
   goto18() : ScriptCollection("goto18") {}
   void activate() override
   {
      clear_attached_scripts();
      simple_camera_to(-7, 0, 0.25);
      set_nav_buttons("", "goto1", "", "");

      attach("MainDoorTerminal", "OpenMainDoor");
   }
};



class goto23: public ScriptCollection, public ScriptHelper
{
public:
   goto23() : ScriptCollection("goto23") {}
   void activate() override
   {
      clear_attached_scripts();
      simple_camera_to(16, 0, 0.75);
      set_nav_buttons("", "goto4", "", "");
   }
};



