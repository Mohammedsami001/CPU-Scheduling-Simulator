#include "SJFScheduler.h"
#include <climits>

void SJFScheduler::run(std::vector<Process> processes, int quantum) {
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    
    std::vector<int> ganttProcesses;
    std::vector<int> ganttTimes;
    ganttTimes.push_back(currentTime);
    
    while (completed < n) {
        int idx = -1;
        int minBurst = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0 && processes[i].arrivalTime <= currentTime) {
                if (processes[i].burstTime < minBurst) {
                    minBurst = processes[i].burstTime;
                    idx = i;
                } else if (processes[i].burstTime == minBurst) {
                    if (idx == -1 || processes[i].id < processes[idx].id) {
                        idx = i;
                    }
                }
            }
        }
        
        if (idx != -1) {
            Process& p = processes[idx];
            p.responseTime = currentTime - p.arrivalTime;
            p.isStarted = true;
            
            ganttProcesses.push_back(p.id);
            currentTime += p.burstTime;
            p.remainingTime = 0;
            p.completionTime = currentTime;
            ganttTimes.push_back(currentTime);
            completed++;
        } else {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (processes[i].remainingTime > 0 && processes[i].arrivalTime > currentTime) {
                    if (processes[i].arrivalTime < nextArrival) {
                        nextArrival = processes[i].arrivalTime;
                    }
                }
            }
            if (nextArrival != INT_MAX) {
                ganttProcesses.push_back(-1);
                currentTime = nextArrival;
                ganttTimes.push_back(currentTime);
            }
        }
    }
    
    printGanttChart(ganttProcesses, ganttTimes);
    printMetrics(processes, "Shortest Job First (SJF)");
}
