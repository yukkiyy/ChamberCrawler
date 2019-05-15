#ifndef _WALL_H_
#define _WALL_H_
#include "cell.h"

class Wall : public Cell {
public:
    Wall(char symbol, int row, int col);
    ~Wall();
    bool isMovable(const Enemy &enemy) const override;
    bool isMovable(const Player &player) const override;
};

#endif
