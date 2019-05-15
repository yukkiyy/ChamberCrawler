#include "character.h"
#include "cell.h"
#include "utility.h"
#include "item.h"

int Character::getBoostAtk() const {
    return 0;
}

int Character::getBoostDef() const {
    return 0;
}

void Character::dropItem(Item *item) {
    cell->setItem(item);
    item->setCell(cell);
}

void Character::selfRemoval() {
    cell->setCharacter(nullptr);
    cell = nullptr;
}

Character::Character(char symbol, int HP, int Atk, int Def)
: symbol{symbol}, HP{HP}, maxHP{HP}, Atk{Atk}, Def{Def} {}

Character::~Character() {}

char Character::getSymbol() const {
    return symbol;
}

int Character::getRow() const {
    if (cell == nullptr) return -1;
    return cell->getRow();
}

int Character::getCol() const {
    if (cell == nullptr) return -1;
    return cell->getCol();
}

int Character::getHP() const {
    return HP;
}

int Character::getAtk() const {
    return getBoostAtk() + Atk;
}

int Character::getDef() const {
    return getBoostDef() + Def;
}

Cell *Character::getCell() const {
    return cell;
}

void Character::setHP(int hp) {
    HP = clamp(0, hp, maxHP);
}

void Character::setCell(Cell *c) {
    cell = c;
}

bool Character::isDead() const {
    return HP == 0;
}

void Character::addGold(double g) {}

bool Character::isGeneratable(const Normal &t) const {
    return false;
}

bool Character::isGeneratable(const SmallHorde &t) const {
    return false;
}
