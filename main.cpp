#include "Scheduler.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::string filename = "input.txt";
    
    // Allow specifying input file as command line argument
    if (argc > 1) {
        filename = argv[1];
    }
    
    Scheduler scheduler;
    
    std::cout << "Loading processes from " << filename << "..." << std::endl;
    if (!scheduler.loadProcesses(filename)) {
        std::cerr << "Failed to load processes. Exiting." << std::endl;
        return 1;
    }
    
    std::cout << "Processes loaded successfully." << std::endl;
    
    // Run the simulation
    scheduler.run();
    
    return 0;
}
