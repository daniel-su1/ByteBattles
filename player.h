#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;
class Player {
    string playerName;
    int numVirusDownloaded;
    int numDataDownloaded;
    int abilityCount;
    bool won;
    public:
    // gettor/accessor functions
    string getPlayerName();
    int getNumVirusDownloads();
    int getNumDataDownloads();
    int getAbilityCount();
    bool isWon();
};
#endif
