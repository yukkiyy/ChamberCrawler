#ifndef _FLOORTILE_H_
#define _FLOORTILE_H_
#include "cell.h"

class Floortile : public Cell {
public:
    Floortile(int row, int col);
    ~Floortile();
};

#endif
