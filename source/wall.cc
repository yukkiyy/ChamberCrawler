#include "wall.h"

Wall::Wall(char symbol, int row, int col)
: Cell{symbol, row, col} {}

Wall::~Wall() {}

bool Wall::isMovable(const Enemy &enemy) const {
    return false;
}

bool Wall::isMovable(const Player &player) const {
    return false;
}


