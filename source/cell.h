#ifndef _CELL_H_
#define _CELL_H_
#include <vector>
#include "subject.h"

class Item;
class Normal;
class SmallHorde;
class Character;
class Enemy;
class Player;

enum class Direction;

class Cell : public Subject {
    char symbol;
    int row;
    int col;
    bool visible;
    
    Item *item;
    Character *character;
    
    std::vector<Cell *> neighbors;

public:
    Cell(char symbol, int row, int col, bool visible = true);
    virtual ~Cell() = 0;

    char getSymbol() const;
    char getFloorSymbol() const;
    int getRow() const;
    int getCol() const;
    Character *getCharacter() const;
    
    void addNeighbor(Cell *neighbor, int i);
    void removeNeighbor(Cell *neighbor);
    void replaceNeighbor(Cell *oldnei, Cell *newnei);
    void replaceSelf(Cell *newone);
    void cloneNeighbors(Cell *receiver);

    void setItem(Item *i);
    void setCharacter(Character *c);
    void setVisible(bool v);
    
    bool use(Character &c);
    void use(Direction d);
    
    void attack(Direction d);
    bool attack(Character &attacker);
    
    std::string peek() const;
    std::string peekNeighbor(Direction d) const;

    virtual bool isMovable(const Enemy &e) const;
    virtual bool isMovable(const Player &p) const;
    virtual bool isGeneratable(const Character &c) const;
    virtual bool isGeneratable(const Item &i) const;
    virtual bool isGeneratable(const Normal &t) const;
    virtual bool isGeneratable(const SmallHorde &t) const;
    
    // player move
    void moveTo(Direction d);
    // enemy move
    void randomMove();
};

#endif
