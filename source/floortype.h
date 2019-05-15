#ifndef _FLOORTYPE_H_
#define _FLOORTYPE_H_

#include <stdexcept>

enum class FloorType {
    DOOR,
    FLOORTILE,
    PASSAGE,
    STAIR,
    VOID,
    VWALL,
    HWALL
};

inline FloorType toFloorType(char c) {
    switch (c) {
        case '+':
            return FloorType::DOOR;
            break;
        case '.':
            return FloorType::FLOORTILE;
            break;
        case '#':
            return FloorType::PASSAGE;
            break;
        case '\\':
            return FloorType::STAIR;
            break;
        case ' ':
            return FloorType::VOID;
            break;
        case '|':
            return FloorType::VWALL;
            break;
        case '-':
            return FloorType::HWALL;
            break;
            
        default:
            break;
    }
    throw logic_error;
}

#endif /* _FLOORTYPE_H_ */
