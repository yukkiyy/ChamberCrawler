#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "subject.h"

class Cell;
class Item;
class Normal;
class SmallHorde;

enum class Direction;

class Character : public Subject {
	char symbol;
	int HP;
	int maxHP;
	int Atk;
	int Def;
	Cell *cell;

	virtual int getBoostAtk() const;
	virtual int getBoostDef() const;
protected:
    void dropItem(Item *item);
    void selfRemoval();

public:
	Character(char symbol,int HP, int Atk, int Def);
    ~Character();

	char getSymbol() const;
	int getRow() const;
	int getCol() const;
	int getHP() const;
	int getAtk() const;
	int getDef() const;
    Cell *getCell() const;
    
    virtual void addGold(double g);

	void setHP(int hp);
	void setCell(Cell *c);

	bool isDead() const;
    
	virtual bool isMovable(const Cell &c) const = 0;
	virtual bool attack(Character &c) = 0;
	virtual void defense(Character &c) = 0;
    virtual bool use(Item &i) = 0;
    
    virtual bool isGeneratable(const Normal &t) const;
    virtual bool isGeneratable(const SmallHorde &t) const;
};



#endif
