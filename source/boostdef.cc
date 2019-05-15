#include "boostdef.h"
#include "subject.h"

#include "orc.h"
#include "elves.h"
#include "dwarf.h"
#include "human.h"
#include "mingyu.h"

BoostDef::BoostDef() {}

bool BoostDef::usedBy(Orc &o) {
    o.addDef(5);
    notifyObservers("PC uses BD.");
    return true;
}

bool BoostDef::usedBy(Elves &e) {
    e.addDef(5);
    notifyObservers("PC uses BD.");
    return true;
}

bool BoostDef::usedBy(Dwarf &d) {
    d.addDef(5);
    notifyObservers("PC uses BD.");
    return true;
}

bool BoostDef::usedBy(Human &h) {
    h.addDef(5);
    notifyObservers("PC uses BD.");
    return true;
}

bool BoostDef::usedBy(Mingyu &m) {
    m.addDef(5);
    notifyObservers("PC uses BD.");
    return true;
}
