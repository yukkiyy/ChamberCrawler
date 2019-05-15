#ifndef _POTION_H_
#define _POTION_H_

#include "item.h"

class Potion : public Item {
protected:
    void checkSameCell(Player &p) override;
public:
    Potion();
    bool isMovable() const override;
    std::string peek() const override final;
};

#endif
