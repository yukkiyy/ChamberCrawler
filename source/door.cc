#include "door.h"

Door::Door(int row, int col)
  : Cell{'+', row, col} {}

Door::~Door() {}

bool Door::isMovable(const Enemy &enemy) const {
    return false;
}

bool Door::isMovable(const Player &player) const {
    return true;
}
