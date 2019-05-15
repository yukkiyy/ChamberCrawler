#ifndef _ITEM_H_
#define _ITEM_H_

#include "subject.h"

class Cell;
class Player;

class Orc;
class Elves;
class Dwarf;
class Human;
class Mingyu;

class Item : public Subject {
    char symbol;
    Cell *cell;
protected:
    virtual void checkSameCell(Player &p);
public:
    Item(char symbol);
    virtual ~Item();
    
    char getSymbol() const;
    int getRow() const;
    int getCol() const;
    
    virtual bool isMovable() const;
    
    void setCell(Cell *c);
    
    virtual std::string peek() const = 0;
    
    virtual bool usedBy(Orc &o) = 0;
    virtual bool usedBy(Elves &e) = 0;
    virtual bool usedBy(Dwarf &d) = 0;
    virtual bool usedBy(Human &h) = 0;
    virtual bool usedBy(Mingyu &m) = 0;
    
    virtual bool isGeneratable(const Cell &c) const;
};

#endif
