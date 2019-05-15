#include "floor.h"
#include "item.h"
#include "observer.h"
#include "direction.h"
#include "utility.h"

#include "player.h"
#include "human.h"

#include "cell.h"
#include "stair.h"
#include "wall.h"
#include "floortile.h"
#include "door.h"
#include "passage.h"
#include "void.h"

#include "potion.h"
#include "boostatk.h"
#include "boostdef.h"
#include "woundatk.h"
#include "wounddef.h"
#include "restorehealth.h"
#include "poisonhealth.h"

#include "treasure.h"
#include "normal.h"
#include "smallhorde.h"
#include "merchanthoard.h"
#include "dragonhoard.h"

#include "enemy.h"
#include "dragon.h"
#include "werewolf.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "phoenix.h"
#include "merchant.h"

#include "compass.h"
#include "barriersuit.h"

#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;


void Floor::placePlayer() {
    player_chamber = rand() % 5;
    Cell *c = chambers[player_chamber].chooseRandomCell();
    c->setCharacter(placeHolder);
    placeHolder->setCell(c);
}

void Floor::placeStair() {
    int index = rand() % 5;
    while (index == player_chamber) index = rand() % 5;
    Cell *c = chambers[index].chooseRandomCell();
    chambers[index].removeCell(c);
    stair = new Stair{c->getRow(), c->getCol()};
    c->replaceSelf(stair);
    c->cloneNeighbors(stair);
    cells[c->getRow()][c->getCol()] = stair;
    delete c;
}

void Floor::placePotions() {
    for (int i = 0; i < 10; ++i) {
        Potion *p = nullptr;
        int result = rand() % 6;
        if (result == 0) {
            p = new RestoreHealth;
        }
        else if (result == 1) {
            p = new BoostAtk;
        }
        else if (result == 2) {
            p = new BoostDef;
        }
        else if (result == 3) {
            p = new PoisonHealth;
        }
        else if (result == 4) {
            p = new WoundAtk;
        }
        else /* if (result == 5) */ {
            p = new WoundDef;
        }
        
        // busy looping until find an available cell and place
        while (!chambers[rand() % 5].place(p));
        
        items.emplace_back(p);
    }
}

void Floor::placeGold() {
    for (int i = 0; i < 10; ++i) {
        Treasure *t = nullptr;
        int result = rand() % 8;
        if (result < 5) {
            t = new Normal;
        }
        else if (result < 7) {
            t = new SmallHorde;
        }
        else /* if (result == 7) */ {
            Dragon *dragon = new Dragon;
            t = new DragonHoard{dragon};
            dragon->setHoard(t);
            while (!chambers[rand() % 5].place(t, dragon));
            
            items.emplace_back(t);
            enemies.emplace_back(dragon);
            
            continue;
        }
        
        // busy looping until find an available cell and place
        while (!chambers[rand() % 5].place(t));
        
        items.emplace_back(t);
    }
}

void Floor::placeEnemies() {
    int remainspot = 20 - (int)enemies.size();
    for (int i = 0; i < remainspot; ++i) {
        int result = rand() % 18;
        Enemy *e = nullptr;
        if (result < 4) {
            e = new Werewolf;
        }
        else if (result < 7) {
            e = new Vampire;
        }
        else if (result < 12) {
            e = new Goblin;
        }
        else if (result < 14) {
            e = new Troll;
        }
        else if (result < 16) {
            e = new Phoenix;
        }
        else /* if (result < 18) */ {
            MerchantHoard *mh = new MerchantHoard;
            items.emplace_back(mh);
            e = new Merchant{mh};
        }
        
        // busy looping until find an available cell and place
        while (!chambers[rand() % 5].place(e));
        
        enemies.emplace_back(e);
    }
}

void Floor::placeCompass() {
    Compass *compass = new Compass;
    items.emplace_back(compass);
    // iteratively place compass until succeed
    while (!enemies[rand() % enemies.size()]->setItem(compass));
}

void Floor::assignObserver() {
    for (auto &rows : cells) {
        for (auto &c : rows) {
            c->attach(observer);
        }
    }
    
    for (auto &e : enemies) {
        e->attach(observer);
    }
    
    for (auto &i : items) {
        i->attach(observer);
    }
}

