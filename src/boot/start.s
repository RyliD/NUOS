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
    LDR pc,reset_handler
    LDR pc,undefined_handler
    LDR pc,swi_handler
    LDR pc,prefetch_handler
    LDR pc,data_handler
    LDR pc,unused_handler
    LDR pc,irq_handler
    LDR pc,fiq_handler
reset_handler:      .word _reset
undefined_handler:  .word _hang
swi_handler:        .word _hang
prefetch_handler:   .word _hang
data_handler:       .word _hang
unused_handler:     .word _hang
irq_handler:        .word _irq
fiq_handler:        .word _hang

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

    BL notmain
_hang: B _hang

.globl _enable_interrupts
_enable_interrupts:
    MRS     r0, CPSR
    BIC     r0, r0, #CPSR_IRQ_DISABLE
    MSR     CPSR_c, r0
    BX      lr

_irq:
    PUSH    {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    BL      c_irq_handler
    POP     {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    SUBS    pc, lr, #4
