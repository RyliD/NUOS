#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "types.h"

#define LR 13
#define REGISTERS 14
#define TASKS 3
#define STACK_SIZE 0x01000000
#define END_STACK_ADDRESS 0x0F000000
typedef struct {
	unsigned registers[14];
	unsigned id;
	unsigned stackAddress;
	unsigned sp;
	bool started;
} Task;

typedef struct {
	Task* currentTask;
	unsigned numTasks;
	unsigned maxTasks;
	Task tasks[TASKS];
} Runqueue;

static volatile Runqueue rq = (Runqueue) {0, 0, TASKS};

// a function that can be run in a new task
typedef void (*Function)();

void saveState(int*, int);
int createTask();
int getNextTask();
void switchToTask(int taskId, int*);
void startNewTask();
Task copyCurrentTask();
void copyAndSwitchStack(unsigned* currentBaseAddress, unsigned* newBaseAddress);
void print_1();
void print_2();

int c_schedule(int*, int);

// will not return 
void scheduleNextTask();

// create a new task to run function f
// will return once after invocation
// if/when f returns the task is killed
// returns the id for the new task
unsigned forkRun(Function f);

#endif