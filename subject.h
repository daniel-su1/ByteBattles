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
    void attach(Observer *ob);
    void detach(Observer *ob);
    virtual void notifyObservers() = 0;
};

#endif
