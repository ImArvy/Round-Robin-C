#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

struct Process {
    int pid;
    int burst;
    int quantum;
    bool finished;
};

struct Process* createProcess(_pid, _burst, _quantum, _finished);

void processStatus(struct Process* process);

void roundRobin();

#endif // ROUND_ROBIN_H