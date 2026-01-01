#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.h"
#include <vector>
#include <queue>
#include <memory>

// Comparator for priority queue (higher priority value = higher priority)
struct ProcessComparator {
    bool operator()(const std::shared_ptr<Process>& p1, const std::shared_ptr<Process>& p2) const {
        // Lower priority value means higher priority in this implementation
        // If priorities are equal, use FCFS (earlier arrival time has priority)
        if (p1->getPriority() == p2->getPriority()) {
            return p1->getArrivalTime() > p2->getArrivalTime();
        }
        return p1->getPriority() > p2->getPriority();
    }
};

class Scheduler {
private:
    std::vector<std::shared_ptr<Process>> allProcesses;
    std::priority_queue<std::shared_ptr<Process>, 
                       std::vector<std::shared_ptr<Process>>, 
                       ProcessComparator> readyQueue;
    std::shared_ptr<Process> runningProcess;
    std::vector<std::shared_ptr<Process>> terminatedProcesses;
    int currentTime;
    
public:
    Scheduler();
    
    // Add a process to the system
    void addProcess(std::shared_ptr<Process> process);
    
    // Load processes from input file
    bool loadProcesses(const std::string& filename);
    
    // Check for new arrivals and add to ready queue
    void checkArrivals();
    
    // Select next process to run based on priority
    void schedule();
    
    // Execute current running process for one time unit
    void execute();
    
    // Handle process termination
    void handleTermination();
    
    // Print system status
    void printStatus();
    
    // Check if all processes are complete
    bool allProcessesComplete() const;
    
    // Run the simulation
    void run();
    
    // Get current time
    int getCurrentTime() const { return currentTime; }
    
    // Increment time
    void tick() { currentTime++; }
};

#endif
