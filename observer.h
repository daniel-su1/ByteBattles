#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Link;
class GameBoard;
class Player;
class Wall;
class FireWall;

class Observer {
 public:
    virtual void notify(Link &link) = 0;
    virtual void notify(GameBoard &gb) = 0;
    virtual void notify(Player &p) = 0;
    virtual void notify(FireWall &firewall) = 0;
    virtual void notify(Wall &wall) = 0;
    virtual ~Observer();
};

#endif
