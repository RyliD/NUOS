#include "init.h"
#include "processor.h"
#include "functions.h"
#include "debug-write.h"

void print_1() {
	while(1){
		debug_write_char('1');
	}
}

void print_2() {
	while(1){
		debug_write_char('2');
	}
}

void init_processor()
{
	debug_write_char('a');
	int id = createTask();
	rq.tasks[id].started = true;
	rq.currentTask = rq.tasks[id];
	debug_write_hex(rq.tasks[id].stackAddress);
	forkRun(&print_1);
}

int createTask() {
	debug_write_string("task: ", 6);
	int id = rq.numTasks;
	debug_write_hex(id);
	rq.tasks[id].started = false;
	rq.tasks[id].id = id;
	rq.tasks[id].stackAddress = (END_STACK_ADDRESS - (STACK_SIZE * rq.numTasks));
	debug_write_hex(rq.tasks[id].stackAddress);
	rq.numTasks++;
	return id;
}

int c_schedule(int* regs, int sp) {
	debug_write_char('a');
	debug_write_hex(sp);
	saveState(regs, sp);
	int nextTask = getNextTask();
	debug_write_hex(nextTask);
	switchToTask(nextTask, regs);
	debug_write_char('b');
	debug_write_hex(rq.currentTask.sp);
	return rq.currentTask.sp;
}

int getNextTask() {
	return (rq.currentTask.id + 1) % rq.numTasks;
}

void switchToTask(int taskId, int* registers) {
	int i;
	rq.currentTask = rq.tasks[taskId];
	if(!rq.currentTask.started) {
		startNewTask();
	}
	for(i = 0; i < REGISTERS; i++) {
		debug_write_hex(i);
		debug_write_hex(&registers[i]);
		debug_write_hex(&rq.currentTask.registers[i]);
		debug_write_hex(registers[i]);
		debug_write_hex(rq.currentTask.registers[i]);
		registers[i] = rq.currentTask.registers[LR];
	}
}

void startNewTask() {
	int i;
	// debug_write_hex(rq.currentTask.id);
	// debug_write_hex(rq.currentTask.stackAddress);
	// for(i = 0; i < REGISTERS; i++){
		// rq.currentTask.sp = rq.currentTask.stackAddress
					// - (i * 4);
		// *(int*)rq.currentTask.sp = 
			// rq.currentTask.registers[
			// (REGISTERS - (i + 1)) / REGISTERS];
	// }
	rq.currentTask.started = true;
}

void scheduleNextTask() {
	
}

void saveState(int* registers, int sp) {
	int i;
	for(i = 0; i < REGISTERS; i++) {
		rq.currentTask.registers[i] = registers[i];
	}
	//rq.currentTask.sp = sp;
}

Task copyCurrentTask() {
	unsigned int* registers = _get_all_registers();
}

unsigned forkRun(Function f) {
	int id = createTask();
	rq.tasks[id].registers[LR] = ((int)f) + 4;
}


void copyAndSwitchStack(unsigned* currentBaseAddress, unsigned* newBaseAddress) {
	int i;
	unsigned* cb = currentBaseAddress;
	unsigned* nb = newBaseAddress;
	int stackSize = ((unsigned)cb - (unsigned)_get_stack_pointer()) / 4;
	for(i = 0; i <= stackSize; i++) {
		(*(nb - i)) = (*(cb - i));
	}
	int frameSize = ((unsigned)cb - (unsigned)_get_frame_pointer()) / 4;
	_set_frame_pointer((unsigned)(nb - frameSize));
}