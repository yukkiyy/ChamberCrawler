#ifndef _BOOSTDEF_H_
#define _BOOSTDEF_H_

#include "potion.h"

class BoostDef : public Potion {
public:
    BoostDef();
    bool usedBy(Orc &o) override;
    bool usedBy(Elves &e) override;
    bool usedBy(Dwarf &d) override;
    bool usedBy(Human &h) override;
    bool usedBy(Mingyu &m) override;
};

#endif
