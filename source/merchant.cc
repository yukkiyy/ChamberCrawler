#include "merchant.h"

bool Merchant::hostile = false;


void Merchant::dropGold(Character &c) const {}

Merchant::Merchant(Item *hoard) : Enemy{'M', 30, 70, 5, hoard} {}

Merchant::~Merchant() {}

bool Merchant::attack(Character &c) {
    if (hostile) {
        return this->Enemy::attack(c);
    }
    return false;
}

void Merchant::defense(Character &c) {
    this->Enemy::defense(c);
    if (hostile == false) {
        hostile = true;
        notifyObservers("All Merchants become hostile!");
    }
    
}

void Merchant::reset() {
    Merchant::hostile = false;
}
