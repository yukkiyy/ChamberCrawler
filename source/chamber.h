#ifndef _CHAMBER_H_
#define _CHAMBER_H_
#include <vector>
#include <cstddef>

class Cell;
class Character;
class Item;

class Chamber {
    std::vector<Cell *> cells;
    std::vector<Cell *> empty;
    std::vector<Cell *> occupied;
    
    Cell *chooseFromAll();

public:
    Chamber();
    ~Chamber();

    void addCell(Cell *c);
    // only the cell that will become Stair will be removed
    void removeCell(Cell *c);
    
    // return false if place is not succeed
    bool place(Character *c);
    bool place(Item *i);
    
    // place dragon & dragon hoard / barrier suit
    bool place(Item *i, Character *d);

    // Returns a pointer to unoccupied empty cell
    // return nullptr if no available cell
    Cell *chooseRandomCell();
    
    void reset();
};

#endif
