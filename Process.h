#ifndef PROCESS_H
#define PROCESS_H

#include <string>

enum ProcessState {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

class Process {
private:
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    ProcessState state;
    int startTime;
    int endTime;
    int waitingTime;

public:
    Process(int pid, int arrival, int burst, int prio);
    
    // Getters
    int getPid() const { return pid; }
    int getArrivalTime() const { return arrivalTime; }
    int getBurstTime() const { return burstTime; }
    int getRemainingTime() const { return remainingTime; }
    int getPriority() const { return priority; }
    ProcessState getState() const { return state; }
    int getStartTime() const { return startTime; }
    int getEndTime() const { return endTime; }
    int getWaitingTime() const { return waitingTime; }
    
    // Setters
    void setState(ProcessState s) { state = s; }
    void setStartTime(int t) { startTime = t; }
    void setEndTime(int t) { endTime = t; }
    void incrementWaitingTime() { waitingTime++; }
    
    // Execute for one time unit
    void execute();
    
    // Check if process is complete
    bool isComplete() const { return remainingTime == 0; }
    
    // Get state as string
    std::string getStateString() const;
};

#endif
