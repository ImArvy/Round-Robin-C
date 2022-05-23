#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdbool.h>
#include "RoundRobin.h"
#include "Queue.h"

#define NUM_PROCESSES 10
#define TIME_SLICE 10
int arrivals[] = { 0, 3, 6, 10, 11, 15, 19, 22, 25, 90 };
int bursts[] = { 8, 4, 5, 3, 10, 9, 10, 18, 11, 5 };
int totals[NUM_PROCESSES];

struct Process* createProcess(_pid, _burst, _quantum, _finished) {
    struct Process* process = (struct Process*)malloc(sizeof(struct Process));
    process->pid = _pid;
    process->burst = _burst;
    process->quantum = _quantum;
    process->finished = _finished;
}

void processStatus(struct Process* process) {
    printf("ID : %d , Burst : %d\n", process->pid, process->burst);
}

void roundRobin() {
    int completed = 0;
    int timeStep = 0;
    int i = 0;

    struct Process* running = createProcess(-1, -1, TIME_SLICE, false);
    struct Queue* myQueue = createQueue(10000);

    while (completed < NUM_PROCESSES) {
        //printf("T = %d\n", timestep);
        processStatus(running);
        if (running->burst >= 1) {
            running->burst--; // Decrement the burst
        }
        if (running->quantum >= 1) {
            running->quantum--; // Decrement the quantum
        }
        if (running->burst == 0 && !running->finished) {
            printf("Completed Process-%d at time step-%d\n", running->pid, timeStep);
            totals[running->pid] = timeStep - arrivals[running->pid];
            completed = running->pid;
            if (running->pid == (NUM_PROCESSES - 1)) {
                completed = NUM_PROCESSES;
            }
            running->finished = true;
        }
        while (i < NUM_PROCESSES && arrivals[i] <= timeStep) {
            printf("New Process-%d at time step-%d\n", i, timeStep);
            struct Process* newProcess = createProcess(i, bursts[i], TIME_SLICE, false);
            push(myQueue, newProcess);
            i++;
        }
        if (!queueEmpty(myQueue)) {
            if (running->burst > 0 && running->quantum == 0) { // If running process still has burst time but its time quantum is up
                running->quantum = TIME_SLICE; // Set quantum back to ten
                push(myQueue, running); // Push this one back to the queue so it can finish processing
                running = head(myQueue); // Set the next process in queue to running
                pop(myQueue); // Take running process out of the queue
            }
            if (running->burst <= 0 && running->quantum == 0) { // If running process has no more burst time and its time quantum is up
                running->quantum = TIME_SLICE; // Set quantum back to ten
                running = head(myQueue); // Set the next process in queue to running
                pop(myQueue); // Take running process out of the queue
            }
            if (running->burst <= 0 && running->quantum > 0) { // If running process has no more burst time but its time quantum has not expired
                running->quantum = TIME_SLICE; // Set quantum back to ten
                running = head(myQueue); // Set the next process in queue to running
                pop(myQueue); // Take running process out of the queue
            }
        }
        Sleep(100); // Sleep for one hundred milliseconds
        timeStep++; // Increment the time step
    }
}

int main(int argc, const char* argv[]) {
    roundRobin();
    double averageWaitingTime = 0;
    int waitingTime = 0;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        waitingTime = abs(totals[i] - bursts[i]); // Waiting Time = Turnaround Time - Burst 
        averageWaitingTime += waitingTime;
        printf("Waiting time for Process-%d : %d\n", i, waitingTime);
    }
    averageWaitingTime /= NUM_PROCESSES;
    printf("Average = %.2f\n", averageWaitingTime); // Display average waiting time to 2 decimal points
    return EXIT_SUCCESS;
}

