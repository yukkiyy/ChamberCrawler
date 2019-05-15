#include "dragonhoard.h"
#include "invalid.h"

#include "orc.h"
#include "elves.h"
#include "dwarf.h"
#include "human.h"
#include "enemy.h"
#include "mingyu.h"

DragonHoard::DragonHoard(Enemy *d)
 : Treasure{6}, dragon{d} {}

bool DragonHoard::isMovable() const {
    if (!dragon->isDead()) {
        throw Invalid{"INVALID MOVE! The dragon is not dead!"};
    }
    return dragon->isDead();
}

bool DragonHoard::usedBy(Orc &o) {
    checkSameCell(o);
    if (dragon->isDead()) {
        o.addGold(6.0);
        notifyObservers("PC has picked up a Dragon Hoard of gold.");
        return true;
    }
    else {
        throw Invalid{"INVALID USE! The dragon is not dead!"};
    }
}

bool DragonHoard::usedBy(Elves &e) {
    checkSameCell(e);
    if (dragon->isDead()) {
        e.addGold(6.0);
        notifyObservers("PC has picked up a Dragon Hoard of gold.");
        return true;
    }
    else {
        throw Invalid{"INVALID USE! The dragon is not dead!"};
    }
}

bool DragonHoard::usedBy(Dwarf &d) {
    checkSameCell(d);
    if (dragon->isDead()) {
        d.addGold(6.0);
        notifyObservers("PC has picked up a Dragon Hoard of gold.");
        return true;
    }
    else {
        throw Invalid{"INVALID USE! The dragon is not dead!"};
    }
}

bool DragonHoard::usedBy(Human &h) {
    checkSameCell(h);
    if (dragon->isDead()) {
        h.addGold(6.0);
        notifyObservers("PC has picked up a Dragon Hoard of gold.");
        return true;
    }
    else {
        throw Invalid{"INVALID USE! The dragon is not dead!"};
    }
}

bool DragonHoard::usedBy(Mingyu &m) {
    checkSameCell(m);
    if (dragon->isDead()) {
        m.addGold(6.0);
        m.addHP(6);
        notifyObservers("PC has picked up a Dragon Hoard of gold, and restores 6 HP.");
        return true;
    }
    else {
        throw Invalid{"INVALID USE! The dragon is not dead!"};
    }
}
