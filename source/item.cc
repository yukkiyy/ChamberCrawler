#include "item.h"
#include "cell.h"
#include "utility.h"
#include "invalid.h"
#include "player.h"

#include <string>


void Item::checkSameCell(Player &p) {
    if (!sameCell(getRow(), getCol(), p.getRow(), p.getCol())) {
        throw Invalid{"INVALID USE! Player must stand on treasures!"};
    }
}

Item::Item(char symbol) : symbol(symbol), cell(nullptr) {}

Item::~Item() {}

char Item::getSymbol() const {
    return symbol;
}

int Item::getRow() const {
    if (cell == nullptr) return -1;
    return cell->getRow();
}

int Item::getCol() const {
    if (cell == nullptr) return -1;
    return cell->getCol();
}

void Item::setCell(Cell *c) {
    cell = c;
}

bool Item::isMovable() const {
    return true;
}

bool Item::isGeneratable(const Cell &c) const {
    return c.isGeneratable(*this);
}
