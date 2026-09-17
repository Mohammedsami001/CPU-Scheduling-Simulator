#ifndef SJFSCHEDULER_H
#define SJFSCHEDULER_H

#include "IScheduler.h"

class SJFScheduler : public IScheduler {
public:
    void run(std::vector<Process> processes, int quantum = 0) override;
};

#endif
