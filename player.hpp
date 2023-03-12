/**
 * @file player.hpp
 * @author Nova Light (keymckeyface@gmail.com)
 * @brief Player class that supports a model of a CR ladder player
 * @version 0.1
 * @date 2022-03-11
 * 
 * @copyright Copyright (c) 2022. MIT lisence
 * 
 */

#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <iostream>
#include <ostream>
#include <random>
#include <algorithm>


class Player
{
private:
    size_t id_;
    float partyPct_; 
    short wins_;
    short losses_;
    short oldPB_;
    u_int8_t step_;
    u_int8_t kingTower_;
    u_int8_t cardLevel_;
    u_int8_t league_;
    u_int8_t multiplier_;
    u_int8_t winsToGold_;
    u_int8_t currentGold_;
    bool ultChamp_;

public:
    // constructors and destructors
    Player() = delete; // default constructor
    Player(size_t id, float partyPct, short oldPB, u_int8_t kingTower, u_int8_t cardLevel);
    Player(const Player &other) = default; // copy constructor
    ~Player() = default;
    Player &operator=(const Player &other);

    // methods

    // Getters
    u_int8_t getStep();
    size_t getId();
    u_int8_t getKt();
    u_int8_t getCl();
    float getPartyPct();
    short getWins();
    short getLosses();
    u_int8_t getLeague();


    /**
     * @brief Plays a match with another player
     * @param other player to play match against
     */
    void playMatch(Player& other, double randomVal, u_int8_t curToGold,
                         u_int8_t nextToGold, u_int8_t nextLeague, bool dropLeague);

    /**
     * @brief updates players when a match is played
     * 
     * @param other the player that *this won against
     * @param curToGold number fo wins for a golden step in this league
     * @param nextToGold number of wins for gold in next league
     * @param nextLeague number of steps required for next league
     */
    void winsMatch(Player &other, u_int8_t curToGold, u_int8_t nextToGold,
                     u_int8_t nextLeague, bool dropleague);
    /**
     * @brief Checks if a match is allowed to happen
     *
     * @param other Player to possibly match against
     * @param mmType Type of mm rule: 0 = KT, 1 = CL, 2 = none
     * @return true Match is allowed to happen -> play match
     * @return false Match is not allowed -> add to queue tree
     */
    bool matchAllowed(Player& other) const;


    void reset(u_int8_t finishLeague);

    /**
     * @brief Checks if 2 players are identical
     *
     * @param other player to check against
     * @return true players are equal  (equal ids)
     * @return false players are distinct
     */
    bool operator==(const Player& other) const;

    bool operator!=(const Player& other) const;

    /**
     * @brief prints out the player
     * 
     * @param out ostream to modify
     */
    void printToStream(std::ostream& out) const;
};

// Non Class methods

std::ostream& operator<<(std::ostream& outStream, const Player& p);

#endif