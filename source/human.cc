#include "human.h"
#include "item.h"

#include <string>
#include <cmath>

using namespace std;

Human::Human() : Player{140, 20, 20} {}

Human::~Human() {}

double Human::getScore() const {
    return this->Player::getScore() * 1.5;
}

bool Human::use(Item &i) {
    return i.usedBy(*this);
}

string Human::getRace() const {
    return "Human";
}
