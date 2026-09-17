#ifndef ISCHEDULER_H
#define ISCHEDULER_H

#include <vector>
#include <string>
#include "Process.h"

class IScheduler {
public:
    virtual ~IScheduler() {}
    virtual void run(std::vector<Process> processes, int quantum = 0) = 0;
    
protected:
    void printMetrics(std::vector<Process>& processes, const std::string& algoName);
    void printGanttChart(const std::vector<int>& ganttProcesses, const std::vector<int>& ganttTimes);
};

#endif
