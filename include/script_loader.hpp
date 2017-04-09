#pragma once



#include <string>



class Script;



class ScriptLoader
{
private:
   std::string json_filename;

public:
   ScriptLoader(std::string json_filename);
   Script *create_script();
};



