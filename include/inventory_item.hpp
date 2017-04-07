#pragma once



#include <string>
#include <allegro5/allegro.h>



class InventoryItem
{
public:
  enum Type
  {
    EMPTY = 0,
    ENCRYPTED_CARD_KEY,
    CARD_KEY_DECRYPTER,
    DECRYPTED_CARD_KEY,
  };

  Type type;

  InventoryItem(InventoryItem::Type type);

  bool is_empty();

  std::string get_name();
  std::string get_description();
  ALLEGRO_BITMAP *get_image();
};



