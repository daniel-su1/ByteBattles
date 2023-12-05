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
    bool linksSet;
    bool abilitiesSet;
    public:
        Player(string playerName, int abilityCount);
        // gettor/accessor functions
        string getPlayerName();
        int getNumVirusDownloads();
        int getNumDataDownloads();
        int getAbilityCount();
        bool isWon();
        bool isLinksSet();
        bool isAbilitiesSet();
        void setNumVirusDownloaded(int newNum);
        void setNumDataDownloaded(int newNum);
        void setLinksSet(bool isSet);
        void setAbilitiesSet(bool isSet);
        void abilityUsed();
        void setIsWon(bool w);
};
#endif
