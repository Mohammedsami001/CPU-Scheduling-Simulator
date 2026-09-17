#ifndef PROCESS_H
#define PROCESS_H

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
    bool isStarted;
    
    Process(int id, int arrivalTime, int burstTime, int priority = 0);
};

#endif
