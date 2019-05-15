#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <string>

/* --- Constants --- */
#define ONESEC 1000000          // one second in us unit
#define FPS 60                  // Frames Per Second
#define BUFFERSIZE 10           // Buffer key string size


#define DIAMETER 24            // default button diameter
#define BORDER (DIAMETER / 2)                // default border
#define WIDTH (DIAMETER * 80)               // default window width
#define HEIGHT (DIAMETER * 32)              // default window height


const int iconNums = 19;

const std::string iconPath = "icons/";

const std::string iconFiles[] = {
    // cell
    "door24.xpm",
    "floortile24.xpm",
    "passage24.xpm",
    "stair24.xpm",
    "wall24.xpm",
    
    // enemy
    "dragon24.xpm",
    "goblin24.xpm",
    "merchant24.xpm",
    "phoenix24.xpm",
    "troll24.xpm",
    "vampire24.xpm",
    "werewolf24.xpm",
    
    // item
    "barriersuit24.xpm",
    "compass24.xpm",
    "potion24.xpm",
    "treasure24.xpm",
    
    // player
    "playerfloortile24.xpm",
    "playerdoor24.xpm",
    "playerpassage24.xpm"
};


#endif /* _CONSTANTS_H_ */
