#ifndef _ELVES_H_
#define _ELVES_H_
#include "player.h"

class Elves: public Player{
public:
	Elves();
	~Elves();

	bool use(Item &i) override;
    std::string getRace() const override;
};


#endif
