#ifndef _WOUNDDEF_H_
#define _WOUNDDEF_H_

#include "potion.h"

class WoundDef : public Potion {
public:
    WoundDef();
    bool usedBy(Orc &o) override;
    bool usedBy(Elves &e) override;
    bool usedBy(Dwarf &d) override;
    bool usedBy(Human &h) override;
    bool usedBy(Mingyu &m) override;
};

#endif