void Floor::dfs(vector<vector<int>> &map, int row, int col, int chamber) {
    if (row < 0 || col < 0 ||
        row > 24 || col > 78 ||
        map[row][col] != -1) return;
    map[row][col] = chamber;
    dfs(map, row-1, col, chamber);
    dfs(map, row+1, col, chamber);
    dfs(map, row, col-1, chamber);
    dfs(map, row, col+1, chamber);
}

void Floor::assignChamber(vector<pair<int, int>> &tiles,
                          vector<vector<int>> &map) {
    int chamber = 0;
    for (auto &t : tiles) {
        if (map[t.first][t.second] == -1) {
            dfs(map, t.first, t.second, chamber);
            ++chamber;
        }
    }
    
    for (auto &t : tiles) {
        chambers[map[t.first][t.second]].addCell(cells[t.first][t.second]);
    }
}

// ===== public =====

Floor::Floor(int level)
: level{level}, cells{25, vector<Cell *>(79, nullptr)},
chambers{5, Chamber{}}, stair{nullptr},
player{nullptr}, placeHolder{new Human},
player_chamber{0}
{}

Floor::Floor(Floor &&other)
: level{other.level}, cells{other.cells}, chambers{other.chambers},
enemies{other.enemies}, items{other.items}, stair{other.stair},
player{other.player}, placeHolder{other.placeHolder} {
    
    other.cells.clear();
    other.chambers.clear();
    other.stair = nullptr;
    other.player = nullptr;
    other.placeHolder = nullptr;
}


Floor::~Floor() {
    for (auto &row : cells) {
        for (auto &cell : row) {
            delete cell;
        }
    }
    
    for (auto &enemy : enemies) {
        delete enemy;
    }
    
    for (auto &item : items) {
        delete item;
    }
    
    delete placeHolder;
}

void Floor::setPlayer(Player *p) {
    p->setCell(cells[placeHolder->getRow()][placeHolder->getCol()]);
    cells[placeHolder->getRow()][placeHolder->getCol()]->setCharacter(p);
    player = p;
    assignObserver();
}

void Floor::setObserver(Observer *observer) {
    this->observer = observer;
    attach(observer);
}

char Floor::getSymbol(int row, int col) const {
    return cells[row][col]->getSymbol();
}

char Floor::getBackground(int row, int col) const {
    return cells[row][col]->getFloorSymbol();
}

