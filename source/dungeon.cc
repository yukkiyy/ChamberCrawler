#include "dungeon.h"

#include "player.h"
#include "orc.h"
#include "elves.h"
#include "dwarf.h"
#include "human.h"
#include "mingyu.h"

#include "merchant.h"

#include "gamestate.h"
#include "direction.h"
#include "pctype.h"

#include "invalid.h"
#include "playerdead.h"

#include "cheating.h"

#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

// ===== private =====
void Dungeon::nextFloor() {
    ++level;
    notifyObservers("PC has reached Floor " + to_string(level+1) + "!");
    if (level == 5) {
        state = GameState::WON;
    }
    else {
        player->reset();
        floors[level].setPlayer(player);
    }
}

// ===== public  =====

Dungeon::Dungeon() : player(nullptr), level(0), state(GameState::START) {
    for (int i = 0; i < 5; ++i) {
        floors.push_back(Floor{i});
    }
}

Dungeon::~Dungeon() {
    floors.clear();
    delete player;
}

GameState Dungeon::getState() const {
    return state;
}

// ===== for TextDisplay =====
double Dungeon::getPCGold() const {
    return player->getGold();
}

int Dungeon::getPCHP() const {
    return player->getHP();
}

int Dungeon::getPCAtk() const {
    return player->getAtk();
}

int Dungeon::getPCDef() const {
    return player->getDef();
}

double Dungeon::getPCScore() const {
    return player->getScore();
}

int Dungeon::currentLevel() const {
    return level;
}

string Dungeon::getPCRace() const {
    return player->getRace();
}

char Dungeon::getSymbol(int row, int col) const {
    return floors[level].getSymbol(row, col);
}

char Dungeon::getForeground(int row, int col) const {
    return floors[level].getSymbol(row, col);
}

char Dungeon::getBackground(int row, int col) const {
    return floors[level].getBackground(row, col);
}

void Dungeon::setObserver(Observer *observer) {
    this->observer = observer;
    attach(observer);
    for (auto &f : floors) {
        f.setObserver(observer);
    }
}

// ===== for Game =====

void Dungeon::load(const string &filename) {
    if (filename == "default.txt") {
        for (auto &f : floors) {
            f.load();
            f.generate1();
        }
        floors[rand() % 5].placeBarrierSuit();
        
        for (auto &f : floors) {
            f.generate2();
        }
    }
    else {
        for (auto &f : floors) {
            f.load(filename);
        }
    }
}

void Dungeon::enemyTurn() {
    try {
        floors[level].enemyTurn();
    } catch (PlayerDead &e) {
        state = GameState::LOST;
    }
    
}

void Dungeon::move(Direction dir) {
    if (cheatmode) {
        player->addHP(100);
    }
    
    try {
        if (floors[level].move(dir)) {
            nextFloor();
        }
    } catch (Invalid &e) {
        notifyObservers(e.what());
        throw;
    }
}

void Dungeon::use(Direction dir) {
    if (cheatmode) {
        player->addHP(100);
    }
    
    try {
        floors[level].use(dir);
    } catch (PlayerDead &e) {
        state = GameState::LOST;
        throw;
    } catch (Invalid &e) {
        notifyObservers(e.what());
        throw;
    }
}

void Dungeon::attack(Direction dir) {
    if (cheatmode) {
        player->addHP(100);
    }
    
    try {
        floors[level].attack(dir);
    } catch (Invalid &e) {
        notifyObservers(e.what());
        throw;
    }
}


void Dungeon::setPlayer(PCType race) {
    if (race == PCType::ORC) {
        player = new Orc;
    }
    else if (race == PCType::ELVES) {
        player = new Elves;
    }
    else if (race == PCType::DWARF) {
        player = new Dwarf;
    }
    else if (race == PCType::Mingyu) {
        player = new Mingyu;
    }
    else /* if (race == PCType::HUMAN) */ {
        player = new Human;
    }
    
    player->attach(observer);
    floors[level].setPlayer(player);
    
    notifyObservers("Player character has spawned.");
    
    state = GameState::INGAME;
}


void Dungeon::restart() {
    state = GameState::START;
    delete player;
    player = nullptr;
    level = 0;
    cheatmode = false;
    for (auto &f : floors) {
        f.reset();
    }
    Merchant::reset();
}

void Dungeon::transport() {
    nextFloor();
}

void Dungeon::setState(GameState state) {
    this->state = state;
}
