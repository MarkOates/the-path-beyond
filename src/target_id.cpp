


#include <target_id.hpp>



TargetID::TargetID(std::string id)
   : id(id)
{}



bool TargetID::is_empty()
{
   return id == "";
}



