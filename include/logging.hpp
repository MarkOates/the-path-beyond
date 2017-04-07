#pragma once



#define DEFAULT_LOG_LEVEL L_NORMAL



enum log_level_t
{
   L_SILENT = 0,
   L_ERRORS,
   L_NORMAL,
   L_VERBOSE,
};



class Logging
{
public:
   static void set_level(log_level_t log_level);
   static bool at_least(log_level_t log_level);

private:
   static Logging *instance;
   static Logging *get_instance();
   Logging(log_level_t level);

   log_level_t level;
};



