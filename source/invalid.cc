#include "invalid.h"

using std::string;

Invalid::Invalid(const string &s) : s(s) {}

string Invalid::what() const {
    return s;
}
