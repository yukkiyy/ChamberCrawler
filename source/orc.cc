#include "orc.h"
#include "item.h"

#include <string>
#include <cmath>

using namespace std;

Orc::Orc() : Player{180, 30, 25} {}

Orc::~Orc() {}

bool Orc::use(Item &i) {
    return i.usedBy(*this);
}

string Orc::getRace() const {
    return "Orc";
}

void Orc::addGold(double g) {
    this->Player::addGold(0.5 * g);
}
