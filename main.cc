#include <iostream>
#include <vector>
#include <memory>
#include "link.h"
#include "data.h"
#include "virus.h"
#include "gameboard.h"
using namespace std;
int main() {
    char s;
    std::vector<unique_ptr<Link>> links;
    while (std::cin >> s) {
        int strength;
        if (s == 'v') {
            std::cin >> strength;
            links.emplace_back(std::make_unique<Virus>(strength));
        } else if (s == 'd') {
            std::cin >> strength;
            links.emplace_back(std::make_unique<Data>(strength));
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
    }
        unique_ptr<GameBoard> gb = std::make_unique<GameBoard>();
        gb->init();
        cout << *gb;
}
