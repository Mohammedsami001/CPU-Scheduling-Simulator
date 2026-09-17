#ifndef SRTFSCHEDULER_H
#define SRTFSCHEDULER_H

#include "IScheduler.h"

class SRTFScheduler : public IScheduler {
public:
    void run(std::vector<Process> processes, int quantum = 0) override;
};

#endif
