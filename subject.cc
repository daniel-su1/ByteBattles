#include "subject.h"
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
