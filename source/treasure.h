#ifndef _TREASURE_H_
#define _TREASURE_H_

#include "item.h"

class Treasure : public Item {
    int gold;
public:
    Treasure(int g);
    ~Treasure() = 0;
    bool usedBy(Orc &o) override;
    bool usedBy(Elves &e) override;
    bool usedBy(Dwarf &d) override;
    bool usedBy(Human &h) override;
    bool usedBy(Mingyu &m) override;
    std::string peek() const override final;
};

#endif
