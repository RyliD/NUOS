#include "init.h"
#include "processor.h"
#include "functions.h"
#include "debug-write.h"

void init_processor()
{
	Task task = createTask();
	rq.currentTask = task;
	debug_write_hex(task.stackAddress);
	copyAndSwitchStack((int*)0x4000, (unsigned*)task.stackAddress);
	debug_write_string("RETURNED", 8);
	debug_write_hex( _get_stack_pointer());
}

Task createTask() {
	Task task;
	task.id = rq.numTasks;
	debug_write_hex( END_STACK_ADDRESS);
	debug_write_hex( STACK_SIZE);
	task.stackAddress = (END_STACK_ADDRESS - (STACK_SIZE * rq.numTasks));
	rq.tasks[rq.numTasks] = task;
	debug_write_hex( task.stackAddress);
	rq.numTasks++;
	return task;
}

Task copyCurrentTask() {
	unsigned int* registers = _get_all_registers();
}


void copyAndSwitchStack(unsigned* currentBaseAddress, unsigned* newBaseAddress) {
	int i;
	unsigned* cb = currentBaseAddress;
	unsigned* nb = newBaseAddress;
	debug_write_hex( _get_stack_pointer());
	debug_write_hex( _get_frame_pointer());
	debug_write_char('5');
	int stackSize = ((unsigned)cb - (unsigned)_get_stack_pointer()) / 4;
	for(i = 0; i <= stackSize; i++) {
		(*(nb - i)) = (*(cb - i));
	}
	int frameSize = ((unsigned)cb - (unsigned)_get_frame_pointer()) / 4;
	debug_write_hex( _get_stack_pointer());
	_set_frame_pointer((unsigned)(nb - frameSize));
	debug_write_hex( _get_stack_pointer());
	debug_write_hex( _get_frame_pointer());
}