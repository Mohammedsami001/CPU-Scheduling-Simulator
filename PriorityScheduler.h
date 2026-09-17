#ifndef PRIORITYSCHEDULER_H
#define PRIORITYSCHEDULER_H

#include "IScheduler.h"

class PriorityScheduler : public IScheduler {
public:
    void run(std::vector<Process> processes, int quantum = 0) override;
};

#endif
