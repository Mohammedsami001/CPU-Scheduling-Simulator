#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Process.h"
#include "FCFSScheduler.h"
#include "SJFScheduler.h"
#include "SRTFScheduler.h"
#include "PriorityScheduler.h"
#include "RoundRobinScheduler.h"

int main(int argc, char* argv[]) {
    std::string filename = "processes.csv";
    int quantum = 2;
    
    if (argc >= 2) {
        filename = argv[1];
    }
    if (argc >= 3) {
        quantum = std::stoi(argv[2]);
    }
    
    std::vector<Process> processes;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return 1;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string token;
        
        int id, arr, brs, pri = 0;
        
        if (std::getline(ss, token, ',')) id = std::stoi(token);
        if (std::getline(ss, token, ',')) arr = std::stoi(token);
        if (std::getline(ss, token, ',')) brs = std::stoi(token);
        if (std::getline(ss, token, ',')) pri = std::stoi(token);
        
        processes.push_back(Process(id, arr, brs, pri));
    }
    
    FCFSScheduler fcfs;
    SJFScheduler sjf;
    SRTFScheduler srtf;
    PriorityScheduler prio;
    RoundRobinScheduler rr;
    
    fcfs.run(processes);
    sjf.run(processes);
    srtf.run(processes);
    prio.run(processes);
    rr.run(processes, quantum);
    
    return 0;
}
