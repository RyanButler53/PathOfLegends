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
    numPlayers_ = numPlayers;
    u_int8_t kt, cl;
    short oldPB;
    float partyPct;
    // Must treat as unsigned ints to properly read in numbers
    unsigned toGoldStep;
    unsigned stepReq;
    bool dropLeague;
    ifstream infile(settings);
    ifstream playersIn(playerFile);
    for (size_t stepRule = 0; stepRule < 9; ++stepRule) {
        //steps req, gold step, lvl cap
        infile >> stepReq;
        stepRequirements_[stepRule] = stepReq;
        infile >> toGoldStep;
        if (toGoldStep == 0){
            toGoldStep = 255;
        }
        goldStepRules_[stepRule] = toGoldStep;
    }
    size_t id = 0;
    for (size_t id = 0; id < numPlayers_; ++id)
    {
        playersIn >> kt;
        playersIn >> oldPB;
        playersIn >> partyPct;
        playersIn >> cl;
        Player newPlayer = Player{id, partyPct, oldPB, kt, cl, goldStepRules_[0]};
        players_.push_back(newPlayer);
    }
    // Need to get UC step requirement.
    infile >> stepReq;
    stepRequirements_[9] = stepReq;
    // cout << "UC requirement: " << int(stepRequirements_[9]) << endl;
    infile >> dropLeague;
    infile >> maxMultiplier_;
    goldStepRules_[9] = 255;
    queue_ = new HashQueue(players_);
    mt19937 rng_(seed);
    outStream = ofstream(outputFile + ".results");
}

Simulation::~Simulation()
{
    delete queue_;
}

float Simulation::nBattlesSimulation(size_t numBattles){
    size_t battlesPlayed = 0;
    uniform_real_distribution<double> doubleDist(0, 1);
    uniform_int_distribution<size_t> playerDist(0, numPlayers_ - 1);
    cout << "(id, wins, league, winsToGold, currentGold, step)" << endl;
    while (battlesPlayed < numBattles)
    {
        size_t p1 = playerDist(rng_);
        size_t opponent = queue_->findOpponent(p1);
        // cout << "Queue status: " << *queue_ << endl;
        cout << *queue_ << " (opponent:  " << opponent << ")" << endl;
        if (opponent != numPlayers_)// and doubleDist(rng_) > players_[p1].getPartyPct())
        {
            cout << players_[p1] << players_[opponent] << endl;
            cout << "league check: " << (players_[p1].getLeague() == players_[opponent].getLeague()) << endl;
            // play battle
            //  cout << "playing a battle" << endl;
            double randomVal = doubleDist(rng_);
            // cout << p1 << endl;
            // cout << players_.size() << endl;
            // cout << players_[p1] << endl;
            u_int8_t league = players_[p1].getLeague();
            u_int8_t curToGold = 0;
            cout << players_[p1] << " vs " << players_[opponent] << "-> ";
            players_[p1].playMatch(players_[opponent], randomVal,
                                   goldStepRules_[league], goldStepRules_[league + 1],
                                   stepRequirements_[league + 1], dropLeague_);
            ++battlesPlayed;
            cout << players_[p1] << " vs " << players_[opponent] << endl;

        }
    // count number of ultimate champs
    }
    for (auto& p : players_){
        if (p.isUC()){
            ++ultChamps_;
        }
        outStream << p << endl;
    }
    outStream << endl;
    return ultChamps_ / float(numPlayers_);
}

size_t ucPctSimulation(float ultPct){
    
    return ultPct;
}