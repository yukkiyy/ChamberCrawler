#ifndef _POISONHEALTH_H_
#define _POISONHEALTH_H_

#include "potion.h"

class PoisonHealth : public Potion {
public:
    PoisonHealth();
    bool usedBy(Orc &o) override;
    bool usedBy(Elves &e) override;
    bool usedBy(Dwarf &d) override;
    bool usedBy(Human &h) override;
    bool usedBy(Mingyu &m) override;
};

#endif
