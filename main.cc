#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <random>
#include <chrono>
#include <algorithm>
#include <random>
#include <chrono>
#include <algorithm>
#include "link.h"
#include "data.h"
#include "virus.h"
#include "player.h"
#include "coords.h"
#include "abilitycard.h"
#include "gameboard.h"
#include "window.h"
#include "graphicsdisplay.h"

using namespace std;

class QuitProgram : public exception {};

void parseArgs(int argc, char* argv[], vector<string>& abilities, vector<vector<string>>& links, bool& graphicsEnabled) {
    const string ARG_ERROR_MSG = "Error, please use the argument options: -ability1 <order>, -ability2 <order>, -link1 <placement-file>, link2 <file> -graphics\n";
    for (int i = 1; i < argc; i++) {
        string curArg = argv[i];
        if (curArg[0] == '-') { // is a flag
            if (curArg == "-ability1") {
                i++; // next argument should be the order of abilities
                string abilitiesOrder = argv[i];
                abilities[0] = abilitiesOrder;
            } else if (curArg == "-ability2") {
                i++; // next argument should be the order of abilities
                string abilitiesOrder = argv[i];
                abilities[1] = abilitiesOrder;
            } else if (curArg == "-link1") {
                i++; // next arg should be a file containing placements

                // take all possible string pos from placementFile, then place into vector linkPlacements
                ifstream placementFile{argv[i]};
                string pos;
                vector<string> linkPlacements; 
                while (placementFile >> pos) { linkPlacements.emplace_back(pos); }

                links[0] = linkPlacements;
            } else if (curArg == "-link2") {
                i++; // next arg should be a file containing placements

                // take all possible string pos from placementFile, then place into vector linkPlacements
                ifstream placementFile{argv[i]};
                string pos;
                vector<string> linkPlacements; 
                while (placementFile >> pos) { linkPlacements.emplace_back(pos); }

                links[1] = linkPlacements;
            } else if (curArg == "-graphics") {
                graphicsEnabled = true;
            } else { // incorrect flag
                throw (logic_error(ARG_ERROR_MSG));
            }
        } else { // passed in argument without a flag
            throw (logic_error(ARG_ERROR_MSG));
        }
    } 
}

unique_ptr<GameBoard> parseCmds(istream& in, unique_ptr<GameBoard> gb, bool isSequence = false) {
    string cmd;
    while (in >> cmd) {
        if (gb->getIsWon()) {
            std::vector<std::shared_ptr<Player>> players = gb->getPlayers();
            cout << "WINNER: ";
            for (size_t i = 0; i < players.size(); i++) {
                if (players[i]->isWon()) {
                    cout << players[i]->getPlayerName() << endl;
                }
            }
            throw QuitProgram();
        }

        try {
            if (cmd == "move") {
                // the next inputs should be the name of the link (a-g, A-G) followed by its direction (up, down, left, right)
                string linkName, direction;
                in >> linkName;
                in >> direction;

                gb->moveLink(linkName, direction);
                cout << *gb;
            } else if (cmd == "abilities") {
                cout << gb->playerAbilities(*gb->getPlayers()[gb->getCurrPlayerIndex()]);
            } else if (cmd == "ability") {
                int abilityId;
                in >> abilityId;
                AbilityType type = gb->getAbilityType(abilityId);
                switch (type) {
                    case AbilityType::FIREWALL: 
                    case AbilityType::WALL: {
                        int xCoord, yCoord;
                        if (in >> xCoord && in >> yCoord) {
                            gb->useAbility(abilityId, xCoord, yCoord);
                        } else {
                            throw (logic_error("Error, please follow:\n\tability <ID> <x> <y>"));
                        }
                        break;
                    } case AbilityType::SKIP: {
                        gb->useAbility(abilityId);
                        break;
                    } default: {
                        string linkName;
                        if (in >> linkName) {
                            gb->useAbility(abilityId, linkName);
                        } else {
                            throw (logic_error("Error, please follow:\n\tability <ID> <linkname>"));
                        }
                        break;
                    }
                }
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
                    gb = parseCmds(sequenceFile, move(gb), true); 
                }
            } else if (cmd == "quit") {
                throw QuitProgram(); // exit game and terminate program
            } else {
                string errorMsg = "Error, please use one of the following commands:\n";
                errorMsg += "\tmove a <dir> where a is a link name (a-g or A-G)\n";
                errorMsg += "\tabilities\n";
                errorMsg += "\tability <N> <x> <y> (FireWall, Wall) or ability <N> <linkName> (others)\n";
                errorMsg += "\tboard\n";
                errorMsg += "\tsequence <file>\n";
                errorMsg += "\tquit\n";                 
                if (isSequence) {
                    throw (invalid_argument(errorMsg)); // invalid arguments from sequence mistakes are thrown into main
                } else {
                    throw (logic_error(errorMsg));
                }
            }
          if (gb->getIsWon()) {
            std::vector<std::shared_ptr<Player>> players = gb->getPlayers();
            cout << "WINNER ";
            for (size_t i = 0; i < players.size(); i++) {
                if (players[i]->isWon()) {
                    cout << players[i]->getPlayerName() << endl;
                }
            }
            throw QuitProgram();
        }

        } catch (invalid_argument& err) {
            throw;
        } catch (logic_error& e) {
            cerr << e.what() << endl;
        }
    }
    return gb;
}

