#ifndef _PCTYPE_H_
#define _PCTYPE_H_

#include <string>

enum class PCType {
    ORC,
    ELVES,
    DWARF,
    HUMAN,
    Mingyu
};

bool isPCType(char c);

PCType toPCType(char c);

#endif /*_PCTYPE_H_ */
