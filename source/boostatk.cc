#include "boostatk.h"

#include "orc.h"
#include "elves.h"
#include "dwarf.h"
#include "human.h"
#include "mingyu.h"

BoostAtk::BoostAtk() {}

bool BoostAtk::usedBy(Orc &o) {
    o.addAtk(5);
    notifyObservers("PC uses BA.");
    return true;
}

bool BoostAtk::usedBy(Elves &e) {
    e.addAtk(5);
    notifyObservers("PC uses BA.");
    return true;
}

bool BoostAtk::usedBy(Dwarf &d) {
    d.addAtk(5);
    notifyObservers("PC uses BA.");
    return true;
}

bool BoostAtk::usedBy(Human &h) {
    h.addAtk(5);
    notifyObservers("PC uses BA.");
    return true;
}

bool BoostAtk::usedBy(Mingyu &m) {
    m.addAtk(5);
    notifyObservers("PC uses BA.");
    return true;
}