void Floor::load(const string &filename) {
    ifstream in{filename};
    string line;
    // skip first level floors
    for (int i = 0; i < level; ++i) {
        for (int j = 0; j < 25; ++j) {
            getline(in, line);
        }
    }
    
    
    vector<pair<int, int>> tiles;
    vector<vector<int>> map{25, vector<int>(79, -2)};
    
    vector<Dragon *> dragons;
    vector<pair<int, int>> dragonhoards;
    
    pair<int, int> barriersuitloc{-1, -1};
    bool hasCompass = false;
    
    for (int row = 0; row < 25; ++row) {
        getline(in, line);
        for (int col = 0; col < 79; ++col) {
            char c = line[col];
            if (c == ' ') {
                cells[row][col] = new Void{row, col};
            }
            else if (c == '+') {
                cells[row][col] = new Door{row, col};
            }
            else if (c == '#') {
                cells[row][col] = new Passage{row, col};
            }
            else if (c == '\\') {
                cells[row][col] = new Stair{row, col};
                stair = cells[row][col];
            }
            else if (c == '|' || c == '-') {
                cells[row][col] = new Wall{c, row, col};
            }
            else {
                cells[row][col] = new Floortile{row, col};
                map[row][col] = -1;
                tiles.emplace_back(row, col);
                
                if (c == '@') {
                    cells[row][col]->setCharacter(placeHolder);
                    placeHolder->setCell(cells[row][col]);
                }
                // enemies
                else if (c == 'V') {
                    Enemy *e = new Vampire;
                    enemies.emplace_back(e);
                    cells[row][col]->setCharacter(e);
                    e->setCell(cells[row][col]);
                }
                else if (c == 'W') {
                    Enemy *e = new Werewolf;
                    enemies.emplace_back(e);
                    cells[row][col]->setCharacter(e);
                    e->setCell(cells[row][col]);
                }
                else if (c == 'N') {
                    Enemy *e = new Goblin;
                    enemies.emplace_back(e);
                    cells[row][col]->setCharacter(e);
                    e->setCell(cells[row][col]);
                }
                else if (c == 'M') {
                    MerchantHoard *mh = new MerchantHoard;
                    items.emplace_back(mh);
                    Enemy *e = new Merchant{mh};
                    enemies.emplace_back(e);
                    cells[row][col]->setCharacter(e);
                    e->setCell(cells[row][col]);
                }
                else if (c == 'D') {
                    Dragon *e = new Dragon;
                    enemies.emplace_back(e);
                    cells[row][col]->setCharacter(e);
                    e->setCell(cells[row][col]);
                    dragons.emplace_back(e);
                }
                else if (c == 'X') {
                    Enemy *e = new Phoenix;
                    enemies.emplace_back(e);
                    cells[row][col]->setCharacter(e);
                    e->setCell(cells[row][col]);
                }
                else if (c == 'T') {
                    Enemy *e = new Troll;
                    enemies.emplace_back(e);
                    cells[row][col]->setCharacter(e);
                    e->setCell(cells[row][col]);
                }
                // items
                else if (c == '0') {
                    Item *i = new RestoreHealth;
                    items.emplace_back(i);
                    cells[row][col]->setItem(i);
                    i->setCell(cells[row][col]);
                }
                else if (c == '1') {
                    Item *i = new BoostAtk;
                    items.emplace_back(i);
                    cells[row][col]->setItem(i);
                    i->setCell(cells[row][col]);
                }
                else if (c == '2') {
                    Item *i = new BoostDef;
                    items.emplace_back(i);
                    cells[row][col]->setItem(i);
                    i->setCell(cells[row][col]);
                }
                else if (c == '3') {
                    Item *i = new PoisonHealth;
                    items.emplace_back(i);
                    cells[row][col]->setItem(i);
                    i->setCell(cells[row][col]);
                }
                else if (c == '4') {
                    Item *i = new WoundAtk;
                    items.emplace_back(i);
                    cells[row][col]->setItem(i);
                    i->setCell(cells[row][col]);
                }
                else if (c == '5') {
                    Item *i = new WoundDef;
                    items.emplace_back(i);
                    cells[row][col]->setItem(i);
                    i->setCell(cells[row][col]);
                }
                else if (c == '6') {
                    Item *i = new Normal;
                    items.emplace_back(i);
                    cells[row][col]->setItem(i);
                    i->setCell(cells[row][col]);
                }
                else if (c == '7') {
                    Item *i = new SmallHorde;
                    items.emplace_back(i);
                    cells[row][col]->setItem(i);
                    i->setCell(cells[row][col]);
                }
                else if (c == '8') {
                    Item *i = new MerchantHoard;
                    items.emplace_back(i);
                    cells[row][col]->setItem(i);
                    i->setCell(cells[row][col]);
                }
                else if (c == '9') {
                    dragonhoards.emplace_back(row, col);
                }
                else if (c == 'C') {
                    hasCompass = true;
                    Item *i = new Compass;
                    items.emplace_back(i);
                    cells[row][col]->setItem(i);
                    i->setCell(cells[row][col]);
                }
                else if (c == 'B') {
                    barriersuitloc = {row, col};
                }
            }
        }
    }
    
    /*
     
     c-1   c     c+1
     [NW0] [NO1] [NE2] r-1
     [WE3] [   ] [EA4] r
     [SW5] [SO6] [SE7] r+1
     
     */
    for (int r = 0; r < 25; ++r) {
        for (int c = 0; c < 79; ++c) {
            if (r > 0 && c > 0)   cells[r][c]->addNeighbor(cells[r-1][c-1], 0);
            if (r > 0)            cells[r][c]->addNeighbor(cells[r-1][c], 1);
            if (r > 0 && c < 78)  cells[r][c]->addNeighbor(cells[r-1][c+1], 2);
            if (c > 0)            cells[r][c]->addNeighbor(cells[r][c-1], 3);
            if (c < 78)           cells[r][c]->addNeighbor(cells[r][c+1], 4);
            if (r < 24 && c > 0)  cells[r][c]->addNeighbor(cells[r+1][c-1], 5);
            if (r < 24)           cells[r][c]->addNeighbor(cells[r+1][c], 6);
            if (r < 24 && c < 78) cells[r][c]->addNeighbor(cells[r+1][c+1], 7);
        }
    }
    
    // if it is default map, then do full random generation
    if (filename == "default.txt") {
        assignChamber(tiles, map);
        return;
    }
    
    if (!hasCompass) placeCompass();
    
    for (auto &p : dragonhoards) {
        for (unsigned int i = 0; i < dragons.size(); ++i) {
            if (isNeighbor(p.first, p.second,
                           dragons[i]->getRow(), dragons[i]->getCol())) {
                Dragon *d = dragons[i];
                dragons.erase(dragons.begin() + i);
                DragonHoard *dh = new DragonHoard{d};
                d->setHoard(dh);
                items.emplace_back(dh);
                cells[p.first][p.second]->setItem(dh);
                dh->setCell(cells[p.first][p.second]);
                break;
            }
        }
    }
    
    if (barriersuitloc.first != -1) {
        Dragon *d = dragons[0];
        if (!isNeighbor(barriersuitloc.first, barriersuitloc.second,
                        d->getRow(), d->getCol())) {
            throw logic_error{"Last dragon <" +
                to_string(d->getRow()) + ", " + to_string(d->getCol()) +
                "> could not be paired with BarrierSuit <" +
                to_string(barriersuitloc.first) + ", " +
                to_string(barriersuitloc.second) + ">"};
        }
        BarrierSuit *bs = new BarrierSuit{d};
        d->setHoard(bs);
        items.emplace_back(bs);
        cells[barriersuitloc.first][barriersuitloc.second]->setItem(bs);
        bs->setCell(cells[barriersuitloc.first][barriersuitloc.second]);
    }
}

