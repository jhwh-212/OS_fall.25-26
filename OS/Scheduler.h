#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <queue>
#include <vector>
#include <memory>
#include "Process.h"
#include "ProcessComparator.h"

class Scheduler {
private:
    int currentTime = 0;

    /* Ready queue ordered by priority */
    std::priority_queue<
        std::shared_ptr<Process>,
        std::vector<std::shared_ptr<Process>>,
        ProcessComparator
    > readyQueue;

    /* FIFO blocked queue (interrupt handling) */
    std::queue<std::shared_ptr<Process>> blockedQueue;

    std::shared_ptr<Process> runningProcess;

    std::vector<std::shared_ptr<Process>> allProcesses;
    std::vector<std::shared_ptr<Process>> terminatedProcesses;

    /* Gantt chart: PID per time unit */
    std::vector<int> ganttChart;

public:
    void addProcess(std::shared_ptr<Process> p);

    void checkArrivals();
    void schedule();
    void execute();
    void handleInterrupts();
    void handleBlocked();
    void handleTermination();

    void printStatus() const;
    void printGanttChart() const;

    bool allProcessesComplete() const;
    void tick();
    void run();
};

#endif
