#include "subject.h"
#include <iostream>
using namespace std;


void Subject::attach(Observer* ob) { observers.emplace_back(ob); }

void Subject::detach(Observer* ob) {
    for (auto it = observers.begin(); it != observers.end();) {
        if (ob == *it)
            it = observers.erase(it);
        else
            it++;
    }
}

void Subject::notifyObservers() {
    for (Observer* ob : observers) {
        std::cout << "calling observers" << std::endl;
    }
}

