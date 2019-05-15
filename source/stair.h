#ifndef _STAIR_H_
#define _STAIR_H_
#include "cell.h"

class Stair : public Cell {
public:
    Stair(int row, int col);
    ~Stair();
    bool isMovable(const Enemy &enemy) const override;
    bool isMovable(const Player &player) const override;
};

#endif
