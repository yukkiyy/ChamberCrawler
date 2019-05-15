#include "normal.h"
#include "cell.h"

Normal::Normal() : Treasure{1} {}

bool Normal::isGeneratable(const Cell &c) const {
    return c.isGeneratable(*this);
}
