#include "player.h"
#include <iostream>
Player::Player(string playerName, int abilityCount): playerName{playerName}, numVirusDownloaded{0}, numDataDownloaded{0},
    abilityCount{abilityCount}, won{false}, linksSet{false}, abilitiesSet{false} {}

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

bool Player::isAbilitiesSet() {
    return abilitiesSet;
}

bool Player::isLinksSet() {
    return linksSet;
}

void Player::setNumVirusDownloaded(int newNum){
    numVirusDownloaded = newNum;
}
void Player::setNumDataDownloaded(int newNum) {
    numDataDownloaded = newNum;
}

void Player::setAbilitiesSet(bool isSet) {
    abilitiesSet = isSet;
}

void Player::setLinksSet(bool isSet) {
    linksSet = isSet;
}

void Player::abilityUsed() {
    abilityCount--;
}

void Player::setIsWon(bool w) {
    won = w;
}

