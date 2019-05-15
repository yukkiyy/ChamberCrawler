#include "subject.h"
#include "observer.h"
#include <vector>

using namespace std;

Subject::Subject() {}

Subject::~Subject() {}

void Subject::notifyObservers(const string &action) {
    for (auto &ob : observers) ob->notify(action);
}

void Subject::attach(Observer *ob) {
    
    observers.emplace_back(ob);
    
}
