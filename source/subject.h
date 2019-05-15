#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <string>

class Observer;

class Subject {
    std::vector<Observer *> observers;
public:
    Subject();
    virtual ~Subject() = 0;
    void notifyObservers(const std::string &action);
    void attach(Observer *observer);
};

#endif
