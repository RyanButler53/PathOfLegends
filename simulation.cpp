/**
 * @file simulation.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "simulation.hpp"
using namespace std;

Simulation::Simulation(string settings, string playerFile){
    vector<Player> players_;
    u_int8_t kt, cl;
    short oldPB;
    float partyPct;
    u_int8_t toGoldStep;
    bool dropLeague;

    ifstream infile(settings);
    ifstream playersIn(playerFile);
    size_t id = 0;
    while (true)
    {
        playersIn >> kt;
        playersIn >> oldPB;
        playersIn >> partyPct;
        playersIn >> cl;
        players_.push_back(Player{id, partyPct, oldPB, kt, cl});
        ++id;
        if (playersIn.eof()) {
            break;
        }
    }
    for (size_t stepRule = 0; stepRule < 9; ++stepRule) {
        //steps req, gold step, lvl cap
        infile >> stepRequirements_[stepRule];
        infile >> toGoldStep;
        if (toGoldStep == 0){
            toGoldStep = 255;
        }
        goldStepRules_[stepRule] = toGoldStep;
        infile >> levelCaps_[stepRule];
    }
    // Need to get UC step requirement. 
    infile >> stepRequirements_[9];
    infile >> dropLeague;
    goldStepRules_[9] = 255;
    queue_ = new HashQueue(players_);
}

Simulation::~Simulation()
{
    delete queue_;
}
