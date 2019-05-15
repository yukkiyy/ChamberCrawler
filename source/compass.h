#ifndef _COMPASS_H_
#define _COMPASS_H_

#include "major.h"

class Compass : public Major {
public:
    Compass();
    bool usedBy(Orc &o) override;
    bool usedBy(Elves &e) override;
    bool usedBy(Dwarf &d) override;
    bool usedBy(Human &h) override;
    bool usedBy(Mingyu &m) override;
    std::string peek() const override;
};

#endif
