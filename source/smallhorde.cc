#include "smallhorde.h"
#include "cell.h"

SmallHorde::SmallHorde() : Treasure{2} {}

bool SmallHorde::isGeneratable(const Cell &c) const {
    return c.isGeneratable(*this);
}