void Floor::generate1() {
    placePlayer();
    placeStair();
    placePotions();
    placeGold();
}

void Floor::generate2() {
    placeEnemies();
    placeCompass();
}

void Floor::placeBarrierSuit() {
    Dragon *dragon = new Dragon;
    BarrierSuit *bs = new BarrierSuit{dragon};
    dragon->setHoard(bs);
    while (!chambers[rand() % 5].place(bs, dragon));
    
    items.emplace_back(bs);
    enemies.emplace_back(dragon);
}

void Floor::enemyTurn() {
    queue<Character *> q;
    
    for (int row = 0; row < 25; ++row) {
        for (int col = 0; col < 79; ++col) {
            Character *c = cells[row][col]->getCharacter();
            if (c != nullptr && !c->isDead() && c != player) {
                q.push(c);
            }
        }
    }
    
    while (!q.empty()) {
        Character *c = q.front();
        q.pop();
        cells[c->getRow()][c->getCol()]->randomMove();
    }
}


bool Floor::move(Direction dir) {
    cells[player->getRow()][player->getCol()]->moveTo(dir);
    if (player->ownCompass()) stair->setVisible(true);
    if (sameCell(player->getRow(), player->getCol(),
                 stair->getRow(), stair->getCol())) return true;
    return false;
}

void Floor::use(Direction dir) {
    cells[player->getRow()][player->getCol()]->use(dir);
}



void Floor::attack(Direction dir) {
    cells[player->getRow()][player->getCol()]->attack(dir);
}

void Floor::reset() {
    for (int row = 0; row < 25; ++row) {
        for (int col = 0; col < 79; ++col) {
            delete cells[row][col];
            cells[row][col] = nullptr;
        }
    }
    
    for (auto &enemy : enemies) {
        delete enemy;
    }
    
    enemies.clear();
    
    for (auto &item : items) {
        delete item;
    }
    
    items.clear();
    
    for (auto &c : chambers) {
        c.reset();
    }
    
    delete placeHolder;
    placeHolder = new Human;
    stair = nullptr;
}
