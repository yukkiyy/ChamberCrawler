#include "game.h"
#include "cheating.h"

bool cheatmode;

int main(int argc, char *argv[]) {
    cheatmode = false;
    
    Game g{argc, argv};
    g.play();
    return 0;
}
