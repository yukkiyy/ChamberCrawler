#include "stair.h"

Stair::Stair(int row, int col)
: Cell{'\\', row, col, false} {}

Stair::~Stair() {}

bool Stair::isMovable(const Enemy &enemy) const {
    return false;
}

bool Stair::isMovable(const Player &player) const {
    return true;
}
