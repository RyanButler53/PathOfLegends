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

Simulation::Simulation(string settings, string playerFile, size_t seed, size_t numPlayers, string outputFile){
    vector<Player> players_;
    numPlayers_ = numPlayers;
    u_int8_t kt, cl;
    short oldPB;
    float partyPct;
    u_int8_t toGoldStep;
    bool dropLeague;

    // bug; incorrent values are being read in. Issue with unsigned char types? 

    ifstream infile(settings);
    ifstream playersIn(playerFile);
    cout << "file contents:" << endl;
    for (size_t stepRule = 0; stepRule < 9; ++stepRule) {
        //steps req, gold step, lvl cap
        infile >> stepRequirements_[stepRule];
        infile >> toGoldStep;
        if (toGoldStep == 0){
            toGoldStep = 255;
        }
        goldStepRules_[stepRule] = toGoldStep;
    }
    size_t id = 0;
    for (size_t id = 0; id < numPlayers; ++id)
    {
        playersIn >> kt;
        playersIn >> oldPB;
        playersIn >> partyPct;
        playersIn >> cl;
        players_.push_back(Player{id, partyPct, oldPB, kt, cl, goldStepRules_[0]});
    }
    // Need to get UC step requirement. 
    infile >> stepRequirements_[9];
    infile >> dropLeague;
    infile >> maxMultiplier_;
    goldStepRules_[9] = 255;
    queue_ = new HashQueue(players_);
    mt19937 rng_(seed);
    uniform_int_distribution<size_t> playerDist(0, numPlayers_ - 1);
    
}

Simulation::~Simulation()
{
    delete queue_;
}

float Simulation::nBattlesSimulation(size_t numBattles){
    size_t battlesPlayed = 0;
    uniform_real_distribution<double> doubleDist(0, 1);
    uniform_int_distribution<size_t> playerDist(0, numPlayers_ - 1);
    cout << "initial queue: " << *queue_ << endl;
    while (battlesPlayed < numBattles)
    {
        size_t p1 = playerDist(rng_);
        size_t opponent = queue_->findOpponent(p1);
        cout << p1 << " " << opponent << endl;
        cout << "Queue status: " << *queue_ << endl;
        if (opponent != numPlayers_)// and doubleDist(rng_) > players_[p1].getPartyPct())
        {
            //play battle
            cout << "playing a battle" << endl;
            double randomVal = doubleDist(rng_);
            cout << "randomvalue" << randomVal << endl;
            u_int8_t league = players_[p1].getLeague();
            u_int8_t curToGold = 0;
            cout << "playing match" << endl;
            cout << goldStepRules_[league] << " " << std::flush
            << goldStepRules_[league + 1] << " "
            << stepRequirements_[league + 1];
            players_[p1].playMatch(players_[opponent], randomVal,
                                   goldStepRules_[league], goldStepRules_[league + 1],
                                   stepRequirements_[league + 1], dropLeague_);
            ++numBattles;
            cout << players_[p1] << " vs " << players_[opponent] << endl;
        }
    // count number of ultimate champs
    }
    for (auto& p : players_){
        if (p.isUC()){
            ++ultChamps_;
        }
    }
    return ultChamps_ / float(numPlayers_);    
}

size_t ucPctSimulation(float ultPct){
    
    return ultPct;
}