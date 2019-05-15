#include "poisonhealth.h"

#include "orc.h"
#include "elves.h"
#include "dwarf.h"
#include "human.h"
#include "mingyu.h"

PoisonHealth::PoisonHealth() {}

bool PoisonHealth::usedBy(Orc &o) {
    notifyObservers("PC uses PH.");
    o.addHP(-10);
    return true;
}

bool PoisonHealth::usedBy(Elves &e) {
    notifyObservers("PC uses PH (turned RH).");
    e.addHP(10);
    return true;
}

bool PoisonHealth::usedBy(Dwarf &d) {
    notifyObservers("PC uses PH.");
    d.addHP(-10);
    return true;
}

bool PoisonHealth::usedBy(Human &h) {
    notifyObservers("PC uses PH.");
    h.addHP(-10);
    return true;
}

bool PoisonHealth::usedBy(Mingyu &m) {
    notifyObservers("PC uses PH.");
    m.addHP(-10);
    return true;
}
