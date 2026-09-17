#include "FCFSScheduler.h"
#include <algorithm>

void FCFSScheduler::run(std::vector<Process> processes, int quantum) {
    std::vector<Process*> ptrs;
    for (auto& p : processes) {
        ptrs.push_back(&p);
    }
    
    std::sort(ptrs.begin(), ptrs.end(), [](Process* a, Process* b) {
        if (a->arrivalTime == b->arrivalTime) {
            return a->id < b->id;
        }
        return a->arrivalTime < b->arrivalTime;
    });
    
    std::vector<int> ganttProcesses;
    std::vector<int> ganttTimes;
    int currentTime = 0;
    
    ganttTimes.push_back(currentTime);
    
    for (auto* p : ptrs) {
        if (currentTime < p->arrivalTime) {
            ganttProcesses.push_back(-1); // IDLE
            currentTime = p->arrivalTime;
            ganttTimes.push_back(currentTime);
        }
        
        p->isStarted = true;
        p->responseTime = currentTime - p->arrivalTime;
        
        ganttProcesses.push_back(p->id);
        currentTime += p->burstTime;
        p->remainingTime = 0;
        p->completionTime = currentTime;
        ganttTimes.push_back(currentTime);
    }
    
    printGanttChart(ganttProcesses, ganttTimes);
    printMetrics(processes, "First-Come, First-Served (FCFS)");
}
