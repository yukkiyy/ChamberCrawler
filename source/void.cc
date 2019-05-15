#include "void.h"

Void::Void(int row, int col)
: Cell{' ', row, col} {}

Void::~Void() {}

bool Void::isMovable(const Enemy &enemy) const {
    return false;
}

bool Void::isMovable(const Player &player) const {
    return false;
}


