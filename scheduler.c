#include "scheduler.h"
#include <limits.h>

// ---------------- Scheduling Algorithms ----------------

// FCFS Scheduling
Metrics fcfs_metrics(Process proc[], int n) {
    // Copy the array so we don't modify the caller's data
    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i] = proc[i];
    }

    // Sort by arrivalTime (simple O(n^2) sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[j].arrivalTime < p[i].arrivalTime) {
                Process tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }
        }
    }

    int currentTime = 0;
    float totalTurnaround = 0.0f;
    float totalWaiting    = 0.0f;
    float totalResponse   = 0.0f;

    for (int i = 0; i < n; i++) {
        // If CPU is idle, fast‐forward to the next arrival
        if (currentTime < p[i].arrivalTime) {
            currentTime = p[i].arrivalTime;
        }

        // Record when this process starts
        p[i].startTime = currentTime;
        // Completion = start + burst
        p[i].completionTime = currentTime + p[i].burstTime;

        int turnaround = p[i].completionTime - p[i].arrivalTime;
        int waiting    = turnaround - p[i].burstTime;
        int response   = p[i].startTime   - p[i].arrivalTime;

        totalTurnaround += (float)turnaround;
        totalWaiting    += (float)waiting;
        totalResponse   += (float)response;

        // Advance time to when this process finishes
        currentTime = p[i].completionTime;
    }

    Metrics m;
    m.avgTurnaround = totalTurnaround / (float)n;
    m.avgWaiting    = totalWaiting    / (float)n;
    m.avgResponse   = totalResponse   / (float)n;
    return m;
}


// SJF Scheduling (Non‐preemptive)
Metrics sjf_metrics(Process proc[], int n) {
    // Copy array so we don't modify the caller's data
    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i] = proc[i];
    }

    int completed[n];
    for (int i = 0; i < n; i++) {
        completed[i] = 0;
    }
    int completedCount = 0;
    int currentTime = 0;

    float totalTurnaround = 0.0f;
    float totalWaiting    = 0.0f;
    float totalResponse   = 0.0f;

    while (completedCount < n) {
        // Find the index of the shortest‐burst process that has arrived by currentTime
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (!completed[i] && p[i].arrivalTime <= currentTime) {
                if (idx == -1 || p[i].burstTime < p[idx].burstTime) {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            // No process ready yet: fast‐forward to the next earliest arrival
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!completed[i] && p[i].arrivalTime < nextArrival) {
                    nextArrival = p[i].arrivalTime;
                }
            }
            currentTime = nextArrival;
            continue;
        }

        // Schedule process p[idx]
        p[idx].startTime      = currentTime;
        p[idx].completionTime = currentTime + p[idx].burstTime;

        int turnaround = p[idx].completionTime - p[idx].arrivalTime;
        int waiting    = turnaround - p[idx].burstTime;
        int response   = p[idx].startTime   - p[idx].arrivalTime;

        totalTurnaround += (float)turnaround;
        totalWaiting    += (float)waiting;
        totalResponse   += (float)response;

        currentTime = p[idx].completionTime;
        completed[idx] = 1;
        completedCount++;
    }

    Metrics m;
    m.avgTurnaround = totalTurnaround / (float)n;
    m.avgWaiting    = totalWaiting    / (float)n;
    m.avgResponse   = totalResponse   / (float)n;
    return m;
}


// Round Robin Scheduling (Preemptive)
// Round Robin Scheduling (Preemptive, correct version)
Metrics rr_metrics(Process proc[], int n, int timeQuantum) {
    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i] = proc[i];
        p[i].remainingTime = p[i].burstTime;
        p[i].startTime = -1; // Not started
    }

    int completed = 0;
    int queue[n * 10]; // plenty of space
    int front = 0, rear = 0;
    int inQueue[n];
    for (int i = 0; i < n; i++) inQueue[i] = 0;

    int currentTime = 0;

    // Enqueue processes that have arrived at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].arrivalTime == 0) {
            queue[rear++] = i;
            inQueue[i] = 1;
        }
    }

    float totalTurnaround = 0.0f, totalWaiting = 0.0f, totalResponse = 0.0f;

    while (completed < n) {
        if (front == rear) {
            // Queue is empty, fast-forward to earliest arrival
            int minArrival = INT_MAX, idx = -1;
            for (int i = 0; i < n; i++) {
                if (p[i].remainingTime > 0 && p[i].arrivalTime < minArrival && !inQueue[i]) {
                    minArrival = p[i].arrivalTime;
                    idx = i;
                }
            }
            if (idx != -1) {
                currentTime = p[idx].arrivalTime;
                queue[rear++] = idx;
                inQueue[idx] = 1;
            }
            continue;
        }
        int idx = queue[front++];
        inQueue[idx] = 0;
        // If not started before, record startTime
        if (p[idx].startTime == -1) {
            p[idx].startTime = (currentTime < p[idx].arrivalTime) ? p[idx].arrivalTime : currentTime;
            if (currentTime < p[idx].arrivalTime)
                currentTime = p[idx].arrivalTime;
        }
        int execTime = (p[idx].remainingTime < timeQuantum) ? p[idx].remainingTime : timeQuantum;
        int oldTime = currentTime;
        currentTime += execTime;
        p[idx].remainingTime -= execTime;

        // Enqueue processes that have arrived in the meantime
        for (int j = 0; j < n; j++) {
            if (j != idx && p[j].remainingTime > 0 && !inQueue[j] &&
                p[j].arrivalTime > oldTime && p[j].arrivalTime <= currentTime) {
                queue[rear++] = j;
                inQueue[j] = 1;
            }
        }

        if (p[idx].remainingTime > 0) {
            queue[rear++] = idx;
            inQueue[idx] = 1;
        } else {
            p[idx].completionTime = currentTime;
            completed++;
        }
    }

    for (int i = 0; i < n; i++) {
        int turnaround = p[i].completionTime - p[i].arrivalTime;
        int waiting = turnaround - p[i].burstTime;
        int response = p[i].startTime - p[i].arrivalTime;
        totalTurnaround += turnaround;
        totalWaiting += waiting;
        totalResponse += response;
    }

    Metrics m;
    m.avgTurnaround = totalTurnaround / n;
    m.avgWaiting = totalWaiting / n;
    m.avgResponse = totalResponse / n;
    return m;
}

