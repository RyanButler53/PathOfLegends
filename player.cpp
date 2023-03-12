#include "player.hpp"
#include <iostream>
#include <ostream>
#include <algorithm>

using namespace std;


// Player::Player():
//     id_{0}, partyPct_{0.0}, wins_{0}, losses_{0}, oldPB_{5000}, step_{0},
//     kingTower_{11}, cardLevel_{88},league_{0}, ultChamp_{false},
//     inQueue_{false}{
//     }
Player::Player(size_t id, float partyPct, short oldPB, 
                u_int8_t kingTower, u_int8_t cardLevel):
    id_{id}, partyPct_{partyPct}, wins_{0}, losses_{0}, oldPB_{oldPB}, step_{0},
    kingTower_{kingTower}, cardLevel_{cardLevel},league_{0}, ultChamp_{false}
    {
        //nothing to do here
    }


u_int8_t Player::getStep(){
    return step_;
}

size_t Player::getId(){
    return id_;
}

u_int8_t Player:: getKt(){
    return kingTower_;
}

u_int8_t Player::getCl(){
    return cardLevel_;
}

float Player::getPartyPct(){
    return partyPct_;
}

short Player::getWins(){
    return wins_;
}

short Player::getLosses() {
    return losses_;
}

u_int8_t Player::getLeague() {
    return league_;
}

void Player::reset(u_int8_t finishLeague){
    ultChamp_ = false;
    multiplier_ = finishLeague;
    step_ = 0;
}

bool  Player::operator==(const Player& other) const {
    return id_ == other.id_;
}

bool Player::operator!=(const Player& other) const {
    return !(*this == other);
}

bool Player::matchAllowed(Player& other) const {
    // Can only play players in their league
    if (*this == other){ //same player
        return false;
    }
    return league_ == other.league_;
}
void Player::playMatch(Player& other, double randomVal, u_int8_t curToGold,
                         u_int8_t nextToGold, u_int8_t nextLeague, bool dropLeague){

    short pbDiff = abs(oldPB_ - other.oldPB_);
    long double higherPBwins = -0.0000001097213 * pbDiff * pbDiff + 0.00030971 * pbDiff + 0.48544;

    //levels are *very close* on the path.
    // Assume that low levels wrapped up in low old pb
    if ((oldPB_ > other.oldPB_ and randomVal < higherPBwins) or (oldPB_ < other.oldPB_ and randomVal > higherPBwins)){ 
        // ^ player is higher pb and higher pb wins^^        ^ player is lower pb and higher pb loses
        winsMatch(other, curToGold, nextToGold, nextLeague, dropLeague);
        if (league_ == 9){
            ultChamp_ = true;
        }
    } else {
        other.winsMatch(*this, curToGold, nextToGold, nextLeague, dropLeague);
    }
    //player is overleveled
    
}
void Player::winsMatch(Player& other,  u_int8_t curToGold,
                     u_int8_t nextToGold, u_int8_t nextLeague, bool dropLeague){
    // Handle winner
    step_ += multiplier_;
    if (multiplier_ > 1){
        --multiplier_;
    }
    
    // Reach new league, refresh golden steps
    if (step_ == nextLeague){
        ++league_;
        winsToGold_ = nextToGold;
        if (!dropLeague){
            currentGold_ = step_;
        }
    } else if (winsToGold_ == 0) {
        currentGold_ = step_;
        winsToGold_ = curToGold;
    } else if (winsToGold_ != 255) { // gold steps.
        --winsToGold_;
    } // No gold steps, no new league

    // Handle loser
    if (other.step_ != currentGold_){
        --other.step_;
    }
    return;
}

void Player::printToStream(ostream& out) const {

    out << "(" << kingTower_ << "," << cardLevel_ << ", " << step_ <<")" << endl;
}

ostream& operator<<(ostream& outStream, const Player p){
    p.printToStream(outStream);
    return outStream;
}