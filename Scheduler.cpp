#include "Scheduler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

Scheduler::Scheduler() : runningProcess(nullptr), currentTime(0) {}

void Scheduler::addProcess(std::shared_ptr<Process> process) {
    allProcesses.push_back(process);
}

bool Scheduler::loadProcesses(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    
    std::string line;
    // Skip header line if present
    std::getline(file, line);
    if (line.find("PID") != std::string::npos || line.find("pid") != std::string::npos) {
        // Header line, continue to next line
    } else {
        // No header, rewind
        file.clear();
        file.seekg(0);
    }
    
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        std::istringstream iss(line);
        int pid, arrival, burst, priority;
        
        if (iss >> pid >> arrival >> burst >> priority) {
            auto process = std::make_shared<Process>(pid, arrival, burst, priority);
            addProcess(process);
        }
    }
    
    file.close();
    
    // Sort processes by arrival time for easier processing
    std::sort(allProcesses.begin(), allProcesses.end(),
              [](const std::shared_ptr<Process>& a, const std::shared_ptr<Process>& b) {
                  return a->getArrivalTime() < b->getArrivalTime();
              });
    
    return true;
}

void Scheduler::checkArrivals() {
    for (auto& process : allProcesses) {
        if (process->getState() == NEW && process->getArrivalTime() == currentTime) {
            process->setState(READY);
            readyQueue.push(process);
        }
    }
}

void Scheduler::schedule() {
    // If no process is running and ready queue has processes, select one
    if (runningProcess == nullptr && !readyQueue.empty()) {
        runningProcess = readyQueue.top();
        readyQueue.pop();
        runningProcess->setState(RUNNING);
        
        // Set start time if this is the first time running
        if (runningProcess->getStartTime() == -1) {
            runningProcess->setStartTime(currentTime);
        }
    }
}

void Scheduler::execute() {
    if (runningProcess != nullptr) {
        runningProcess->execute();
    }
    
    // Increment waiting time for all processes in ready queue
    // Note: priority_queue doesn't allow iteration, so we track this differently
    // For simplicity, we'll update waiting times when processes are scheduled
}

void Scheduler::handleTermination() {
    if (runningProcess != nullptr && runningProcess->isComplete()) {
        runningProcess->setEndTime(currentTime);
        terminatedProcesses.push_back(runningProcess);
        runningProcess = nullptr;
    }
}

void Scheduler::printStatus() {
    std::cout << "\n=== Time Unit: " << currentTime << " ===" << std::endl;
    
    std::cout << "Running Process: ";
    if (runningProcess != nullptr) {
        std::cout << "P" << runningProcess->getPid() 
                  << " (Priority: " << runningProcess->getPriority()
                  << ", Remaining: " << runningProcess->getRemainingTime() << ")";
    } else {
        std::cout << "IDLE";
    }
    std::cout << std::endl;
    
    // Show ready queue (create a copy to display)
    std::cout << "Ready Queue: ";
    if (readyQueue.empty()) {
        std::cout << "EMPTY";
    } else {
        // Priority queue doesn't support iteration, so we'll show count
        std::priority_queue<std::shared_ptr<Process>, 
                           std::vector<std::shared_ptr<Process>>, 
                           ProcessComparator> tempQueue = readyQueue;
        bool first = true;
        while (!tempQueue.empty()) {
            auto p = tempQueue.top();
            tempQueue.pop();
            if (!first) std::cout << ", ";
            std::cout << "P" << p->getPid() << "(Pri:" << p->getPriority() << ")";
            first = false;
        }
    }
    std::cout << std::endl;
    
    // Show all process states
    std::cout << "All Processes:" << std::endl;
    std::cout << std::setw(6) << "PID" 
              << std::setw(12) << "State" 
              << std::setw(10) << "Priority"
              << std::setw(12) << "Remaining" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    for (const auto& process : allProcesses) {
        std::cout << std::setw(6) << process->getPid()
                  << std::setw(12) << process->getStateString()
                  << std::setw(10) << process->getPriority()
                  << std::setw(12) << process->getRemainingTime()
                  << std::endl;
    }
}

bool Scheduler::allProcessesComplete() const {
    for (const auto& process : allProcesses) {
        if (process->getState() != TERMINATED) {
            return false;
        }
    }
    return true;
}

void Scheduler::run() {
    std::cout << "===== CPU Scheduler Simulation Started =====" << std::endl;
    std::cout << "Total Processes: " << allProcesses.size() << std::endl;
    
    while (!allProcessesComplete()) {
        // Check for new process arrivals
        checkArrivals();
        
        // Schedule next process if CPU is idle
        schedule();
        
        // Execute current process
        execute();
        
        // Print status
        printStatus();
        
        // Handle process termination
        handleTermination();
        
        // Move to next time unit
        tick();
    }
    
    std::cout << "\n===== Simulation Complete =====" << std::endl;
    std::cout << "Total Time Units: " << currentTime << std::endl;
    
    // Print summary
    std::cout << "\nProcess Execution Summary:" << std::endl;
    std::cout << std::setw(6) << "PID" 
              << std::setw(12) << "Arrival"
              << std::setw(10) << "Burst"
              << std::setw(10) << "Priority"
              << std::setw(10) << "Start"
              << std::setw(10) << "End"
              << std::setw(15) << "Turnaround" << std::endl;
    std::cout << std::string(73, '-') << std::endl;
    
    for (const auto& process : terminatedProcesses) {
        int turnaround = process->getEndTime() - process->getArrivalTime();
        std::cout << std::setw(6) << process->getPid()
                  << std::setw(12) << process->getArrivalTime()
                  << std::setw(10) << process->getBurstTime()
                  << std::setw(10) << process->getPriority()
                  << std::setw(10) << process->getStartTime()
                  << std::setw(10) << process->getEndTime()
                  << std::setw(15) << turnaround
                  << std::endl;
    }
}
