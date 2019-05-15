#ifndef _VOID_H_
#define _VOID_H_
#include "cell.h"

class Void : public Cell {
public:
    Void(int row, int col);
    ~Void();
    bool isMovable(const Enemy &enemy) const override;
    bool isMovable(const Player &player) const override;
};

#endif
