#include "chamber.h"
#include "character.h"
#include "item.h"
#include "cell.h"
#include "utility.h"

#include <vector>

using namespace std;

Cell *Chamber::chooseFromAll() {
    if (cells.size() == 0) return nullptr;
    size_t i = rand() % cells.size();
    Cell *c = cells[i];
    
    for (size_t i = 0; i < empty.size(); ++i) {
        if (empty[i] == c) {
            empty.erase(empty.begin() + i);
            break;
        }
    }
    
    occupied.emplace_back(c);
    return c;
}


Cell *Chamber::chooseRandomCell() {
    if (empty.size() == 0) return nullptr;
    size_t i = rand() % empty.size();
    Cell *c = empty[i];
    occupied.emplace_back(c);
    empty.erase(empty.begin() + i);
    return c;
}

Chamber::Chamber() {}

Chamber::~Chamber() {}

void Chamber::addCell(Cell *c) {
    empty.emplace_back(c);
    cells.emplace_back(c);
}

void Chamber::removeCell(Cell *c) {
    for (size_t i = 0; i < empty.size(); ++i) {
        if (empty[i] == c) {
            empty.erase(empty.begin() + i);
            break;
        }
    }
    
    
    for (size_t i = 0; i < cells.size(); ++i) {
        if (cells[i] == c) {
            cells.erase(cells.begin() + i);
            break;
        }
    }
}

bool Chamber::place(Character *c) {
    Cell *cell = chooseRandomCell();
    if (cell == nullptr) return false;
    cell->setCharacter(c);
    c->setCell(cell);
    return true;
}

bool Chamber::place(Item *item) {
    Cell *cell = chooseFromAll();
    if (cell == nullptr) return false;
    
    while (!item->isGeneratable(*cell)) {
        cell = chooseFromAll();
    }
    
    cell->setItem(item);
    item->setCell(cell);
    return true;
}

bool Chamber::place(Item *item, Character *c) {
    Cell *cell = chooseRandomCell();
    if (cell == nullptr) return false;
    
    for (unsigned int i = 0; i < empty.size(); ++i) {
        if (isNeighbor(cell->getRow(), cell->getCol(), empty[i]->getRow(), empty[i]->getCol())) {
            Cell *cell2 = empty[i];
            occupied.emplace_back(cell2);
            empty.erase(empty.begin() + i);
            cell->setItem(item);
            item->setCell(cell);
            cell2->setCharacter(c);
            c->setCell(cell2);
            return true;
        }
    }
    
    // did not find valid neighbor
    empty.emplace_back(cell);
    occupied.pop_back();
    return false;
}

void Chamber::reset() {
    empty.clear();
    occupied.clear();
    cells.clear();
}
