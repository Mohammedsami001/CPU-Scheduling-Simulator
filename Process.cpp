#include "Process.h"

Process::Process(int id, int arrivalTime, int burstTime, int priority) {
    this->id = id;
    this->arrivalTime = arrivalTime;
    this->burstTime = burstTime;
    this->priority = priority;
    
    this->remainingTime = burstTime;
    this->completionTime = 0;
    this->turnaroundTime = 0;
    this->waitingTime = 0;
    this->responseTime = -1;
    this->isStarted = false;
}
