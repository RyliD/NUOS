#ifndef PROCESSOR_H
#define PROCESSOR_H

#define REGISTERS 14
#define STACK_SIZE 0x01000000
#define END_STACK_ADDRESS 0x0F000000
typedef struct {
	unsigned registers[14];
	unsigned id;
	unsigned stackAddress;
} Task;

typedef struct {
	Task currentTask;
	unsigned numTasks;
	unsigned maxTasks;
	Task tasks[2];
} Runqueue;

static volatile Runqueue rq = (Runqueue) {0, 0, 2};

Task createTask();
Task copyCurrentTask();
void copyAndSwitchStack(unsigned* currentBaseAddress, unsigned* newBaseAddress);

#endif