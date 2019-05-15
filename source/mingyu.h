#ifndef _MINGYU_H_
#define _MINGYU_H_
#include "player.h"

class Mingyu : public Player {
public:
	Mingyu();
	~Mingyu();
	bool use(Item &i) override;
    std::string getRace() const override;
};


#endif
