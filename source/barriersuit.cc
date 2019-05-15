#include "barriersuit.h"
#include "invalid.h"

#include "orc.h"
#include "elves.h"
#include "dwarf.h"
#include "human.h"
#include "enemy.h"
#include "mingyu.h"

using std::string;

BarrierSuit::BarrierSuit(Enemy *d)
 : Major{'B'}, dragon{d} {}

bool BarrierSuit::isMovable() const {
    if (!dragon->isDead()) {
        throw Invalid{"INVALID MOVE! The dragon is not dead!"};
    }
    return dragon->isDead();
}

bool BarrierSuit::usedBy(Orc &o) {
    checkSameCell(o);
    if (dragon->isDead()) {
        o.equipBarrierSuit();
        notifyObservers("PC equips the Barrier Suit.");
        return true;
    }
    else {
        throw Invalid{"INVALID USE! The dragon is not dead!"};
    }
}

bool BarrierSuit::usedBy(Elves &e) {
    checkSameCell(e);
    if (dragon->isDead()) {
        e.equipBarrierSuit();
        notifyObservers("PC equips the Barrier Suit.");
        return true;
    }
    else {
        throw Invalid{"INVALID USE! The dragon is not dead!"};
    }
}

bool BarrierSuit::usedBy(Dwarf &d) {
    checkSameCell(d);
    if (dragon->isDead()) {
        d.equipBarrierSuit();
        notifyObservers("PC equips the Barrier Suit.");
        return true;
    }
    else {
        throw Invalid{"INVALID USE! The dragon is not dead!"};
    }
}

bool BarrierSuit::usedBy(Human &h) {
    checkSameCell(h);
    if (dragon->isDead()) {
        h.equipBarrierSuit();
        notifyObservers("PC equips the Barrier Suit.");
        return true;
    }
    else {
        throw Invalid{"INVALID USE! The dragon is not dead!"};
    }
}

bool BarrierSuit::usedBy(Mingyu &m) {
    checkSameCell(m);
    if (dragon->isDead()) {
        m.equipBarrierSuit();
        notifyObservers("PC equips the Barrier Suit.");
        return true;
    }
    else {
        throw Invalid{"INVALID USE! The dragon is not dead!"};
    }
}

string BarrierSuit::peek() const {
    return "a barrier suit";
}
