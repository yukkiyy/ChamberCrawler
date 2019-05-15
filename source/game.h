#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include "dungeon.h"
#include "textdisplay.h"

enum class Direction;
enum class PCType;

class Xwindow;

class Game {
    Dungeon dungeon;
    TextDisplay td;
    std::string filename;
    
    bool quitting;
    
    void playCommandline();
    void playCursor();
    void playGraphics();
    
    void printToCursor();
    
    bool isDirectionKey(char c) const;
    Direction keyToDirection(char c) const;
    
    void repaint(Xwindow &w);
    
    char nextChar(Xwindow &w);

public:
    Game(int argc, char **argv);
    void play();
};

#endif
