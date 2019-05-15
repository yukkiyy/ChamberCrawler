#ifndef _BOOSTATK_H_
#define _BOOSTATK_H_

#include "potion.h"

class BoostAtk : public Potion {
public:
    BoostAtk();
    bool usedBy(Orc &o) override;
    bool usedBy(Elves &e) override;
    bool usedBy(Dwarf &d) override;
    bool usedBy(Human &h) override;
    bool usedBy(Mingyu &m) override;
};

#endif
