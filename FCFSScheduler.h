#ifndef FCFSSCHEDULER_H
#define FCFSSCHEDULER_H

#include "IScheduler.h"

class FCFSScheduler : public IScheduler {
public:
    void run(std::vector<Process> processes, int quantum = 0) override;
};

#endif
