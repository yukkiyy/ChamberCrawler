#include "pctype.h"

#include <string>
#include <cstdlib>

using namespace std;

bool isPCType(char c) {
    return (c == 'h') || (c == 'e') ||
    (c == 'd') || (c == 'o') ||
    (c == 'm') || (c == '?');
}

PCType toPCType(char c) {
    if (c == 'h') return PCType::HUMAN;
    if (c == 'e') return PCType::ELVES;
    if (c == 'd') return PCType::DWARF;
    if (c == 'm') return PCType::Mingyu;
    if (c == 'o') return PCType::ORC;
    
    // random choose one
    int choice = rand() % 5;
    if (choice == 0) return PCType::HUMAN;
    if (choice == 1) return PCType::ELVES;
    if (choice == 2) return PCType::DWARF;
    if (choice == 3) return PCType::Mingyu;
    return PCType::ORC;
}
