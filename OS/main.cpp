#include <iostream>
#include <memory>
#include "Scheduler.h"

using namespace std;

/*
 * main.cpp
 * ----------
 * Acts as the system workload generator.
 * Creates processes and hands them to the dispatcher (Scheduler).
 */
int main() {
    Scheduler scheduler;

    /*
     * Process parameters:
     * (PID, Arrival Time, Burst Time, Priority)
     * Lower priority number = higher priority
     */
    scheduler.addProcess(make_shared<Process>(1, 0, 6, 2));
    scheduler.addProcess(make_shared<Process>(2, 1, 4, 1));
    scheduler.addProcess(make_shared<Process>(3, 2, 5, 3));
    scheduler.addProcess(make_shared<Process>(4, 3, 3, 2));

    // Start dispatcher simulation
    scheduler.run();

    return 0;
}
