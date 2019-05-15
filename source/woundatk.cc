#include "woundatk.h"

#include "orc.h"
#include "elves.h"
#include "dwarf.h"
#include "human.h"
#include "mingyu.h"

WoundAtk::WoundAtk() {}

bool WoundAtk::usedBy(Orc &o) {
    o.addAtk(-5);
    notifyObservers("PC uses WA.");
    return true;
}

bool WoundAtk::usedBy(Elves &e) {
    e.addAtk(5);
    notifyObservers("PC uses WA (turned BA).");
    return true;
}

bool WoundAtk::usedBy(Dwarf &d) {
    d.addAtk(-5);
    notifyObservers("PC uses WA.");
    return true;
}

bool WoundAtk::usedBy(Human &h) {
    h.addAtk(-5);
    notifyObservers("PC uses WA.");
    return true;
}

bool WoundAtk::usedBy(Mingyu &m) {
    m.addAtk(-5);
    notifyObservers("PC uses WA.");
    return true;
}
