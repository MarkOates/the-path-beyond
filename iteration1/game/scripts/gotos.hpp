



class goto1: public Script, public ScriptHelper
{
public:
  goto1() : Script("goto1") {}
  void activate() override
  {
    simple_camera_to(0, 0, 0.25);
    set_nav("", "", "5", "2");
  }
};



class goto2: public Script, public ScriptHelper
{
public:
  goto2() : Script("goto2") {}
  void activate() override
  {
    simple_camera_to(0, 0, 0.124);
    set_nav("", "", "1", "3");
  }
};



class goto3: public Script, public ScriptHelper
{
public:
  goto3() : Script("goto3") {}
  void activate() override
  {
    simple_camera_to(0, 0, 0.9);
    set_nav("", "", "2", "4");
  }
};



class goto4: public Script, public ScriptHelper
{
public:
  goto4() : Script("goto4") {}
  void activate() override
  {
    simple_camera_to(0, 0, 0.7);
    set_nav("", "", "3", "5");
  }
};



class goto5: public Script, public ScriptHelper
{
public:
  goto5() : Script("goto5") {}
  void activate() override
  {
    simple_camera_to(0, 0, 0.5);
    set_nav("", "", "4", "1");
  }
};


