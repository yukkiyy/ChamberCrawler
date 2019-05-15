#include "dragon.h"
#include "item.h"
#include "character.h"
#include "utility.h"

void Dragon::dropGold(Character &c) const {}

Dragon::Dragon() : Enemy{'D', 150, 20, 20} {}

Dragon::~Dragon() {}

bool Dragon::attack(Character &c) {
    if (isNeighbor(c.getRow(), c.getCol(), hoard->getRow(), hoard->getCol())) {
        return this->Enemy::attack(c);
    }
    return false;
}

void Dragon::setHoard(Item *i) {
    hoard = i;
}

bool Dragon::isMovable(const Cell &c) const {
    return false;
}
