#include <iostream>
#include <vector>
#include <memory>
#include "link.h"
#include "data.h"
#include "virus.h"
#include "player.h"
#include "coords.h"

int main() {
    string name1 = "Player 1";
    Player p1(name1, 5);
    char s;
    std::vector<std::unique_ptr<Link>> links;
    while (std::cin >> s) {
        int strength;
        if (s == 'v') {
            std::cin >> strength;
            string pieceName = "A";
            links.emplace_back(std::make_unique<Virus>(strength, Coords(1,1), pieceName, p1));
        } else if (s == 'd') {
            std::cin >> strength;
            string pieceName = "a";
            links.emplace_back(std::make_unique<Data>(strength, Coords(1,1), pieceName, p1));
        } else {
            break;
        }
    }
    for (const auto& link : links) {
        if (link->getType() == virus) {
            std::cout << "VIRUS, strength:";
        } else {
            std::cout << "DATA, strength:";
        }
        std::cout << link->getStrength() << std::endl;
        
        std::cout << "Owner:" << (link->getOwner()).getPlayerName() << endl;
    }
}