int main(int argc, char* argv[]) {
    unique_ptr<GameBoard> gb = make_unique<GameBoard>();
    gb->init();

    const int PLAYER_COUNT = gb->PLAYER_COUNT;
    vector<string> abilities(PLAYER_COUNT);
    vector<vector<string>> links(PLAYER_COUNT);
    bool graphicsEnabled = false;
    
    // cmd line args
    try {
        // set abilities, links, and graphicsEnabled
        parseArgs(argc, argv, abilities, links, graphicsEnabled);
    } catch (logic_error& err) {
        cerr << err.what();
        return 1; // terminate program with incorrect args
    }

    // init graphics
    unique_ptr<Xwindow> xw = nullptr;
    unique_ptr<GraphicsDisplay> gd = nullptr;
    if (graphicsEnabled){
        xw = make_unique<Xwindow>(500,800);
        gd = make_unique<GraphicsDisplay>(xw.get());
        gb->setGraphicsDisplay(gd.get());
    }
    
    // set abilities and links in gb
    for (int i = 0; i < PLAYER_COUNT; i++) {
        shared_ptr<Player> currPlayer = gb->getPlayers()[i];
        // abilities
        if (abilities[i].empty()) {
            abilities[i] = "LFDSP";
        } // else, it was set by cmd line args
        gb->setAbilities(abilities[i], currPlayer);

        // links
        if (links[i].empty()) {
            // randomize the links' positions
            vector<string> linkPlacements; 
            
            for (int i = 1; i <= gb->BOARD_SIZE / 2; i++) {
                linkPlacements.emplace_back(gb->DATA_DISPLAY_STR + to_string(i));
                linkPlacements.emplace_back(gb->VIRUS_DISPLAY_STR + to_string(i));
            }

            // from shuffle.cc:
            // use a time-based seed for the default seed value
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine rng{seed};
            std::shuffle( linkPlacements.begin(), linkPlacements.end(), rng );
            links[i] = linkPlacements;
        }
        unique_ptr <vector<string>> pLink = make_unique<vector<string>>(links[i]);
        gb->setLinks(move(pLink), currPlayer); // pLink is now nullptr from ownership transfer
    }

    gb->notifyObservers();

    // text commands
    try {
        gb = parseCmds(cin, move(gb));
    } catch (invalid_argument& e) { // if the text commands are incorrect
        cerr << e.what();
    } catch (QuitProgram& q) {
        return 0; // exit program on quit command
    }
}
