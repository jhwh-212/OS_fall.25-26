# OS_fall.25-26
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

