#include "player.h"
#include "utility.h"
#include "cell.h"
#include "playerdead.h"

#include <cmath>
#include <cstdlib>

using namespace std;

int Player::getBoostAtk() const {
    return boostAtk;
}

int Player::getBoostDef() const {
    return boostDef;
}

Player::Player(int HP, int Atk, int Def)
  : Character{'@', HP, Atk, Def},
    boostAtk{0}, boostDef{0}, gold{0.0},
    hasBarrierSuit{false}, hasCompass{false} {}

Player::~Player() {}

void Player::addHP(int hp) {
    setHP(getHP() + hp);
    if (isDead()) throw PlayerDead{};
}

void Player::addAtk(int atk) {
    boostAtk += atk;
    if (getAtk() < 0) {
        boostAtk += abs(getAtk());
    }
}

void Player::addDef(int def) {
    boostDef += def;
    if (getDef() < 0) {
        boostDef += abs(getDef());
    }
}

void Player::addGold(double g) {
    gold += g;
}

void Player::reset() {
    boostAtk = 0;
    boostDef = 0;
    hasCompass = false;
}

void Player::equipBarrierSuit() {
    hasBarrierSuit = true;
}

void Player::equipCompass() {
    hasCompass = true;
}

bool Player::ownCompass() const {
    return hasCompass;
}

bool Player::isMovable(const Cell &c) const {
    return c.isMovable(*this);
}

double Player::getGold() const {
    return gold;
}

double Player::getScore() const {
    return gold;
}

bool Player::attack(Character &c) {
    c.defense(*this);
    return true;
}

void Player::defense(Character &c) {
    string msg{c.getSymbol()};
    
    if (rand() % 2 == 0) {
        msg += " misses attack to PC.";
        notifyObservers(msg);
        return;
    }
    
    int dmg = ceil((100.0 / (100.0 + getDef())) * c.getAtk());
    if (hasBarrierSuit) {
        dmg = ceil(dmg * 0.5);
    }
    
    msg += " deals " + to_string(dmg) + " damage to PC.";
    notifyObservers(msg);
    
    setHP(getHP() - dmg);
    
    if (isDead()) throw PlayerDead{};
}


bool Player::isGeneratable(const Normal &t) const {
    return true;
}

bool Player::isGeneratable(const SmallHorde &t) const {
    return true;
}


