#ifndef PROCESS_H
#define PROCESS_H

#include <string>

/*
 * Process States as defined in Operating System theory
 * (Silberschatz, Galvin, Gagne)
 */
enum State { NEW, READY, RUNNING, BLOCKED, TERMINATED };

class Process {
private:
    int pid;
    int priority;
    int arrivalTime;
    int burstTime;
    int remainingTime;

    int startTime = -1;
    int endTime   = -1;

    int blockTime = 0;
    State state   = NEW;

public:
    Process(int id, int at, int bt, int pr)
        : pid(id), arrivalTime(at), burstTime(bt),
          remainingTime(bt), priority(pr) {}

    /* ----- Execution ----- */
    void executeOneUnit() { remainingTime--; }

    bool isComplete() const { return remainingTime <= 0; }

    /* ----- Interrupt simulation ----- */
    bool shouldInterrupt() const {
        // deterministic interrupt model (acceptable for simulation)
        return remainingTime > 1 && remainingTime % 3 == 0;
    }

    /* ----- Getters / Setters ----- */
    int getPid() const { return pid; }
    int getPriority() const { return priority; }
    int getArrivalTime() const { return arrivalTime; }
    int getBurstTime() const { return burstTime; }
    int getRemainingTime() const { return remainingTime; }

    int getStartTime() const { return startTime; }
    int getEndTime() const { return endTime; }

    void setStartTime(int t) { startTime = t; }
    void setEndTime(int t)   { endTime = t; }

    State getState() const { return state; }
    void setState(State s) { state = s; }

    int getBlockTime() const { return blockTime; }
    void setBlockTime(int t) { blockTime = t; }
    void decrementBlockTime() { blockTime--; }
};

#endif
