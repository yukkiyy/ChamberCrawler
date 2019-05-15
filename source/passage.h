#ifndef _PASSAGE_H_
#define _PASSAGE_H_
#include "cell.h"

class Passage : public Cell {
public:
    Passage(int row, int col);
    ~Passage();
    bool isMovable(const Enemy &enemy) const override;
    bool isMovable(const Player &player) const override;
};

#endif
