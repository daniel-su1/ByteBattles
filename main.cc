#include <iostream>
#include <vector>
#include <memory>
#include "link.h"
#include "data.h"
#include "virus.h" // todo: remove all but gameboard
#include "gameboard.h"

int main() {
    string cmd;
    GameBoard gb;
    int moves = 0;

    // You will need to make changes this code.

    while (true) {
        cin >> cmd;
        if (cmd == "new") {
        int n;
        cin >> n;
        }
        else if (cmd == "init") {
        cout << g;
        }
        else if (cmd == "game") {
        cin >> moves;
        }
        else if (cmd == "switch") {
        int r = 0, c = 0;
        cin >> r >> c;
        }
    }

    char s;
    std::vector<std::unique_ptr<Link>> links;
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
}
