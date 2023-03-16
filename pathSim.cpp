#include <iostream>
#include "simulation.hpp"
using namespace std;

#define NUM_BATTLES 10 //update this.
#define NUM_PLAYERS 5 // Kept small for testing. 

// Test command:  ./pathSim -p small.txt -o test -i settings.txt -d 70

void printCompilerCommands(); 

int main(int argc, const char **argv) {
    string playerFile = "small.txt";
    string settingsFile = "settings";
    string outputPrefix = "simulation";
    size_t seed = 70;


    // Process command line arguments. 
    vector<string> args(argv + 1, argc + argv);
    for (size_t i = 0; i < args.size(); ++i){
        string arg = args[i];
        if (arg == "-h"){
            printCompilerCommands();
            exit(0);
        } else if (arg == "-o"){
            ++i;
            outputPrefix = args[i];
        } else if (arg == "-i"){
            ++i;
            settingsFile = args[i];
        } else if (arg == "-p"){
            ++i;
            playerFile = args[i];
        }else if (arg == "-d"){
            ++i;
            seed = stoi(args[i]);
        }
    }
    Simulation pathSim{settingsFile, playerFile, seed, NUM_PLAYERS, outputPrefix + ".results"};
    float result = pathSim.nBattlesSimulation(NUM_BATTLES);
    cout << result << endl;
    return 0;
}

void printCompilerCommands(){
    cout << "Compiler Flags: \n" << endl;
    cout << "-h: Prints this help message" << endl;
    cout << "-o OUTPUT-PREFIX: The prefix of the results file. " << endl;
    cout << "   Ex: -o sim10k => sim10k.results" << endl;
    cout << "   Default: simulation.results" << endl;
    cout << "-i INPUT-PREFIX: The settings input file" << endl;
    cout << "   Ex: -i currentSettings.txt => readsfrom file \"currentSettings.txt\" " << endl;
    cout << "   Default: \"settings.txt\" (included in original repo)" << endl;
    cout << "-p FILENAME: The file where initial player data comes from" << endl;
    cout << "   Ex: -p 25kPlayers.txt => players come from file \"25kPlayers.txt\"" << endl;
    cout << "   Default: /ladderSample/25k.txt" << endl;
    cout << "-d SEED: Seed for RNG." << endl;
    cout << "    Default: 70" << endl;
}
