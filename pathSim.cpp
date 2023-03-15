#include <iostream>
#include "simulation.hpp"
using namespace std;

int main() //int argc, char **argv
{
    
    // must specify settings file and path to players file.
    string playerFile = "small.txt";
    string settingsFile = "settings.txt";
    size_t seed = 70;
    size_t numBattles = 5;
    Simulation pathSim{settingsFile, playerFile, seed, 15};
    float result = pathSim.runSimulation(numBattles);
    cout << result << endl;
    return 0;
}