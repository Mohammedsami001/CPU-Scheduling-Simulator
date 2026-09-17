#ifndef ROUNDROBINSCHEDULER_H
#define ROUNDROBINSCHEDULER_H

#include "IScheduler.h"

class RoundRobinScheduler : public IScheduler {
public:
    void run(std::vector<Process> processes, int quantum = 0) override;
};

#endif
