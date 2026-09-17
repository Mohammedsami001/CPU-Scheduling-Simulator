# CPU Scheduling Simulator

An object-oriented CPU Scheduling Simulator implemented in C++, designed to model and compare the performance of various fundamental Operating System scheduling algorithms. This project provides detailed execution metrics including Waiting Time, Turnaround Time, and a text-based Gantt Chart for visual execution tracing.

## 📌 Features
- **Object-Oriented Design**: Utilizes an abstract base `IScheduler` interface, allowing easy extension for new algorithms.
- **C++ Standard Template Library (STL)**: Heavily relies on `std::vector`, `std::queue`, and custom `std::sort` lambdas for highly efficient process queue management.
- **Comprehensive Metrics**: Automatically calculates and averages Completion Time, Turnaround Time, Waiting Time, and Response Time.
- **Visual Gantt Charts**: Outputs a clear, timeline-based Gantt chart to the console for every scheduling execution.
- **File-Driven Input**: Reads process data asynchronously from a simple `.csv` file, making regression testing and algorithmic comparison reproducible.

## ⚙️ Algorithms Implemented

1. **First-Come, First-Served (FCFS)**
   - **Type**: Non-preemptive
   - **Logic**: Processes are executed strictly in the order of their arrival times. Tie-breaking is done via Process ID.
2. **Shortest Job First (SJF)**
   - **Type**: Non-preemptive
   - **Logic**: Selects the available process with the shortest burst time. Ideal for minimizing average waiting time but susceptible to starvation.
3. **Shortest Remaining Time First (SRTF)**
   - **Type**: Preemptive
   - **Logic**: A preemptive version of SJF. The scheduler dynamically evaluates the remaining execution time of all arrived processes at every time step.
4. **Priority Scheduling**
   - **Type**: Preemptive
   - **Logic**: Processes with a lower numerical priority value represent higher priority (e.g., Priority 1 > Priority 3). 
5. **Round Robin (RR)**
   - **Type**: Preemptive
   - **Logic**: Utilizes a circular ready queue. Each process is assigned a fixed time slice (quantum). If it doesn't complete within the quantum, it is preempted and pushed to the back of the queue.

## 🚀 Compilation & Execution

### Prerequisites
- A modern C++ compiler (e.g., GCC/G++) supporting C++11 or higher.

### Build
Compile the source code using the following command:
```bash
g++ -o scheduler main.cpp Process.cpp IScheduler.cpp FCFSScheduler.cpp SJFScheduler.cpp SRTFScheduler.cpp PriorityScheduler.cpp RoundRobinScheduler.cpp
```

### Run
The executable optionally takes the CSV filename and the Round Robin time quantum as command-line arguments.
```bash
# Default (Reads processes.csv, Quantum = 2)
./scheduler 

# Custom file and Quantum
./scheduler my_processes.csv 4
```

## 📄 Input Format (`processes.csv`)
The application reads process properties from a comma-separated file. The columns represent:
`Process ID, Arrival Time, Burst Time, Priority`

**Example `processes.csv`:**
```csv
1,0,8,3
2,1,4,1
3,2,9,4
4,3,5,2
```

## 📊 Sample Output

Upon execution, the terminal outputs the Gantt chart and an analytical metrics table for *each* algorithm. Below is a sample output for the **Shortest Remaining Time First (SRTF)** algorithm:

```text
--- Gantt Chart ---
|  P1  |  P2  |  P4  |  P1  |  P3  |
0      1      5      10      17      26      

--- Shortest Remaining Time First (SRTF) Metrics ---
ID      Arrival Burst   Prio    Completion      Turnaround      Waiting Response
P1      0       8       3       17              17              9       0
P2      1       4       1       5               4               0       0
P3      2       9       4       26              24              15      15
P4      3       5       2       10              7               2       2

Average Turnaround Time: 13
Average Waiting Time: 6.5
```

## 🏗️ Architectural Design
- **`Process` Class**: A lightweight data structure encapsulating state variables (`remainingTime`, `isStarted`) and final metrics (`waitingTime`, `turnaroundTime`).
- **`IScheduler` Base Class**: Contains the pure virtual `run()` method enforcing polymorphism, alongside protected helper methods `printMetrics()` and `printGanttChart()` to adhere to the DRY (Don't Repeat Yourself) principle.

---
*Developed by [Mohammedsami001](https://github.com/Mohammedsami001)*
