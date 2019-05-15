#ifndef _FLOOR_H_
#define _FLOOR_H_
#include <vector>
#include <utility>
#include "chamber.h"
#include "subject.h"

class Observer;
class Cell;
class Player;
class Enemy;
class Item;

enum class Direction;

class Floor : public Subject {
    Observer *observer;
    
    int level;
    std::vector<std::vector<Cell *>> cells;
    std::vector<Chamber> chambers;
    std::vector<Enemy *> enemies;
    std::vector<Item *> items;
    
    Cell *stair;
    Player *player;
    Player *placeHolder;
    int player_chamber;
    
    void placePlayer();
    void placeStair();
    void placePotions();
    void placeGold();
    void placeEnemies();
    void placeCompass();
    
    void assignObserver();
    
    void dfs(std::vector<std::vector<int>> &map, int row, int col, int chamber);
    void assignChamber(std::vector<std::pair<int, int>> &tiles, std::vector<std::vector<int>> &map);
    
    
public:

    Floor(int level);
    Floor(Floor &&other);
    ~Floor();

    
    void setPlayer(Player *p);
    void setObserver(Observer *observer);

    char getSymbol(int row, int col) const;
    char getBackground(int row, int col) const;
    void load(const std::string &filename = "default.txt");
    void generate1();
    void generate2();
    
    void placeBarrierSuit();
    void enemyTurn();
    
    // commands
    bool move(Direction dir);
    void use(Direction dir);
    void attack(Direction dir);
    
    void reset();
    
    std::string peek(int row, int col, Direction dir) const;
};

#endif
