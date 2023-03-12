#ifndef HASHQUEUE_HPP_INCLUDED
#define HASHQUEUE_HPP_INCLUDED

#include "player.hpp"
#include <vector>

class HashQueue {
    private:
        std::vector<Player> playerVec_;
        // Queue array stores index in playerVec
        size_t* queue_;
        size_t numPlayers;

    public:
        HashQueue(std::vector<Player>& players);
        ~HashQueue();

        /**
         * @brief Finds an opponent for the player
         * 
         * @param player Player index in vector to find an opponent
         * @return size_t If there is an opponent, return that opponent and clear the queue. 
         * If not, add to queue. 
         * Constant time. 
         */
        size_t findOpponent(size_t playerInd);

        /**
         * @brief Perform season reset. Empty the queue. 
         * 
         */
        void reset();
};

#endif