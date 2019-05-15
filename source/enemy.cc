#include "enemy.h"
#include "cell.h"

#include <cmath>
#include <string>

using namespace std;

void Enemy::dropGold(Character &c) const {
    c.addGold(1.0);
}

Enemy::Enemy(char symbol, int HP, int Atk, int Def, Item *item)
: Character{symbol, HP, Atk, Def}, item{item} {}

Enemy::~Enemy() {}

bool Enemy::setItem(Item *i) {
    if (item != nullptr) return false;
    item = i;
    return true;
}

bool Enemy::placeable() const {
    return item == nullptr;
}

bool Enemy::isMovable(const Cell &c) const {
    return c.isMovable(*this);
}

bool Enemy::attack(Character &c) {
    c.defense(*this);
    return true;
}

void Enemy::defense(Character &c) {
    int dmg = ceil((100.0 / (100.0 + getDef())) * c.getAtk());
    setHP(getHP() - dmg);

    string msg;
    if (isDead()) {
        msg = string(1, getSymbol()) + " has been slain.";
    } else {
        msg = "PC deals " + to_string(dmg) +
                 " damage to " + getSymbol() +
                 " (" + to_string(getHP()) + " HP).";
    }

    notifyObservers(msg);
    
    if (isDead()) {
        if (item != nullptr) {
            dropItem(item);
        }
        dropGold(c);
        selfRemoval();
    }
    
}

bool Enemy::use(Item &i) {
    return false;
}
