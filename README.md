# CPU Scheduling Algorithms

This project implements three fundamental CPU scheduling algorithms in C as part of an Operating Systems course project.

## Algorithms Implemented

1. **FCFS (First Come First Serve)**
2. **SJF (Shortest Job First - Non-Preemptive)**
3. **Round Robin (RR)**

Each algorithm computes the following performance metrics:
- Average Turnaround Time
- Average Waiting Time
- Average Response Time

## File Structure

```
.
├── scheduler.h         # Declarations for structs and scheduling functions
├── scheduler.c         # Implementation of the scheduling algorithms
├── scheduler_test.c    # Test cases and assertions for validating correctness
├── Makefile            # Build automation script
└── README.md           # Project documentation (this file)
```

## How to Compile

To build the project, simply use:

```bash
make
```

This compiles the source files and produces an executable named `scheduler_test`.

## How to Run

To run the compiled test program:

```bash
make run
```

This will execute the scheduler tests and print the calculated vs. expected metrics for:
- FCFS
- SJF
- Round Robin (with specified quantum)

If all assertions pass, you will see:

```
>>> Test Case X PASSED.
...
ALL TESTS PASSED.
```
How to compile and run without MakeFile:

>> gcc -std=c99 -O2 -Wall scheduler.c scheduler_test.c -o scheduler_test.exe -lm
>> ./scheduler_test.exe

## How to Clean

To remove the compiled binary:

```bash
make clean
```
## Inputs
The scheduling functions in scheduler.c do not read from stdin or external files. Instead:

In scheduler_test.c, each test defines an array of Process structs. For each process P_i, you specify:

pid (an integer identifier, e.g., 1, 2, 3).

arrivalTime (the time at which the process becomes ready to run, in arbitrary time units).

burstTime (the total CPU time required by the process, in the same time units).

The fields remainingTime, startTime, and completionTime are initialized to 0 (or –1 for startTime in Round Robin).

In the Round Robin tests, scheduler_test.c also passes a timeQuantum value (e.g., 4 or 2) to rr_metrics(...).

No interactive prompts are used. All arrival/burst times and the quantum are hard‐coded within scheduler_test.c.

## Outputs:
==== Test Case 1 ====
FCFS: Calculated: Turnaround: 15.00, Waiting: 7.33, Response: 7.33
      Expected:   Turnaround: 15.00, Waiting: 7.33, Response: 7.33
SJF:  Calculated: Turnaround: 15.00, Waiting: 7.33, Response: 7.33
      Expected:   Turnaround: 15.00, Waiting: 7.33, Response: 7.33
RR (Quantum = 4): Calculated: Turnaround: 19.33, Waiting: 11.67, Response: 3.00
         Expected:   Turnaround: 19.33, Waiting: 11.67, Response: 3.00
>>> Test Case 1 PASSED.

==== Test Case 2 ====
FCFS: Calculated: Turnaround: 5.67, Waiting: 1.67, Response: 1.67
      Expected:   Turnaround: 5.67, Waiting: 1.67, Response: 1.67
SJF:  Calculated: Turnaround: 5.67, Waiting: 1.67, Response: 1.67
      Expected:   Turnaround: 5.67, Waiting: 1.67, Response: 1.67
RR (Quantum = 2): Calculated: Turnaround: 5.67, Waiting: 1.67, Response: 1.00
         Expected:   Turnaround: 5.67, Waiting: 1.67, Response: 1.00
>>> Test Case 2 PASSED.

==== Test Case 3 ====
FCFS: Calculated: Turnaround: 5.75, Waiting: 3.25, Response: 3.25
      Expected:   Turnaround: 5.75, Waiting: 3.25, Response: 3.25
SJF:  Calculated: Turnaround: 5.00, Waiting: 2.50, Response: 2.50
      Expected:   Turnaround: 5.00, Waiting: 2.50, Response: 2.50
RR (Quantum = 2): Calculated: Turnaround: 6.25, Waiting: 3.75, Response: 1.75
         Expected:   Turnaround: 6.25, Waiting: 3.75, Response: 1.75
>>> Test Case 3 PASSED.

==== Test Case 4 ====
FCFS: Calculated: Turnaround: 8.60, Waiting: 4.60, Response: 4.60
      Expected:   Turnaround: 8.60, Waiting: 4.60, Response: 4.60
SJF:  Calculated: Turnaround: 7.60, Waiting: 3.60, Response: 3.60
      Expected:   Turnaround: 7.60, Waiting: 3.60, Response: 3.60
RR (Quantum = 3): Calculated: Turnaround: 10.60, Waiting: 6.60, Response: 2.60
         Expected:   Turnaround: 10.60, Waiting: 6.60, Response: 2.60
>>> Test Case 4 PASSED.

==== Test Case 5 (Single Process) ====
FCFS: Calculated: Turnaround: 5.00, Waiting: 0.00, Response: 0.00
      Expected:   Turnaround: 5.00, Waiting: 0.00, Response: 0.00
SJF:  Calculated: Turnaround: 5.00, Waiting: 0.00, Response: 0.00
      Expected:   Turnaround: 5.00, Waiting: 0.00, Response: 0.00
RR (Quantum = 2): Calculated: Turnaround: 5.00, Waiting: 0.00, Response: 0.00
         Expected:   Turnaround: 5.00, Waiting: 0.00, Response: 0.00
>>> Test Case 5 (Single Process) PASSED.

