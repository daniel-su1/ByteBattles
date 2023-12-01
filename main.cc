#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "link.h"
#include "data.h"
#include "virus.h"
#include "player.h"
#include "coords.h"
#include "abilitycard.h"
#include "gameboard.h"

using namespace std;

int main(int argc, char* argv[]) {
    try {
        GameBoard gb;
        gb.init();

        // cmd line setup args
        const string ARG_ERROR_MSG = "Error, commands supported are: \n\t -ability1 <order> \n\t -ability2 <order> \n\t -link1 <placement-file> \n\t -link2 <order> \n\t -graphics \n\t -enhancements\n";
        for (int i = 1; i < argc; i++) {
            string curArg = argv[i];
            if (curArg[0] == '-') { // is a flag
                if (curArg == "-ability1") {
                    i++; // next argument should be the order of abilities
                    string abilitiesOrder = argv[i];
                    Player* player= &(gb.getPlayers()[0]);
                    gb.setAbilities(abilitiesOrder, player);
                } else if (curArg == "-ability2") {
                    i++; // next argument should be the order of abilities
                    string abilitiesOrder = argv[i];
                    Player* player= &(gb.getPlayers()[1]);
                    gb.setAbilities(abilitiesOrder, player);
                } else if (curArg == "-link1") {
                    i++; // next arg should be a file containing placements

                    // take all possible string pos from placementFile, then place into vector linkPlacements
                    ifstream placementFile{argv[i]};
                    string pos;
                    unique_ptr <vector<string>> linkPlacements = make_unique<vector<string>>(); 
                    while (placementFile >> pos) { linkPlacements->emplace_back(pos); }

                    Player* player= &(gb.getPlayers()[0]);

                    gb.setLinks(std::move(linkPlacements), player); // linkPlacements is now nullptr from ownership transfer
                } else if (curArg == "-link2") {
                    i++; // next arg should be a file containing placements

                    // take all possible string pos from placementFile, then place into vector linkPlacements
                    ifstream placementFile{argv[i]};
                    string pos;
                    unique_ptr <vector<string>> linkPlacements = make_unique<vector<string>>(); 
                    while (placementFile >> pos) { linkPlacements->emplace_back(pos); }

                    Player* player= &(gb.getPlayers()[0]);

                    gb.setLinks(std::move(linkPlacements), player); // linkPlacements is now nullptr from ownership transfer
                } else if (curArg == "-graphics") {
                    // TODO: deal w graphics
                    // do not need i++ bc theres no args
                    cout << "graphics!!" << endl;
                } else if (curArg == "-enhancements") {
                    // TODO: enhance!
                    cout << "EMNHANCE" << endl;
                } else { // incorrect flag
                    throw (logic_error(ARG_ERROR_MSG));
                }
            } else { // passed in argument without a flag
                throw (logic_error(ARG_ERROR_MSG));
            }
        }

        // text command interactions
        string cmd;
        while (cin >> cmd) {
            if (cmd == "move") {
                // get link name (a-gb and A-gb) and direction (up, down, left, right) from cin
                string link, dir;
                cin >> link;
                cin >> dir;
                gb.movePiece(link, dir);
            } else if (cmd == "abilities") {
                cout << gb.playerAbilities(gb.getCurrPlayer());
            } else if (cmd == "ability") {
                // get ability card's id from cin
                int id;
                cin >> id;
                vector<AbilityCard>& allAbilityCards = gb.getAllAbilityCards();
                unique_ptr<AbilityCard> newCard = make_unique<AbilityCard>(allAbilityCards[id]);
            } else if (cmd == "board") {

            } else if (cmd == "sequence") {

            } else if (cmd == "quit") {
                break;
            } else { // misspelled command
                cerr << "Error, commands supported are: \n\t move <link> <dir> \n\t abilities \n\t ability <ID> \n\t board \n\t sequence <file> \n\t quit\n" << endl;
            }
        }
    } catch (logic_error& err) {
        cerr << err.what();
    }
}

// int oldMain() {
//     string name1 = "Player 1";
//     Player p1(name1, 5);
//     char s;
//     std::vector<unique_ptr<Link>> links;
//     while (std::cin >> s) {
//         int strength;
//         if (s == 'v') {
//             std::cin >> strength;
//             string pieceName = "A";
//             links.emplace_back(std::make_unique<Virus>(strength, Coords(1,1), pieceName, p1));
//         } else if (s == 'd') {
//             std::cin >> strength;
//             string pieceName = "a";
//             links.emplace_back(std::make_unique<Data>(strength, Coords(1,1), pieceName, p1));
//         } else {
//             break;
//         }
//     }
//     for (const auto& link : links) {
//         if (link->getType() == virus) {
//             std::cout << "VIRUS, strength:";
//         } else {
//             std::cout << "DATA, strength:";
//         }
//         std::cout << link->getStrength() << std::endl;
        
//         std::cout << "Owner:" << (link->getOwner()).getPlayerName() << endl;
//     }
//         unique_ptr<GameBoard> gb = std::make_unique<GameBoard>();
//         gb->init();
//         cout << *gb;
// }
