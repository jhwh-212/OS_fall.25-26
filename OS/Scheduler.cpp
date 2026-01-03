#include "Scheduler.h"
#include <iostream>
#include <iomanip>

using namespace std;

/* Add process to system */
void Scheduler::addProcess(shared_ptr<Process> p) {
    allProcesses.push_back(p);
}

/* Admit newly arrived processes */
void Scheduler::checkArrivals() {
    for (auto &p : allProcesses) {
        if (p->getState() == NEW && p->getArrivalTime() <= currentTime) {
            p->setState(READY);
            readyQueue.push(p);
        }
    }
}

/* Dispatcher decision (preemptive priority) */
void Scheduler::schedule() {
    if (!runningProcess && !readyQueue.empty()) {
        runningProcess = readyQueue.top();
        readyQueue.pop();
        runningProcess->setState(RUNNING);

        if (runningProcess->getStartTime() == -1)
            runningProcess->setStartTime(currentTime);
    }
}

/* Execute one CPU time unit */
void Scheduler::execute() {
    if (runningProcess) {
        runningProcess->executeOneUnit();
        ganttChart.push_back(runningProcess->getPid());
    } else {
        ganttChart.push_back(-1); // CPU idle
    }
}

/* Handle interrupts (RUNNING → BLOCKED) */
void Scheduler::handleInterrupts() {
    if (runningProcess && runningProcess->shouldInterrupt()) {
        runningProcess->setState(BLOCKED);
        runningProcess->setBlockTime(2); // fixed I/O duration
        blockedQueue.push(runningProcess);
        runningProcess = nullptr;
    }
}

/* Handle blocked processes */
void Scheduler::handleBlocked() {
    int n = blockedQueue.size();
    while (n--) {
        auto p = blockedQueue.front();
        blockedQueue.pop();
        p->decrementBlockTime();

        if (p->getBlockTime() == 0) {
            p->setState(READY);
            readyQueue.push(p);
        } else {
            blockedQueue.push(p);
        }
    }
}

/* Handle process completion */
void Scheduler::handleTermination() {
    if (runningProcess && runningProcess->isComplete()) {
        runningProcess->setState(TERMINATED);
        runningProcess->setEndTime(currentTime);
        terminatedProcesses.push_back(runningProcess);
        runningProcess = nullptr;
    }
}

/* Check completion */
bool Scheduler::allProcessesComplete() const {
    for (auto &p : allProcesses)
        if (p->getState() != TERMINATED)
            return false;
    return true;
}

/* Print runtime status */
void Scheduler::printStatus() const {
    cout << "\n=== Time " << currentTime << " ===\n";
    cout << "Running: ";
    if (runningProcess) cout << "P" << runningProcess->getPid();
    else cout << "IDLE";
    cout << "\n";
}

/* Advance time */
void Scheduler::tick() {
    currentTime++;
}

/* Print Gantt chart */
void Scheduler::printGanttChart() const {
    cout << "\nGantt Chart:\n|";
    for (int pid : ganttChart)
        if (pid == -1) cout << " IDLE |";
        else cout << " P" << pid << " |";
    cout << "\n";
}

/* Main simulation loop */
void Scheduler::run() {
    while (!allProcessesComplete()) {
        checkArrivals();
        handleBlocked();
        schedule();
        execute();
        handleInterrupts();
        handleTermination();
        printStatus();
        tick();
    }
    printGanttChart();
}

