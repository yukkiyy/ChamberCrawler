#ifndef _DUNGEON_H_
#define _DUNGEON_H_

#include "subject.h"
#include "floor.h"
#include "pctype.h"

#include <vector>

class Observer;
class Player;

enum class GameState;
enum class Direction;

class Dungeon : public Subject {
    Observer *observer;
    
    Player *player;
    std::vector<Floor> floors;
    
    int level;
    GameState state;
    
    void nextFloor();
public:
    Dungeon();
    ~Dungeon();
    
    GameState getState() const;
    void setState(GameState state);
    
    // for TextDisplay
    double getPCGold() const;
    int getPCHP() const;
    int getPCAtk() const;
    int getPCDef() const;
    double getPCScore() const;
    int currentLevel() const;
    std::string getPCRace() const;
    char getSymbol(int row, int col) const;
    char getForeground(int row, int col) const;
    char getBackground(int row, int col) const;
    void setObserver(Observer *observer);
    
    // for Game
    void load(const std::string &filename = "default.txt");
    void enemyTurn();
    
    // Game commands
    void move(Direction dir);
    void use(Direction dir);
    void attack(Direction dir);
    void setPlayer(PCType race = PCType::HUMAN);
    void restart();
    
    // cheating mode
    void transport();
};

#endif
