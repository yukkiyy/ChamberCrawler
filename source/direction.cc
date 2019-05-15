#include "direction.h"

using namespace std;

bool isDirection(const string &s) {
    return  (s == "no") || (s == "so") ||
    (s == "ea") || (s == "we") ||
    (s == "ne") || (s == "nw") ||
    (s == "se") || (s == "sw");
}

Direction toDirection(const string &s) {
    if (s == "no") return Direction::NO;
    if (s == "so") return Direction::SO;
    if (s == "ea") return Direction::EA;
    if (s == "we") return Direction::WE;
    if (s == "ne") return Direction::NE;
    if (s == "nw") return Direction::NW;
    if (s == "se") return Direction::SE;
    return Direction::SW;
}

/*
 
 c-1  c    c+1
 [NW0] [NO1] [NE2] r-1
 [WE3] [   ] [EA4] r
 [SW5] [SO6] [SE7] r+1
 
 */
Direction toDirection(int n) {
    if (n == 0) return Direction::NW;
    if (n == 1) return Direction::NO;
    if (n == 2) return Direction::NE;
    if (n == 3) return Direction::WE;
    if (n == 4) return Direction::EA;
    if (n == 5) return Direction::SW;
    if (n == 6) return Direction::SO;
    return Direction::SE; // n == 7
}


string toString(Direction d) {
    if (d == Direction::NO) return "North";
    if (d == Direction::SO) return "South";
    if (d == Direction::EA) return "East";
    if (d == Direction::WE) return "West";
    if (d == Direction::NE) return "North East";
    if (d == Direction::NW) return "North West";
    if (d == Direction::SE) return "South East";
    return "South West";
}

/*
 
 c-1  c    c+1
 [NW0] [NO1] [NE2] r-1
 [WE3] [   ] [EA4] r
 [SW5] [SO6] [SE7] r+1
 
 */
int toInt(Direction d) {
    if (d == Direction::NW) return 0;
    if (d == Direction::NO) return 1;
    if (d == Direction::NE) return 2;
    if (d == Direction::WE) return 3;
    if (d == Direction::EA) return 4;
    if (d == Direction::SW) return 5;
    if (d == Direction::SO) return 6;
    return 7; // d == Direction::SE
}

