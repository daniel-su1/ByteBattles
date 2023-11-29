#ifndef _SUBJECT_H
#define _SUBJECT_H
#include <vector>
#include <string>
#include <memory>
using namespace std;
class Observer;

class Subject {
 protected:
    vector<Observer*> observers;
 public:
    virtual void attach(Observer *ob) = 0;
    virtual void detach(Observer *ob) = 0;
    virtual void notifyObservers() = 0;
};

#endif
