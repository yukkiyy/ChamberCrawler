#ifndef _ORC_H_
#define _ORC_H_
#include "player.h"

class Orc: public Player {
public:
	Orc();
	~Orc();

	bool use(Item &i) override;
    std::string getRace() const override;
    
    void addGold(double g) override;
};


#endif
