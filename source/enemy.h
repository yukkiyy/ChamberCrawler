#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "character.h"

class Item;
class Cell;

class Enemy : public Character {
	Item *item;
    virtual void dropGold(Character &c) const;
public:
	Enemy(char symbol, int HP, int Atk, int Def, Item *item = nullptr);
	virtual ~Enemy() = 0;
	
	bool setItem(Item *i);
    bool placeable() const;
    
    virtual bool isMovable(const Cell &c) const override;

    bool attack(Character &c) override;
	void defense(Character &c) override;
    
    bool use(Item &i) override final;
};


#endif
