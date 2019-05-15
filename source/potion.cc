#include "potion.h"

using std::string;

void Potion::checkSameCell(Player &p) {}

Potion::Potion() : Item{'P'} {}

bool Potion::isMovable() const {
    return false;
}

string Potion::peek() const {
    return "unknown potion";
}

