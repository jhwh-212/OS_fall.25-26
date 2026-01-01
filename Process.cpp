#include "Process.h"

Process::Process(int pid, int arrival, int burst, int prio)
    : pid(pid), arrivalTime(arrival), burstTime(burst), 
      remainingTime(burst), priority(prio), state(NEW),
      startTime(-1), endTime(-1), waitingTime(0) {}

void Process::execute() {
    if (remainingTime > 0) {
        remainingTime--;
        if (remainingTime == 0) {
            state = TERMINATED;
        }
    }
}

std::string Process::getStateString() const {
    switch (state) {
        case NEW: return "NEW";
        case READY: return "READY";
        case RUNNING: return "RUNNING";
        case WAITING: return "WAITING";
        case TERMINATED: return "TERMINATED";
        default: return "UNKNOWN";
    }
}
