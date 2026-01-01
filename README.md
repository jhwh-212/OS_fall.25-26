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
