# OS_fall.25-26
Dispatcher - CPU Scheduler Simulation

## Overview
This is a simulated CPU dispatcher/scheduler implemented in C++ that:
- Reads processes from an input file
- Maintains processes in priority-based queues
- Executes processes based on priority scheduling (lower priority number = higher priority)
- Handles process state transitions and termination
- Prints the system status at each time unit
- Stops when all processes have completed

## Features
- **Priority-based scheduling**: Processes with lower priority numbers execute first
- **FCFS tie-breaking**: When priorities are equal, earlier arrival time takes precedence
- **Real-time status output**: Shows running process, ready queue, and all process states at each time unit
- **Comprehensive summary**: Displays turnaround time and execution statistics after completion

## Files
- `Process.h` / `Process.cpp`: Process class definition and implementation
- `Scheduler.h` / `Scheduler.cpp`: Scheduler class for queue management and scheduling
- `main.cpp`: Main program entry point
- `Makefile`: Build configuration
- `input.txt`: Sample input file with process specifications

## Building
```bash
make
```

## Running
```bash
# Use default input file (input.txt)
./cpu_scheduler

# Use custom input file
./cpu_scheduler custom_input.txt
```

## Input File Format
The input file should contain one process per line with the following format:
```
PID ArrivalTime BurstTime Priority
```

Example:
```
# PID ArrivalTime BurstTime Priority
# Lower priority number = higher priority
1 0 5 2
2 1 3 1
3 2 4 3
4 3 2 1
5 5 6 2
```

- **PID**: Process ID (integer)
- **ArrivalTime**: Time when process arrives (integer, time units)
- **BurstTime**: CPU time required (integer, time units)
- **Priority**: Process priority (integer, lower = higher priority)

Lines starting with `#` are treated as comments and ignored.

## Output
The program displays:
1. **Real-time status**: At each time unit, shows:
   - Current running process with its priority and remaining time
   - Processes in the ready queue with their priorities
   - Complete table of all processes and their states

2. **Summary statistics**: After completion, shows:
   - Total execution time
   - Per-process statistics (arrival, burst, priority, start, end, turnaround time)

## Process States
- **NEW**: Process has not yet arrived
- **READY**: Process is in the ready queue waiting for CPU
- **RUNNING**: Process is currently executing on CPU
- **WAITING**: Process is waiting for I/O (not implemented in this version)
- **TERMINATED**: Process has completed execution

## Scheduling Algorithm
The scheduler uses **non-preemptive priority scheduling**:
1. Processes arrive at their specified arrival time and enter the ready queue
2. When the CPU is idle, the process with the highest priority (lowest priority number) is selected
3. If multiple processes have the same priority, FCFS (First Come First Serve) is used
4. Once a process starts executing, it runs to completion
5. When a process terminates, the next highest priority process is scheduled

## Example Run
With the sample input file, the simulation shows:
- Process 1 starts at time 0 and runs until time 4
- Process 2 (higher priority) starts at time 5
- Process 4 (same priority as P2, but later arrival) starts at time 8
- And so on, with detailed status printed at each time unit

## Cleaning
```bash
make clean
```

## Requirements
- C++11 or later
- g++ compiler
- make
Dispatcher

# **Process Dispatcher Simulator**

## **Overview**
This C++ project simulates a **CPU process dispatcher** with preemptive priority scheduling.
The program manages multiple processes, handles interrupts, executes processes one time unit at a time, and prints a detailed log of system activity.
It demonstrates key operating system concepts such as **process scheduling, context switching, and process states**.

---

## **Features**

### **1. Process Representation**
* Each process is represented using a **struct** containing:
  * **Process ID (PID)**
  * **Priority**
  * **Burst time** (how long the process needs to execute)
  * **Current state** (`READY`, `RUNNING`, `BLOCKED`, `TERMINATED`)

---

### **2. Queues**
* **Ready Queue:** Stores processes ready to execute, implemented as a **priority queue**.
* **Blocked Queue:** Stores processes waiting due to interrupts, implemented as **FIFO** (first-in, first-out).

---

### **3. Dispatcher / Scheduling Logic**
* Implements **preemptive priority scheduling**.
* Dispatcher selects the **highest-priority process** from the ready queue.
* Each process executes **one time unit at a time**.
* Handles **context switching** automatically when a higher-priority process arrives.

---

### **4. Interrupt Handling**
* Simulates **process interrupts** (randomly or deterministically).
* Interrupted processes are moved to the **blocked queue**.
* After a certain delay, processes are **unblocked** and returned to the ready queue.

---

### **5. Process Termination**
* Burst time decreases after each execution.
* Processes are **terminated** when burst time reaches zero.
* Simulation stops when both ready and blocked queues are empty.

---

### **6. Input / Output**
* **Input:**

  * Number of processes
  * PID, priority, and burst time for each process
* **Output (per time unit):**
  * Dispatcher decision (which process runs)
  * States of all processes
  * Remaining burst time
  * Interrupt events
  * Current queue states
* **Final summary:** Shows all completed processes and execution statistics.

---

### **7. Optional / Bonus Enhancements**
* **Gantt Chart:** Visual timeline of CPU execution per process.
  Example: `| P102 | P102 | P101 | P102 | P103 | P103 |`
* **Priority Aging / Boost:** Prevents starvation by gradually increasing priority of waiting processes.
* **Statistics:**
  * Total execution time
  * Total context switches
  * CPU utilization (optional)

---

### **8. Modular Functions**
The code is organized with clear, reusable functions:

* `dispatchProcess()` → Handles scheduling and execution
* `handleInterrupt()` → Manages process interrupts
* `unblockProcess()` → Moves blocked processes back to the ready queue
* `printQueueStatus()` → Prints current ready and blocked queues
* `printGanttChart()` → Optional function for timeline visualization

---

### **9. How It Works**
1. User inputs the number of processes and details (PID, priority, burst time).
2. Dispatcher continuously:
   * Picks the highest-priority ready process.
   * Executes it for one time unit.
   * Checks for interrupts and blocked processes.
   * Updates process states and queues.
3. Simulation ends when all processes terminate.
4. Detailed logs and final summary are displayed.

---

### **10. How to Run**
1. Compile the code using a C++ compiler:

   ```bash
   g++ -o dispatcher dispatcher.cpp
   ```
2. Run the program:

   ```bash
   ./dispatcher
   ```
3. Follow the prompts to input process information.
4. Observe detailed output per time unit and final summary.

---

### **11. Learning Outcomes**
By implementing this project, students learn:
* Preemptive priority scheduling
* Context switching
* Process state management
* Interrupt handling
* Queue data structures (priority queue and FIFO)
* CPU simulation and performance logging

---

### **12. Notes**
* The program can be extended with **Gantt charts** or **priority aging** for extra credit.
* Output is formatted clearly for **grading and analysis**.

