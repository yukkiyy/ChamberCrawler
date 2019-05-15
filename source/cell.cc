#include <vector>
#include "cell.h"
#include "item.h"
#include "player.h"
#include "character.h"
#include "utility.h"
#include "direction.h"
#include "invalid.h"

#include "cheating.h"

#include <unordered_map>

using namespace std;

Cell::Cell(char symbol, int row, int col, bool visible)
  : symbol{symbol}, row{row}, col{col}, visible{visible},
item{nullptr}, character{nullptr}, neighbors{8, nullptr} {}

Cell::~Cell() {}

char Cell::getSymbol() const {
    if (character != nullptr) {
        return character->getSymbol();
    }
    if (item != nullptr) {
        return item->getSymbol();
    }
    // is stair and not visible to player
    if (symbol == '\\' && !visible && !cheatmode) {
        return '.';
    }
    return symbol;
}

char Cell::getFloorSymbol() const {
    // is stair and not visible to player
    if (symbol == '\\' && !visible && !cheatmode) {
        return '.';
    }
    return symbol;
}

int Cell::getRow() const {
    return row;
}

int Cell::getCol() const {
    return col;
}

Character *Cell::getCharacter() const {
    return character;
}

void Cell::addNeighbor(Cell *neighbor, int i) {
    neighbors[i] = neighbor;
}

void Cell::replaceNeighbor(Cell *oldnei, Cell *newnei) {
    for (unsigned int i = 0; i < neighbors.size(); ++i) {
        if (neighbors[i] == oldnei) neighbors[i] = newnei;
    }
}

void Cell::replaceSelf(Cell *newone) {
    for (unsigned int i = 0; i < neighbors.size(); ++i) {
        if (neighbors[i] != nullptr) {
            neighbors[i]->replaceNeighbor(this, newone);
        }
    }
}

void Cell::cloneNeighbors(Cell *receiver) {
    for (unsigned int i = 0; i < neighbors.size(); ++i) {
        receiver->addNeighbor(neighbors[i], i);
    }
}

void Cell::setItem(Item *i) {
    item = i;
}

void Cell::setCharacter(Character *c) {
    character = c;
    if (item != nullptr && c != nullptr && c->use(*item)) {
        item = nullptr;
    }
}

void Cell::setVisible(bool v) {
    visible = v;
}

bool Cell::use(Character &c) {
    if (item == nullptr) return false;
    if (c.use(*item)) item = nullptr;
    return true;
}

void Cell::use(Direction d) {
    int dir = toInt(d);
    // if no neighbor in that direction
    if (neighbors[dir] == nullptr) {
        throw Invalid{"INVALID USE! Direction " +
            toString(d) + " has no cell!"};
    }
    
    if (!neighbors[dir]->use(*character)) {
        throw Invalid{"INVALID USE! Direction " +
            toString(d) + " has no item!"};
    }
}

void Cell::attack(Direction d) {
    int dir = toInt(d);
    // if no neighbor in that direction
    if (neighbors[dir] == nullptr) {
        throw Invalid{"INVALID ATTACK! Direction " +
            toString(d) + " has no cell!"};
    }
    
    if (!neighbors[dir]->attack(*character)) {
        throw Invalid{"INVALID ATTACK! Direction " +
            toString(d) + " has no enemy!"};
    }
}

bool Cell::attack(Character &attacker) {
    if (character == nullptr) return false;
    return attacker.attack(*character);
}

string Cell::peek() const {
    if (item == nullptr) return "";
    return item->peek();
}

