#include "player.hpp"
#include "hashQueue.hpp"
#include <iostream>
using namespace std;

HashQueue::HashQueue(vector<Player> &players) :
        queue_{new size_t[9]},
        playerVec_{players},
        numPlayers{players.size()} {
    for (size_t league = 0; league < 9; ++league) {
        queue_[league] = numPlayers;
    }
}

HashQueue::~HashQueue(){
    delete[] queue_;
}

size_t HashQueue::findOpponent(size_t playerInd){
    u_int8_t league = playerVec_[playerInd].getLeague();
    // there is an opponent that is not the player looking for a match
    if (league == 9){
        return numPlayers;
    } else if (queue_[league] != numPlayers and queue_[league] != playerInd) {
        size_t oppIndex = queue_[league];
        // Reset queue
        queue_[league] = numPlayers;
        return queue_[league];
    } else {
        // Add to queue
        queue_[league] = playerInd;
        return numPlayers;
    }
}

void HashQueue::reset(){
    for (size_t i = 0; i < 9; ++i){
        queue_[i] = numPlayers;
    }
}