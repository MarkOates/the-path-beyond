


class PickupCardKeyDecrypter : public ScriptCollection, public ScriptHelper
{
public:
   PickupCardKeyDecrypter() : ScriptCollection("PickupCardKeyDecrypter") {}
   void activate() override
   {
      inventory_gui->add_item(InventoryItem::CARD_KEY_DECRYPTER);
      delete_entity("CardKeyDecrypter");
      show_notification("picked up Card Key Decrypter");
   }
};



class PickupEncryptedCardKey : public ScriptCollection, public ScriptHelper
{
public:
   PickupEncryptedCardKey() : ScriptCollection("PickupEncryptedCardKey") {}
   void activate() override
   {
      inventory_gui->add_item(InventoryItem::ENCRYPTED_CARD_KEY);
      delete_entity("EncryptedCardKey");
      show_notification("picked up Encrypted Card Key");
   }
};



class OpenMainDoor : public ScriptCollection, public ScriptHelper
{
public:
   OpenMainDoor() : ScriptCollection("OpenMainDoor") {}
   void activate() override
   {
      if (inventory_gui->has_item(InventoryItem::Type::DECRYPTED_CARD_KEY))
      {
         show_notification("You have escaped the moon base.");
      }
      else
      {
         show_notification("You need a valid key");
      }
   }
};