string Cell::peekNeighbor(Direction d) const {
    string msg = "";
    unordered_map<string, int> peekcount;
    
    // north row
    /*
     c-2  c-1  c   c+1  c+2
     [  ] [++] [++] [++] [  ] r-2
     [  ] [NW] [NO] [NE] [  ] r-1
     [  ] [WE] [**] [EA] [  ] r
     [  ] [SW] [SO] [SE] [  ] r+1
     [  ] [  ] [  ] [  ] [  ] r+2
     */
    /*
     
     c-1  c    c+1
     [NW0] [NO1] [NE2] r-1
     [WE3] [   ] [EA4] r
     [SW5] [SO6] [SE7] r+1
     
     */
    if (d == Direction::NO) {
        if (neighbors[0] != nullptr) ++peekcount[neighbors[0]->peek()];
        if (neighbors[1] != nullptr) ++peekcount[neighbors[1]->peek()];
        if (neighbors[2] != nullptr) ++peekcount[neighbors[2]->peek()];
    }
    /*
     c-2  c-1  c   c+1  c+2
     [++] [++] [++] [  ] [  ] r-2
     [++] [NW] [NO] [NE] [  ] r-1
     [++] [WE] [**] [EA] [  ] r
     [  ] [SW] [SO] [SE] [  ] r+1
     [  ] [  ] [  ] [  ] [  ] r+2
     */
    /*
     
     c-1  c    c+1
     [NW0] [NO1] [NE2] r-1
     [WE3] [   ] [EA4] r
     [SW5] [SO6] [SE7] r+1
     
     */
    else if (d == Direction::NW) {
        if (neighbors[0] != nullptr) ++peekcount[neighbors[0]->peek()];
        if (neighbors[1] != nullptr) ++peekcount[neighbors[1]->peek()];
        if (neighbors[2] != nullptr) ++peekcount[neighbors[2]->peek()];
        if (neighbors[3] != nullptr) ++peekcount[neighbors[3]->peek()];
        if (neighbors[5] != nullptr) ++peekcount[neighbors[5]->peek()];
    }
    /*
     c-2  c-1  c   c+1  c+2
     [  ] [  ] [++] [++] [++] r-2
     [  ] [NW] [NO] [NE] [++] r-1
     [  ] [WE] [**] [EA] [++] r
     [  ] [SW] [SO] [SE] [  ] r+1
     [  ] [  ] [  ] [  ] [  ] r+2
     */
    /*
     
     c-1  c    c+1
     [NW0] [NO1] [NE2] r-1
     [WE3] [   ] [EA4] r
     [SW5] [SO6] [SE7] r+1
     
     */
    else if (d == Direction::NE) {
        if (neighbors[0] != nullptr) ++peekcount[neighbors[0]->peek()];
        if (neighbors[1] != nullptr) ++peekcount[neighbors[1]->peek()];
        if (neighbors[2] != nullptr) ++peekcount[neighbors[2]->peek()];
        if (neighbors[4] != nullptr) ++peekcount[neighbors[4]->peek()];
        if (neighbors[7] != nullptr) ++peekcount[neighbors[7]->peek()];
    }
    // this row
    /*
     c-2  c-1  c   c+1  c+2
     [  ] [  ] [  ] [  ] [  ] r-2
     [++] [NW] [NO] [NE] [  ] r-1
     [++] [WE] [**] [EA] [  ] r
     [++] [SW] [SO] [SE] [  ] r+1
     [  ] [  ] [  ] [  ] [  ] r+2
     */
    /*
     
     c-1  c    c+1
     [NW0] [NO1] [NE2] r-1
     [WE3] [   ] [EA4] r
     [SW5] [SO6] [SE7] r+1
     
     */
    else if (d == Direction::WE) {
        if (neighbors[0] != nullptr) ++peekcount[neighbors[0]->peek()];
        if (neighbors[3] != nullptr) ++peekcount[neighbors[3]->peek()];
        if (neighbors[5] != nullptr) ++peekcount[neighbors[5]->peek()];
    }
    /*
     c-2  c-1  c   c+1  c+2
     [  ] [  ] [  ] [  ] [  ] r-2
     [  ] [NW] [NO] [NE] [++] r-1
     [  ] [WE] [**] [EA] [++] r
     [  ] [SW] [SO] [SE] [++] r+1
     [  ] [  ] [  ] [  ] [  ] r+2
     */
     /*
      
      c-1  c    c+1
      [NW0] [NO1] [NE2] r-1
      [WE3] [   ] [EA4] r
      [SW5] [SO6] [SE7] r+1
      
      */
    else if (d == Direction::EA) {
        if (neighbors[2] != nullptr) ++peekcount[neighbors[2]->peek()];
        if (neighbors[4] != nullptr) ++peekcount[neighbors[4]->peek()];
        if (neighbors[7] != nullptr) ++peekcount[neighbors[7]->peek()];
    }
    // south row
    /*
     c-2  c-1  c   c+1  c+2
     [  ] [  ] [  ] [  ] [  ] r-2
     [  ] [NW] [NO] [NE] [  ] r-1
     [  ] [WE] [**] [EA] [  ] r
     [  ] [SW] [SO] [SE] [  ] r+1
     [  ] [++] [++] [++] [  ] r+2
     */
    /*
     
     c-1  c    c+1
     [NW0] [NO1] [NE2] r-1
     [WE3] [   ] [EA4] r
     [SW5] [SO6] [SE7] r+1
     
     */
    else if (d == Direction::SO) {
        if (neighbors[5] != nullptr) ++peekcount[neighbors[5]->peek()];
        if (neighbors[6] != nullptr) ++peekcount[neighbors[6]->peek()];
        if (neighbors[7] != nullptr) ++peekcount[neighbors[7]->peek()];
    }
    /*
     c-2  c-1  c   c+1  c+2
     [  ] [  ] [  ] [  ] [  ] r-2
     [  ] [NW] [NO] [NE] [  ] r-1
     [++] [WE] [**] [EA] [  ] r
     [++] [SW] [SO] [SE] [  ] r+1
     [++] [++] [++] [  ] [  ] r+2
     */
    /*
     
     c-1  c    c+1
     [NW0] [NO1] [NE2] r-1
     [WE3] [   ] [EA4] r
     [SW5] [SO6] [SE7] r+1
     
     */
    else if (d == Direction::SW) {
        if (neighbors[0] != nullptr) ++peekcount[neighbors[0]->peek()];
        if (neighbors[3] != nullptr) ++peekcount[neighbors[3]->peek()];
        if (neighbors[5] != nullptr) ++peekcount[neighbors[5]->peek()];
        if (neighbors[6] != nullptr) ++peekcount[neighbors[6]->peek()];
        if (neighbors[7] != nullptr) ++peekcount[neighbors[7]->peek()];
    }
    /*
     c-2  c-1  c   c+1  c+2
     [  ] [  ] [  ] [  ] [  ] r-2
     [  ] [NW] [NO] [NE] [  ] r-1
     [  ] [WE] [**] [EA] [++] r
     [  ] [SW] [SO] [SE] [++] r+1
     [  ] [  ] [++] [++] [++] r+2
     */
    /*
     
     c-1  c    c+1
     [NW0] [NO1] [NE2] r-1
     [WE3] [   ] [EA4] r
     [SW5] [SO6] [SE7] r+1
     
     */
    else /* if (d == Direction::SE) */ {
        if (neighbors[2] != nullptr) ++peekcount[neighbors[2]->peek()];
        if (neighbors[4] != nullptr) ++peekcount[neighbors[4]->peek()];
        if (neighbors[5] != nullptr) ++peekcount[neighbors[5]->peek()];
        if (neighbors[6] != nullptr) ++peekcount[neighbors[6]->peek()];
        if (neighbors[7] != nullptr) ++peekcount[neighbors[7]->peek()];
    }
    
    for (auto &p : peekcount) {
        if (p.first != "") {
            if (msg == "") msg = " and sees ";
            if (p.second == 1) {
                // unknown potion / treasure
                if (p.first[0] == 'u') {
                    if (msg != " and sees ") msg += ", ";
                    msg += "an ";
                }
                msg += p.first;
            }
            else {
                
                if (msg != " and sees ") msg += ", ";
                msg += to_string(p.second) + " " + p.first + "s";
            }
        }
    }
    
    return msg;
}



