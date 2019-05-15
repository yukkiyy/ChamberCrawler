#ifndef _NORMAL_H_
#define _NORMAL_H_

#include "treasure.h"

class Normal : public Treasure {
public:
    Normal();
    
    bool isGeneratable(const Cell &c) const override;
};

#endif
