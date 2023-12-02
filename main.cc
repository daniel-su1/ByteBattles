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

class QuitProgram : public exception {};

unique_ptr<GameBoard> parseArgs(int argc, char* argv[], unique_ptr<GameBoard> gb) {
    const string ARG_ERROR_MSG = "Error, please use the argument options: -ability1 <order>, -ability2 <order>, -link1 <placement-file>, link2 <order> -graphics -enhancements\n";
    for (int i = 1; i < argc; i++) {
        string curArg = argv[i];
        if (curArg[0] == '-') { // is a flag
            if (curArg == "-ability1") {
                i++; // next argument should be the order of abilities
                string abilitiesOrder = argv[i];
                Player* player= &(gb->getPlayers()[0]);
                gb->setAbilities(abilitiesOrder, player);
            } else if (curArg == "-ability2") {
                i++; // next argument should be the order of abilities
                string abilitiesOrder = argv[i];
                Player* player= &(gb->getPlayers()[1]);
                gb->setAbilities(abilitiesOrder, player);
            } else if (curArg == "-link1") {
                i++; // next arg should be a file containing placements

                // take all possible string pos from placementFile, then place into vector linkPlacements
                ifstream placementFile{argv[i]};
                string pos;
                unique_ptr <vector<string>> linkPlacements = make_unique<vector<string>>(); 
                while (placementFile >> pos) { linkPlacements->emplace_back(pos); }

                Player* player= &(gb->getPlayers()[0]);

                gb->setLinks(std::move(linkPlacements), player); // linkPlacements is now nullptr from ownership transfer
            } else if (curArg == "-link2") {
                i++; // next arg should be a file containing placements

                // take all possible string pos from placementFile, then place into vector linkPlacements
                ifstream placementFile{argv[i]};
                string pos;
                unique_ptr <vector<string>> linkPlacements = make_unique<vector<string>>(); 
                while (placementFile >> pos) { linkPlacements->emplace_back(pos); }

                Player* player= &(gb->getPlayers()[1]);

                gb->setLinks(std::move(linkPlacements), player); // linkPlacements is now nullptr from ownership transfer
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
    return gb;
}

unique_ptr<GameBoard> parseCmds(istream& in, unique_ptr<GameBoard> gb) {
    string cmd;
    while (in >> cmd) {
        try {
            if (cmd == "move") {
                // the next inputs should be the name of the link (a-g, A-G) followed by its direction (up, down, left, right)
                string linkName, direction;
                in >> linkName;
                in >> direction;

                gb->moveLink(linkName, direction);
            } else if (cmd == "abilities") {
                cout << gb->playerAbilities(gb->getPlayers()[gb->getCurrPlayerIndex()]);
            } else if (cmd == "ability") {
                
            } else if (cmd == "board") {
                cout << *gb;
            } else if (cmd == "sequence") {
                // next input should be a file name containing commands
                string fileName;
                in >> fileName;
                ifstream sequenceFile{fileName};
                if (sequenceFile.fail()) {
                    throw (logic_error("Error, file does not exist."));
                } else {
                    gb = parseCmds(sequenceFile, move(gb)); 
                }
            } else if (cmd == "quit") {
                throw QuitProgram(); // exit game and terminate program
            } else {
                string errorMsg = "Error, please use one of the following commands:\n";
                errorMsg += "\tmove a <dir> where a is a link name (a-g or A-G)\n";
                errorMsg += "\tabilities\n";
                errorMsg += "\tability <N> <linkname> (link boost) or ability <N> <x> <y> (firewall)\n";
                errorMsg += "\tboard\n";
                errorMsg += "\tsequence <file>\n";
                errorMsg += "\tquit\n"; 
                // TODO: add more deets
                // TODO: ensure nothing is missing from the additional three abilities
                throw (invalid_argument(errorMsg)); // invalid arguments from text command mistakes are thrown into main
            }
        } catch (invalid_argument& err) {
            throw;
        } catch (logic_error& e) {
            cerr << e.what();
        }
    }
    return gb;
}

int main(int argc, char* argv[]) {
    unique_ptr<GameBoard> gb = make_unique<GameBoard>();
    gb->init();
    
    // cmd line args
    try {
        gb = parseArgs(argc, argv, move(gb)); // temporarily pass ownership of gb to parseArgs, then back to gb.
    } catch (logic_error& err) {
        cerr << err.what();
        return 1; // terminate program with incorrect args
    }

    // text commands
    try {
        gb = parseCmds(cin, move(gb));
    } catch (invalid_argument& e) { // if the text commands are incorrect
        cerr << e.what();
    } catch (QuitProgram& q) {
        return 0; // exit program on quit command
    }
}
