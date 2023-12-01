#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <optional>
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

        // cmd line args
        const string ARG_ERROR_MSG = "Error, please follow one of these argument options: -ability1 <order>, -ability2 <order>, -link1 <placement-file>, link2 <order> -graphics -enhancements\n";
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

                    Player* player= &(gb.getPlayers()[1]);

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
        
        // text commands
        string cmd;
        while (cin >> cmd) {
            if (cmd == "move") {
                // the next inputs should be the name of the link (a-g, A-G) followed by its direction (up, down, left, right)
                string linkName, direction;
                cin >> linkName;
                cin >> direction;

                // call moveLink and check if there is an error message
                optional<string> result = gb.moveLink(linkName, direction);
                if (result) {
                    string errorMessage = *result;
                    cerr << "Error: " << errorMessage << endl;
                } 
            } else if (cmd == "abilities") {
                cout << gb.playerAbilities(gb.getCurrPlayer());
            } else if (cmd == "ability") {
                
            } else if (cmd == "board") {
                cout << gb;
            } else if (cmd == "sequence") {
                
            } else if (cmd == "quit") {
                break;
            } else {
                cerr << "Error, please use one of the following commands:\n"
                    << "\tmove a <dir> where a is a link name (a-g or A-G)\n"
                    << "\tabilities\n"
                    << "\tability <N> <linkname> (link boost) or ability <N> <x> <y> (firewall)\n"
                    << "\tboard\n"
                    << "\tsequence <file>\n"
                    << "\tquit" << endl; // TODO: add more deets
                    // TODO: ensure nothing is missing from the additional three abilities
            }
        }

    } catch (logic_error& err) {
        cerr << err.what();
    }
}
