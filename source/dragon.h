#ifndef _DRAGON_H_
#define _DRAGON_H_
#include "enemy.h"

class Cell;
class Item;


class Dragon: public Enemy {
    // Dragon Hoard or Barrier Suit
    Item *hoard;
    void dropGold(Character &c) const override;
public:
	Dragon();
	~Dragon();

	//attack only if the player is close to the dragon hoard
	bool attack(Character &c) override;
    void setHoard(Item *i);
    
    bool isMovable(const Cell &c) const override;
};


#endif

