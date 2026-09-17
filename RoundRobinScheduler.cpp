#include "RoundRobinScheduler.h"
#include <queue>
#include <algorithm>
#include <climits>

void RoundRobinScheduler::run(std::vector<Process> processes, int quantum) {
    if (quantum <= 0) quantum = 1;
    
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    
    std::vector<int> ganttProcesses;
    std::vector<int> ganttTimes;
    ganttTimes.push_back(currentTime);
    
    std::queue<int> readyQueue;
    std::vector<bool> inQueue(n, false);
    
    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime <= currentTime) {
            readyQueue.push(i);
            inQueue[i] = true;
        }
    }
    
    while (completed < n) {
        if (readyQueue.empty()) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (processes[i].remainingTime > 0 && !inQueue[i]) {
                    if (processes[i].arrivalTime < nextArrival) {
                        nextArrival = processes[i].arrivalTime;
                    }
                }
            }
            if (nextArrival != INT_MAX) {
                ganttProcesses.push_back(-1);
                currentTime = nextArrival;
                ganttTimes.push_back(currentTime);
                for (int i = 0; i < n; i++) {
                    if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && !inQueue[i]) {
                        readyQueue.push(i);
                        inQueue[i] = true;
                    }
                }
            }
            continue;
        }
        
        int idx = readyQueue.front();
        readyQueue.pop();
        Process& p = processes[idx];
        
        if (!p.isStarted) {
            p.responseTime = currentTime - p.arrivalTime;
            p.isStarted = true;
        }
        
        int runTime = std::min(quantum, p.remainingTime);
        ganttProcesses.push_back(p.id);
        
        currentTime += runTime;
        p.remainingTime -= runTime;
        ganttTimes.push_back(currentTime);
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && !inQueue[i] && i != idx) {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }
        
        if (p.remainingTime == 0) {
            p.completionTime = currentTime;
            completed++;
        } else {
            readyQueue.push(idx);
        }
    }
    
    printGanttChart(ganttProcesses, ganttTimes);
    printMetrics(processes, "Round Robin (RR) - Quantum: " + std::to_string(quantum));
}
