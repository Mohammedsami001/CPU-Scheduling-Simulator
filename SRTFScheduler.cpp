#include "SRTFScheduler.h"
#include <climits>

void SRTFScheduler::run(std::vector<Process> processes, int quantum) {
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    
    std::vector<int> ganttProcesses;
    std::vector<int> ganttTimes;
    ganttTimes.push_back(currentTime);
    int currentP = -2;
    
    while (completed < n) {
        int idx = -1;
        int minRemaining = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0 && processes[i].arrivalTime <= currentTime) {
                if (processes[i].remainingTime < minRemaining) {
                    minRemaining = processes[i].remainingTime;
                    idx = i;
                } else if (processes[i].remainingTime == minRemaining) {
                    if (idx == -1 || processes[i].id < processes[idx].id) {
                        idx = i;
                    }
                }
            }
        }
        
        if (idx != -1) {
            Process& p = processes[idx];
            if (!p.isStarted) {
                p.responseTime = currentTime - p.arrivalTime;
                p.isStarted = true;
            }
            
            if (currentP != p.id) {
                ganttProcesses.push_back(p.id);
                if (currentP != -2) {
                    ganttTimes.push_back(currentTime);
                }
                currentP = p.id;
            }
            
            p.remainingTime--;
            currentTime++;
            
            if (p.remainingTime == 0) {
                p.completionTime = currentTime;
                completed++;
            }
        } else {
            if (currentP != -1) {
                ganttProcesses.push_back(-1);
                if (currentP != -2) {
                    ganttTimes.push_back(currentTime);
                }
                currentP = -1;
            }
            currentTime++;
        }
    }
    
    if (currentP != -2) {
        ganttTimes.push_back(currentTime);
    }
    
    printGanttChart(ganttProcesses, ganttTimes);
    printMetrics(processes, "Shortest Remaining Time First (SRTF)");
}
