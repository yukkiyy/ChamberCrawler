#include "wounddef.h"

#include "orc.h"
#include "elves.h"
#include "dwarf.h"
#include "human.h"
#include "mingyu.h"

WoundDef::WoundDef() {}

bool WoundDef::usedBy(Orc &o) {
    o.addDef(-5);
    notifyObservers("PC uses WD.");
    return true;
}

bool WoundDef::usedBy(Elves &e) {
    e.addDef(5);
    notifyObservers("PC uses WD (turned BD).");
    return true;
}

bool WoundDef::usedBy(Dwarf &d) {
    d.addDef(-5);
    notifyObservers("PC uses WD.");
    return true;
}

bool WoundDef::usedBy(Human &h) {
    h.addDef(-5);
    notifyObservers("PC uses WD.");
    return true;
}

bool WoundDef::usedBy(Mingyu &m) {
    m.addDef(-5);
    notifyObservers("PC uses WD.");
    return true;
}
