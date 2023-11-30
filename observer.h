#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Link;
class GameBoard;

class Observer {
 public:
    virtual void notify(Link& link) = 0;
    virtual void notify(GameBoard& gb) = 0;
    virtual ~Observer();
};

#endif
