

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



class PickupEncryptedCardKey : public Script, public ScriptHelper
{
public:
  PickupEncryptedCardKey() : Script("PickupEncryptedCardKey") {}
  void activate() override
  {
    inventory_gui->add_item(InventoryItem::ENCRYPTED_CARD_KEY);
    delete_entity("EncryptedCardKey");
  }
};


