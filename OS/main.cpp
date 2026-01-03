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
    int numProcesses;
    cout << "How many processes do you have? ";
    if (!(cin >> numProcesses)) {
        cout << "Invalid input. Exiting." << endl;
        return 1;
    }
    for (int i = 0; i < numProcesses; ++i) {
        int pid, arrival, burst, priority;
        cout << "\nEnter details for process " << i + 1 << ":" << endl;
        cout << "Process ID: ";
        cin >> pid;
        cout << "Arrival Time: ";
        cin >> arrival;
        cout << "Burst Time: ";
        cin >> burst;
        cout << "Priority (lower number = higher priority): ";
        cin >> priority;
        scheduler.addProcess(make_shared<Process>(pid, arrival, burst, priority));
    }
    cout << "\nStarting dispatcher simulation...\n" << endl;
    
    // Start dispatcher simulation
    scheduler.run();
    return 0;
}