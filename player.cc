#include "player.h"
Player::Player(string playerName, int abilityCount): playerName{playerName}, numVirusDownloaded{0}, numDataDownloaded{0},
abilityCount{abilityCount}, won{false} {};

Player::Player(string playerName, int numVirusDownloaded, int numDataDownloaded, int abilityCount, bool won): 
    playerName{playerName}, numVirusDownloaded{numVirusDownloaded}, numDataDownloaded{numDataDownloaded}, 
    abilityCount{abilityCount}, won{won} {}

string Player::getPlayerName() {
    return playerName;
}

int Player::getNumDataDownloads() {
    return numDataDownloaded;
}

int Player::getNumVirusDownloads() {
    return numVirusDownloaded;
}

int Player::getAbilityCount() {
    return abilityCount;
}

bool Player::isWon() {
    return won;
}


