#include "player.hpp"
#include "hashQueue.hpp"
using namespace std;

HashQueue::HashQueue(Player* players, size_t numPlayers):
        queue_{new size_t[9]},
        playerArr_{players},
        numPlayers_{numPlayers} {
    for (size_t league = 0; league < 9; ++league) {
        queue_[league] = numPlayers;
    }
}

HashQueue::~HashQueue(){
    delete[] queue_;
}

size_t HashQueue::findOpponent(size_t playerInd){
    u_int8_t league = playerArr_[playerInd].getLeague();
    // cout << "Player League: " << int(league) << " " << *playerVec_[playerInd] << endl;
    if (league == 9) {
        return numPlayers_;
    //          Empty spot in queue             Player doesn't match against themself
    } else if (queue_[league] != numPlayers_ and queue_[league] != playerInd) {
        size_t oppIndex = queue_[league];
        // cout << *playerVec_[playerInd] << " " << *playerVec_[oppIndex] << " " << flush;
        // Reset queue
        queue_[league] = numPlayers_;
        return oppIndex;
    } else {
        // Add to queue
        queue_[league] = playerInd;
        return numPlayers_;
    }
}

void HashQueue::reset(){
    for (size_t i = 0; i < 9; ++i){
        queue_[i] = numPlayers_;
    }
}

void HashQueue::printToStream(ostream& out) const {
    out << "In queue: ";
    for (size_t i = 0; i < 9; i++)
    {
        out << queue_[i] << " ";
    }
}

ostream& operator<<(ostream& outStream, const HashQueue& h){
    h.printToStream(outStream);
    return outStream;
}