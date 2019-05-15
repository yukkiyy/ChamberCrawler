#ifndef _HUMAN_H_
#define _HUMAN_H_
#include "player.h"

class Human: public Player{
public:
	Human();
	~Human();

	double getScore() const override;
	bool use(Item &i) override;
    std::string getRace() const override;
};


#endif
