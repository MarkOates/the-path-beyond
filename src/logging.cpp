


#include <logging.hpp>



Logging *Logging::get_instance()
{
   if (!instance) instance = new Logging(DEFAULT_LOG_LEVEL);
   return instance;
}



Logging::Logging(log_level_t level)
   : level(level)
{}



void Logging::set_level(log_level_t log_level)
{
   Logging *instance = get_instance();
   instance->level = log_level;
}



bool Logging::at_least(log_level_t log_level)
{
   Logging *instance = get_instance();
   return instance->level >= log_level;
}



Logging *Logging::instance = nullptr;



