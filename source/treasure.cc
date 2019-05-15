#include "treasure.h"
#include "utility.h"
#include "invalid.h"

#include "orc.h"
#include "elves.h"
#include "dwarf.h"
#include "human.h"
#include "mingyu.h"

#include <string>

using std::string;
using std::to_string;

Treasure::Treasure(int g) : Item{'G'}, gold{g} {}

Treasure::~Treasure() {}

bool Treasure::usedBy(Orc &o) {
    checkSameCell(o);
    o.addGold(gold * 1.0);

    string msg = "PC has picked up a ";
    if (gold == 1) {
        msg += "Normal pile";
    }
    else if (gold == 2) {
        msg += "Small Horde";
    }
    else if (gold == 4) {
        msg += "Merchant Hoard";
    }
    msg += " of gold.";
    notifyObservers(msg);
    return true;
}

bool Treasure::usedBy(Elves &e) {
    checkSameCell(e);
    e.addGold(gold * 1.0);

    string msg = "PC has picked up a ";
    if (gold == 1) {
        msg += "Normal pile";
    }
    else if (gold == 2) {
        msg += "Small Horde";
    }
    else if (gold == 4) {
        msg += "Merchant Hoard";
    }
    msg += " of gold.";
    notifyObservers(msg);
    return true;
}

bool Treasure::usedBy(Dwarf &d) {
    checkSameCell(d);
    d.addGold(gold * 1.0);

    string msg = "PC has picked up a ";
    if (gold == 1) {
        msg += "Normal pile";
    }
    else if (gold == 2) {
        msg += "Small Horde";
    }
    else if (gold == 4) {
        msg += "Merchant Hoard";
    }
    msg += " of gold.";
    notifyObservers(msg);
    return true;
}

bool Treasure::usedBy(Human &h) {
    checkSameCell(h);
    h.addGold(gold * 1.0);

    string msg = "PC has picked up a ";
    if (gold == 1) {
        msg += "Normal pile";
    }
    else if (gold == 2) {
        msg += "Small Horde";
    }
    else if (gold == 4) {
        msg += "Merchant Hoard";
    }
    msg += " of gold.";
    notifyObservers(msg);
    return true;
}

bool Treasure::usedBy(Mingyu &m) {
    checkSameCell(m);
    m.addGold(gold * 1.0);
    m.addHP(gold);
    
    string msg = "PC has picked up a ";
    if (gold == 1) {
        msg += "Normal pile";
    }
    else if (gold == 2) {
        msg += "Small Horde";
    }
    else if (gold == 4) {
        msg += "Merchant Hoard";
    }
    msg += " of gold, and restores " + to_string(gold) + " HP.";
    notifyObservers(msg);
    return true;
}

string Treasure::peek() const {
    return "unknown treasure";
}
