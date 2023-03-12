#ifndef SIMULATION_HPP_INCLUDED
#define SIMULATION_HPP_INCLUDED

#include "player.hpp"
#include "hashQueue.hpp"
#include <ostream>
#include <fstream>
#include <string>

class Simulation
{
private:
    
    std::vector<Player> players_;
    u_int8_t goldStepRules_[10];
    u_int8_t stepRequirements_[10];
    u_int8_t levelCaps_[9];
    size_t ultChamps_;
    size_t numPlayers_;
    HashQueue* queue_;
    bool dropLeague_; 

public:

    // Constructors
    Simulation(std::string settings, std::string playerFile);
    ~Simulation();
    Simulation(Simulation &other) = delete;


    size_t runSimulation(float ultPct);
    float runSimulation(size_t numBattles);
};

#endif