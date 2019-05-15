#include "elves.h"
#include "item.h"

#include <string>

using namespace std;

Elves::Elves() : Player{140, 30, 10} {}

Elves::~Elves() {}

bool Elves::use(Item &i) {
    return i.usedBy(*this);
}

string Elves::getRace() const {
    return "Elves";
}

