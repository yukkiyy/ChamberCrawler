#include "passage.h"

Passage::Passage(int row, int col)
: Cell{'#', row, col} {}

Passage::~Passage() {}

bool Passage::isMovable(const Enemy &enemy) const {
    return false;
}

bool Passage::isMovable(const Player &player) const {
    return true;
}
