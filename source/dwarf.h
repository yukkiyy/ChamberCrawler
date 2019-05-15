#ifndef _DWARF_H_
#define _DWARF_H_
#include "player.h"

class Dwarf: public Player {
public:
	Dwarf();
	~Dwarf();

    void addGold(double g) override;
	bool use(Item &i) override;
    std::string getRace() const override;
};

#endif
