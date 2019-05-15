#ifndef _WOUNDATK_H_
#define _WOUNDATK_H_

#include "potion.h"

class WoundAtk : public Potion {
public:
    WoundAtk();
    bool usedBy(Orc &o) override;
    bool usedBy(Elves &e) override;
    bool usedBy(Dwarf &d) override;
    bool usedBy(Human &h) override;
    bool usedBy(Mingyu &m) override;
};

#endif
