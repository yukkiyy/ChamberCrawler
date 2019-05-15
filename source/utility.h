#ifndef _UTILITY_H_
#define _UTILITY_H_

#include "constants.h"



inline int min(int a, int b) {
    return (a > b ? b : a);
}

inline int max(int a, int b) {
    return (a > b ? a : b);
}


inline int clamp(int low, int value, int high) {
    if (value > high) return high;
    if (value < low) return low;
    return value;
}

inline int abs(int n) {
    return (n < 0 ? -n : n);
}

inline bool isNeighbor(int r1, int c1, int r2, int c2) {
    return (abs(r1 - r2) <= 1) && (abs(c1 - c2) <= 1);
}

inline bool sameCell(int r1, int c1, int r2, int c2) {
    return r1 == r2 && c1 == c2;
}

inline int toCoordsX(int col) {
    return BORDER + col * DIAMETER;
}

inline int toCoordsY(int row) {
    return BORDER + (row+1) * DIAMETER;
}


unsigned long now();

#endif /* _UTILITY_H_ */
