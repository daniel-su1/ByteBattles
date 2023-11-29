#include "player.h"

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


