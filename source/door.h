#ifndef _DOOR_H_
#define _DOOR_H_
#include "cell.h"

class Door : public Cell {
public:
    Door(int row, int col);
    ~Door();
    bool isMovable(const Enemy &enemy) const override;
    bool isMovable(const Player &player) const override;
};

#endif
