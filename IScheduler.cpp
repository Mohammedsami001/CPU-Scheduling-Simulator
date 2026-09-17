#include "IScheduler.h"
#include <iostream>
#include <iomanip>

void IScheduler::printMetrics(std::vector<Process>& processes, const std::string& algoName) {
    std::cout << "\n--- " << algoName << " Metrics ---\n";
    std::cout << "ID\tArrival\tBurst\tPrio\tCompletion\tTurnaround\tWaiting\tResponse\n";
    
    double avgTurnaround = 0;
    double avgWaiting = 0;
    
    for (auto& p : processes) {
        // Compute derived metrics if not already done
        if (p.turnaroundTime == 0) {
            p.turnaroundTime = p.completionTime - p.arrivalTime;
        }
        if (p.waitingTime == 0) {
            p.waitingTime = p.turnaroundTime - p.burstTime;
        }
        
        avgTurnaround += p.turnaroundTime;
        avgWaiting += p.waitingTime;
        
        std::cout << "P" << p.id << "\t"
                  << p.arrivalTime << "\t"
                  << p.burstTime << "\t"
                  << p.priority << "\t"
                  << p.completionTime << "\t\t"
                  << p.turnaroundTime << "\t\t"
                  << p.waitingTime << "\t"
                  << p.responseTime << "\n";
    }
    
    std::cout << "\nAverage Turnaround Time: " << avgTurnaround / processes.size() << "\n";
    std::cout << "Average Waiting Time: " << avgWaiting / processes.size() << "\n";
}

void IScheduler::printGanttChart(const std::vector<int>& ganttProcesses, const std::vector<int>& ganttTimes) {
    std::cout << "\n--- Gantt Chart ---\n";
    for (int p : ganttProcesses) {
        if (p == -1) {
            std::cout << "| IDLE ";
        } else {
            std::cout << "|  P" << p << "  ";
        }
    }
    std::cout << "|\n";
    
    for (int t : ganttTimes) {
        std::cout << t << "      ";
    }
    std::cout << "\n";
}
