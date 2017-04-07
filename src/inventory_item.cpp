


#include <inventory_item.hpp>

#include <allegro_flare/framework.h>



InventoryItem::InventoryItem(InventoryItem::Type type)
   : type(type)
{}



bool InventoryItem::is_empty()
{
   return type == EMPTY;
}



std::string InventoryItem::get_name()
{
   switch(type)
   {
   case ENCRYPTED_CARD_KEY:
      return "Encrypted Card Key";
      break;
   case CARD_KEY_DECRYPTER:
      return "Card Key Decrypter";
      break;
   case DECRYPTED_CARD_KEY:
      return "Decrypted Card Key";
      break;
   default:
      return "";
      break;
   }
}



std::string InventoryItem::get_description()
{
   switch(type)
   {
   case ENCRYPTED_CARD_KEY:
      return "";
      break;
   case CARD_KEY_DECRYPTER:
      return "";
      break;
   case DECRYPTED_CARD_KEY:
      return "";
      break;
   default:
      return "";
      break;
   }
   return std::string("");
}



ALLEGRO_BITMAP *InventoryItem::get_image()
{
   switch(type)
   {
   case ENCRYPTED_CARD_KEY:
      return Framework::bitmap("card_key.png");
      break;
   case CARD_KEY_DECRYPTER:
      return Framework::bitmap("card_key_decryptor.png");
      break;
   case DECRYPTED_CARD_KEY:
      return Framework::bitmap("card_key.png");
      break;
   default:
      return NULL;
      break;
   }
   return NULL;
}



