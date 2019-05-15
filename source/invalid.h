#ifndef _INVALID_H_
#define _INVALID_H_

#include <string>

class Invalid {
    std::string s;
    
public:
    Invalid(const std::string &s);
    std::string what() const;
};


#endif /* _INVALID_H_ */
