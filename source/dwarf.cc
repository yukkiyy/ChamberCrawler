#include "dwarf.h"
#include "item.h"

#include <string>

using namespace std;

Dwarf::Dwarf() : Player{100, 20, 30} {}

Dwarf::~Dwarf() {}

void Dwarf::addGold(double g) {
    this->Player::addGold(2 * g);
}

bool Dwarf::use(Item &i) {
    return i.usedBy(*this);
}

string Dwarf::getRace() const {
    return "Dwarf";
}