==== Test Case 6 (Two Processes, Same Arrival) ====
FCFS: Calculated: Turnaround: 7.00, Waiting: 2.00, Response: 2.00
      Expected:   Turnaround: 7.00, Waiting: 2.00, Response: 2.00
SJF:  Calculated: Turnaround: 7.00, Waiting: 2.00, Response: 2.00
      Expected:   Turnaround: 7.00, Waiting: 2.00, Response: 2.00
RR (Quantum = 3): Calculated: Turnaround: 8.50, Waiting: 3.50, Response: 1.50
         Expected:   Turnaround: 8.50, Waiting: 3.50, Response: 1.50
>>> Test Case 6 (Two Processes, Same Arrival) PASSED.

==== Test Case 7 (Varying Arrivals) ====
FCFS: Calculated: Turnaround: 15.25, Waiting: 8.75, Response: 8.75
      Expected:   Turnaround: 15.25, Waiting: 8.75, Response: 8.75
SJF:  Calculated: Turnaround: 14.25, Waiting: 7.75, Response: 7.75
      Expected:   Turnaround: 14.25, Waiting: 7.75, Response: 7.75
RR (Quantum = 3): Calculated: Turnaround: 20.00, Waiting: 13.50, Response: 3.00
         Expected:   Turnaround: 20.00, Waiting: 13.50, Response: 3.00
>>> Test Case 7 (Varying Arrivals) PASSED.

==== Test Case 8 (Six Processes) ====
FCFS: Calculated: Turnaround: 17.00, Waiting: 11.17, Response: 11.17
      Expected:   Turnaround: 17.00, Waiting: 11.17, Response: 11.17
SJF:  Calculated: Turnaround: 15.17, Waiting: 9.33, Response: 9.33
      Expected:   Turnaround: 15.17, Waiting: 9.33, Response: 9.33
RR (Quantum = 4): Calculated: Turnaround: 20.67, Waiting: 14.83, Response: 6.33
         Expected:   Turnaround: 20.67, Waiting: 14.83, Response: 6.33
>>> Test Case 8 (Six Processes) PASSED.

ALL TESTS PASSED.

## Implementation Overview of Scheduling Algorithms
This project supports three classic CPU‐scheduling algorithms. Each works on a list of processes (each with a PID, arrivalTime, and burstTime) and computes:

Turnaround Time (completionTime − arrivalTime)

Waiting Time (turnaroundTime − burstTime)

Response Time (startTime − arrivalTime)

After running the scheduler, we average each metric across all processes.

1. First‐Come, First‐Served (FCFS)
Sort the process list in ascending order of arrivalTime. If two processes have the same arrival, keep their original relative order.

Initialize a currentTime = 0.

For each process P in sorted order:

If currentTime < P.arrivalTime, advance currentTime = P.arrivalTime (CPU is idle until P arrives).

Set P.startTime = currentTime.

Compute P.completionTime = currentTime + P.burstTime.

Calculate:

turnaround = P.completionTime − P.arrivalTime

waiting = turnaround − P.burstTime

response = P.startTime − P.arrivalTime

Accumulate these into running totals, then currentTime = P.completionTime.

After all processes finish, divide each total (turnaround, waiting, response) by n to get the averages.

2. Shortest Job First (SJF, Non‐Preemptive)
Maintain a boolean array completed[i] = false for each process i.

Initialize currentTime = 0 and completedCount = 0.

While completedCount < n:

Among all processes i with arrivalTime ≤ currentTime and completed[i] == false, pick the one with the smallest burstTime (break ties arbitrarily).

If none have arrived yet, set currentTime = (minimum arrivalTime of any unfinished process) and retry.

For the chosen process k:

startTime = currentTime

completionTime = currentTime + burstTime

Compute turnaround, waiting, response exactly as in FCFS and add to totals.

Mark completed[k] = true; increment completedCount.

Advance currentTime = completionTime.

Compute average metrics by dividing each sum by n.

3. Round Robin (RR, Preemptive)
Track for each process:

remainingTime = burstTime

startTime = -1 (not started)

added[i] = false: whether it has been enqueued at least once

completed[i] = false

Use a simple circular queue (array of size n plus front, rear, countQueue) to hold indices of ready processes.

Initialize currentTime = 0.

Enqueue every process i with arrivalTime ≤ 0:

queue[rear++] = i; added[i] = true; inQueue[i] = true; countQueue++

While completedCount < n:

If the queue is empty:

Fast‐forward currentTime = (minimum arrivalTime among all processes not yet added)

Enqueue any process whose arrivalTime ≤ currentTime && added[i] == false

Dequeue index idx = queue[front++]; inQueue[idx] = false;

If startTime[idx] < 0, set startTime[idx] = currentTime (first time it gets CPU).

Execute slice = min(remainingTime[idx], timeQuantum):

currentTime += slice

remainingTime[idx] -= slice

After advancing time, enqueue any newly arrived processes j with arrivalTime[j] ≤ currentTime && added[j] == false (mark added[j] = true).

If remainingTime[idx] > 0 (still not finished), re‐enqueue idx (queue[rear++] = idx; inQueue[idx] = true;).
Else (remainingTime[idx] == 0), set:

completionTime[idx] = currentTime

completed[idx] = true; completedCount++

## Notes

- The `Process` struct contains fields for tracking all timing metrics.
- All algorithms are non-preemptive except RR which uses time slicing.
- The project is written in standard C and should work on any Unix-like system (Linux, macOS, WSL).
