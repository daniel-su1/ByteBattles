#include <iostream>
#include <vector>
#include <memory>
#include "link.h"
#include "data.h"
#include "virus.h"

int main() {
    char s;
    std::vector<std::unique_ptr<Link>> links;
    while (std::cin >> s) {
        int strength;
        std::cin >> strength;

        if (s == 'v') {
            links.push_back(std::make_unique<Virus>(strength));
        } else {
            links.push_back(std::make_unique<Data>(strength));
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
