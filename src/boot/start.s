.equ    CPSR_IRQ_DISABLE,    0x80
.equ    CPSR_FIQ_DISABLE,    0x40

.equ    CPSR_USR_MODE,       0x10
.equ    CPSR_FIQ_MODE,       0x11
.equ    CPSR_IRQ_MODE,       0x12
.equ    CPSR_SVC_MODE,       0x13
.equ    CPSR_ABT_MODE,       0x17
.equ    CPSR_UND_MODE,       0x1B
.equ    CPSR_SYS_MODE,       0x1F

.equ    USR_STACK_TOP,       0x4000
.equ    FIQ_STACK_TOP,       0x4000
.equ    IRQ_STACK_TOP,       0x8000
.equ    SVC_STACK_TOP,       0x8000000
.equ    ABT_STACK_TOP,       0x4000
.equ    UND_STACK_TOP,       0x4000
.equ    SYS_STACK_TOP,       0x4000

.text
.code 32
.globl _start
_start:
    LDR pc, _reset_h
    LDR pc, _undef_vector_h
    LDR pc, _swi_vector_h
    LDR pc, _prefetch_abort_h
    LDR pc, _data_abort_h
    LDR pc, _unused_h
    LDR pc, _irq_vector_h
    LDR pc, _fiq_vector_h
_reset_h:           .word _reset
_undef_vector_h:    .word _hang
_swi_vector_h:      .word _swi_vector
_prefetch_abort_h:  .word _hang
_data_abort_h:      .word _hang
_unused_h:          .word _hang
_irq_vector_h:      .word _irq_vector
_fiq_vector_h:      .word _hang

_reset:
    MOV     r0,#0x8000
    MOV     r1,#0x0000
    LDMIA   r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
    STMIA   r1!,{r2,r3,r4,r5,r6,r7,r8,r9}
    LDMIA   r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
    STMIA   r1!,{r2,r3,r4,r5,r6,r7,r8,r9}

    /* Initialize stack pointers for all ARM modes */
    MSR     CPSR_c, #(CPSR_IRQ_MODE | CPSR_IRQ_DISABLE | CPSR_FIQ_DISABLE)
    MOV     sp, #IRQ_STACK_TOP

    MSR     CPSR_c, #(CPSR_FIQ_MODE | CPSR_IRQ_DISABLE | CPSR_FIQ_DISABLE)
    MOV     sp, #FIQ_STACK_TOP

    MSR     CPSR_c, #(CPSR_SVC_MODE | CPSR_IRQ_DISABLE | CPSR_FIQ_DISABLE)
    MOV     sp, #SVC_STACK_TOP

    MSR     CPSR_c, #(CPSR_ABT_MODE | CPSR_IRQ_DISABLE | CPSR_FIQ_DISABLE)
    MOV     sp, #ABT_STACK_TOP

    MSR     CPSR_c, #(CPSR_UND_MODE | CPSR_IRQ_DISABLE | CPSR_FIQ_DISABLE)
    MOV     sp, #UND_STACK_TOP

    MSR     CPSR_c, #(CPSR_SYS_MODE | CPSR_IRQ_DISABLE | CPSR_FIQ_DISABLE)
    MOV     sp, #SYS_STACK_TOP

    BL cstartup
_hang: B _hang

.globl _disable_interrupts
_disable_interrupts:
    /* todo: */
    BX      lr

.globl _enable_interrupts
_enable_interrupts:
    MRS     r0, CPSR
    BIC     r0, r0, #CPSR_IRQ_DISABLE
    MSR     CPSR_c, r0
    BX      lr

_irq_vector:
    PUSH    {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    BL      c_irq_handler
    POP     {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    SUBS    pc, lr, #4

_swi_vector:
    STMFD   sp!, {r0-r12, lr}
    LDR     r0, [lr, #-4]
    BIC     r0, r0, #0xff000000
    MOV     r1, sp
    MRS     r2, spsr
    STMFD   sp!, {r2}
    BL      c_swi_handler
    LDMFD   sp!, {r2}
    MSR     spsr, r2       
    LDMFD   sp!, {r0-r12, pc}^

.globl _get_stack_pointer
_get_stack_pointer:
    /* Return the stack pointer value */
    str     sp, [sp]
    ldr     r0, [sp]

    /* Return from the function */
    mov     pc, lr
    
.globl _get32
_get32:
    ldr r0,[r0]
    bx lr

.globl _put32
_put32:
    str r1,[r0]
    bx lr
