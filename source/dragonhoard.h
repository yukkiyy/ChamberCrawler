#ifndef _DRAGONHOARD_H_
#define _DRAGONHOARD_H_

#include "treasure.h"

class Enemy;

class DragonHoard : public Treasure {
    Enemy *dragon;
public:
    DragonHoard(Enemy *d);
    bool isMovable() const override;
    bool usedBy(Orc &o) override;
    bool usedBy(Elves &e) override;
    bool usedBy(Dwarf &d) override;
    bool usedBy(Human &h) override;
    bool usedBy(Mingyu &m) override;
};

#endif
