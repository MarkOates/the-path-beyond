


class TargetID
{
public:
  std::string id;
  TargetID(std::string id)
    : id(id)
  {}
  bool is_empty()
  {
    return id == "";
  }
  std::string get_trigger_message() { return tostring("trigger_target_id ") + id; }
  static bool extract_trigger_id(std::string message, std::string *extracted_id)
  {
    if (strncmp(message.c_str(), "trigger_target_id ", 18) == 0)
    {
      // we have a valid trigger message
      *extracted_id = message.substr(18);
      return true;
    }
    return false;
  }
};


