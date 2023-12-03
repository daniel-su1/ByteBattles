#include "player.h"
#include <iostream>
Player::Player(string playerName, int abilityCount): playerName{playerName}, numVirusDownloaded{0}, numDataDownloaded{0},
    abilityCount{abilityCount}, won{false} {}

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

void Player::setNumVirusDownloaded(int newNum){
    numVirusDownloaded = newNum;
}
void Player::setNumDataDownloaded(int newNum) {
    numDataDownloaded = newNum;
}

