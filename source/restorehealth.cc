#include "restorehealth.h"

#include "orc.h"
#include "elves.h"
#include "dwarf.h"
#include "human.h"
#include "mingyu.h"

RestoreHealth::RestoreHealth() {}

bool RestoreHealth::usedBy(Orc &o) {
    o.addHP(10);
    notifyObservers("PC uses RH.");
    return true;
}

bool RestoreHealth::usedBy(Elves &e) {
    e.addHP(10);
    notifyObservers("PC uses RH.");
    return true;
}

bool RestoreHealth::usedBy(Dwarf &d) {
    d.addHP(10);
    notifyObservers("PC uses RH.");
    return true;
}

bool RestoreHealth::usedBy(Human &h) {
    h.addHP(10);
    notifyObservers("PC uses RH.");
    return true;
}

bool RestoreHealth::usedBy(Mingyu &m) {
    m.addHP(10);
    notifyObservers("PC uses RH.");
    return true;
}


