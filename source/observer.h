#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <string>

class Observer {
public:
    virtual ~Observer();
    virtual void notify(const std::string &action) = 0;
};

#endif
