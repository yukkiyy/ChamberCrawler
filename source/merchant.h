#ifndef _MERCHANT_H_
#define _MERCHANT_H_
#include "enemy.h"


class Merchant: public Enemy{
    static bool hostile;
    void dropGold(Character &c) const override;
public:
    Merchant(Item *hoard);
    ~Merchant();

    bool attack(Character &c) override;
	void defense(Character &c) override;
    static void reset();
};

#endif
