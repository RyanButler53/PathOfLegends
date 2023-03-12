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

Simulation::Simulation(string settings, string playerFile, size_t seed){
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
    }
    // Need to get UC step requirement. 
    infile >> stepRequirements_[9];
    infile >> dropLeague;
    goldStepRules_[9] = 255;
    queue_ = new HashQueue(players_);
    mt19937 rng_(seed);
    numPlayers_ = players_.size();
}

Simulation::~Simulation()
{
    delete queue_;
}

float Simulation::runSimulation(size_t numBattles){
    // goal: run a simulation with numBattles battles
    size_t battlesPlayed = 0;
    uniform_real_distribution<double> doubleDist(0, 1);
    uniform_int_distribution<size_t> playerDist(0, players_.size() - 1);

    while (battlesPlayed < numBattles){
        size_t p1 = playerDist(rng_);
        size_t opponent = queue_->findOpponent(p1);
        if (opponent != numPlayers_ and doubleDist(rng_) > players_[p1].getPartyPct()) {
            //play battle
            double randomVal = doubleDist(rng_);
            u_int8_t league = players_[p1].getLeague();
            u_int8_t curToGold = 0;
            players_[p1].playMatch(players_[opponent], randomVal,
                                   goldStepRules_[league], goldStepRules_[league + 1],
                                   stepRequirements_[league+1], dropLeague_);
            ++numBattles;
        }
    }
    // count number of ultimate champs
    for (auto& p : players_){
        if (p.isUC()){
            ++ultChamps_;
        }
    }
    return ultChamps_ / float(numPlayers_);
}

size_t runSimulation(float ultPct){
    return 0;
}