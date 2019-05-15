#ifndef _SMALLHORDE_H_
#define _SMALLHORDE_H_

#include "treasure.h"

class SmallHorde : public Treasure {
public:
    SmallHorde();
    
    bool isGeneratable(const Cell &c) const override;
};

#endif
