#include "compass.h"

#include "orc.h"
#include "elves.h"
#include "dwarf.h"
#include "human.h"
#include "mingyu.h"

using std::string;

Compass::Compass() : Major{'C'} {}

bool Compass::usedBy(Orc &o) {
    checkSameCell(o);
    o.equipCompass();
    notifyObservers("PC equips the Compass.");
    return true;
}

bool Compass::usedBy(Elves &e) {
    checkSameCell(e);
    e.equipCompass();
    notifyObservers("PC equips the Compass.");
    return true;
}

bool Compass::usedBy(Dwarf &d) {
    checkSameCell(d);
    d.equipCompass();
    notifyObservers("PC equips the Compass.");
    return true;
}

bool Compass::usedBy(Human &h) {
    checkSameCell(h);
    h.equipCompass();
    notifyObservers("PC equips the Compass.");
    return true;
}

bool Compass::usedBy(Mingyu &m) {
    checkSameCell(m);
    m.equipCompass();
    notifyObservers("PC equips the Compass.");
    return true;
}

string Compass::peek() const {
    return "a compass";
}
