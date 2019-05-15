#ifndef _RESTOREHEALTH_H_
#define _RESTOREHEALTH_H_

#include "potion.h"

class RestoreHealth : public Potion {
public:
    RestoreHealth();
    bool usedBy(Orc &o) override;
    bool usedBy(Elves &e) override;
    bool usedBy(Dwarf &d) override;
    bool usedBy(Human &h) override;
    bool usedBy(Mingyu &m) override;
};

#endif
