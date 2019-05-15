#ifndef _BARRIERSUIT_H_
#define _BARRIERSUIT_H_

#include "major.h"

class Enemy;

class BarrierSuit : public Major {
    Enemy *dragon;
    
public:
    BarrierSuit(Enemy *d);
    bool isMovable() const override;
    bool usedBy(Orc &o) override;
    bool usedBy(Elves &e) override;
    bool usedBy(Dwarf &d) override;
    bool usedBy(Human &h) override;
    bool usedBy(Mingyu &m) override;
    std::string peek() const override;
};

#endif
