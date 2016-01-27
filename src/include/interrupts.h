#ifndef INTERRUPTS_H
#define INTERRUPTS_H

extern uint32_t ARM_int_lock_SYS(void);
extern void ARM_int_unlock_SYS(uint32_t key);

extern void C_abort(void);
extern void C_fiq(void);
extern void C_irq(void);

#endif
