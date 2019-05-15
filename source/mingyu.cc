#include "mingyu.h"
#include "item.h"

using namespace std;

Mingyu::Mingyu() : Player{200,35,30} {}

Mingyu::~Mingyu() {} 

bool Mingyu::use(Item &i) {
    return i.usedBy(*this);
}

string Mingyu::getRace() const {
	return "Mingyu";
}