bool Cell::isMovable(const Enemy &enemy) const {
    return (item == nullptr) && (character == nullptr);
}

bool Cell::isMovable(const Player &player) const {
    if (character != nullptr) return false;
    if (item != nullptr) return item->isMovable();
    return true;
}

bool Cell::isGeneratable(const Character &c) const {
    return (item == nullptr) && (character == nullptr);
}

bool Cell::isGeneratable(const Item &i) const {
    return (item == nullptr) && (character == nullptr);
}

bool Cell::isGeneratable(const Normal &t) const {
    if (item != nullptr) return false;
    if (character != nullptr) return character->isGeneratable(t);
    return true;
}
bool Cell::isGeneratable(const SmallHorde &t) const {
    if (item != nullptr) return false;
    if (character != nullptr) return character->isGeneratable(t);
    return true;
}

void Cell::moveTo(Direction d) {
    int dir = toInt(d);
    // if no neighbor in that direction
    if (neighbors[dir] == nullptr) {
        throw Invalid{"INVALID MOVE! Direction " +
                      toString(d) + " has no cell!"};
    }
    if (!character->isMovable(*neighbors[dir])) {
        throw Invalid{"INVALID MOVE! Direction " +
                      toString(d) + " is not movable!"};
    }
    
    character->setCell(neighbors[dir]);
    neighbors[dir]->setCharacter(character);
    character = nullptr;
    
    string msg = neighbors[dir]->peekNeighbor(d);
    notifyObservers("PC moves " + toString(d) + msg + ".");
}

void Cell::randomMove() {
    // check if player is around, if it is, try to attack
    for (unsigned int i = 0; i < neighbors.size(); ++i) {
        if (neighbors[i] != nullptr && neighbors[i]->getSymbol() == '@') {
            // if successful attack, then its turn has finished
            if (neighbors[i]->attack(*character)) return;
        }
    }
    
    // starting random move
    vector<Cell *> choices;
    for (unsigned int i = 0; i < neighbors.size(); ++i) {
        if (neighbors[i] != nullptr && character->isMovable(*neighbors[i])) {
            choices.emplace_back(neighbors[i]);
        }
    }
    
    if (choices.size() > 0) {
        int index = rand() % choices.size();
        choices[index]->setCharacter(character);
        character->setCell(choices[index]);
        character = nullptr;
    }
}
