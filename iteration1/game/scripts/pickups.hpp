

class PickupCardKeyDecrypter : public Script, public ScriptHelper
{
public:
  PickupCardKeyDecrypter() : Script("PickupCardKeyDecrypter") {}
  void activate() override
  {
    inventory_gui->add_item(InventoryItem::CARD_KEY_DECRYPTER);
    delete_entity("CardKeyDecrypter");
  }
};



class PickupCardKey : public Script, public ScriptHelper
{
public:
  PickupCardKey() : Script("PickupCardKey") {}
  void activate() override
  {
    inventory_gui->add_item(InventoryItem::CARD_KEY);
    delete_entity("CardKey");
  }
};


