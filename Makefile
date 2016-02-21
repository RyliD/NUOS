

APP_NAME = kernel7

CC      = arm-none-eabi-gcc
ASM     = arm-none-eabi-as
LINK    = arm-none-eabi-gcc
RM      = rm -f

BINDIR  = bin
OBJDIR  = obj
SRCDIR  = src

LINKER  = $(APP_NAME).ld

ELF     = $(BINDIR)/$(APP_NAME).elf
IMAGE   = $(BINDIR)/$(APP_NAME).img
NM      = $(BINDIR)/$(APP_NAME).nm
LIST    = $(BINDIR)/$(APP_NAME).list

CCINC   = -I$(SRCDIR)/include -I$(SRCDIR)/arch/pi/include -I$(OBJDIR)

CCFLAGS = -c -O0 -DRPI2 -nostartfiles -o$@

ASMFLAGS = -o$@

LINKFLAGS = -T $(LINKER) -o $(ELF) \
	-Wl,-Map,$(OBJDIR)/$(APP_NAME).map,--cref -lm -nostartfiles

all: $(NM) $(LIST) $(IMAGE)

$(NM) : $(ELF)
	arm-none-eabi-nm $(ELF) > $(NM)

$(LIST) : $(ELF)
	arm-none-eabi-objdump -d $(ELF) > $(LIST)

$(IMAGE) : $(ELF)
	arm-none-eabi-objcopy $(ELF) -O binary $(IMAGE) 
    
$(ELF) : $(BINDIR) \
	./$(LINKER) \
	$(OBJDIR)/boot/start.o \
	$(OBJDIR)/boot/irq.o \
	$(OBJDIR)/boot/swi.o \
	$(OBJDIR)/boot/cstartup.o \
	$(OBJDIR)/kernel.o \
	$(OBJDIR)/memory.o \
	$(OBJDIR)/processor.o \
	$(OBJDIR)/rpi-armtimer.o \
	$(OBJDIR)/rpi-gpio.o \
	$(OBJDIR)/rpi-irq.o \
	$(OBJDIR)/rpi-uart.o \
	$(OBJDIR)/syscall.o
	$(LINK) \
	$(OBJDIR)/boot/start.o \
	$(OBJDIR)/boot/irq.o \
	$(OBJDIR)/boot/swi.o \
	$(OBJDIR)/boot/cstartup.o \
	$(OBJDIR)/kernel.o \
	$(OBJDIR)/memory.o \
	$(OBJDIR)/processor.o \
	$(OBJDIR)/rpi-armtimer.o \
	$(OBJDIR)/rpi-gpio.o \
	$(OBJDIR)/rpi-irq.o \
	$(OBJDIR)/rpi-uart.o \
	$(OBJDIR)/syscall.o \
	$(LINKFLAGS)

$(BINDIR): 
	mkdir $(BINDIR)

$(OBJDIR): 
	mkdir $(OBJDIR)

$(OBJDIR)/boot: 
	mkdir $(OBJDIR)/boot

# boot
$(OBJDIR)/boot/start.o: $(SRCDIR)/boot/start.s $(OBJDIR) $(OBJDIR)/boot
	$(ASM) $(ASMFLAGS) $<

$(OBJDIR)/boot/irq.o: $(SRCDIR)/boot/irq.c $(OBJDIR) $(OBJDIR)/boot
	$(CC) $(CCFLAGS) $(CCINC) $<

$(OBJDIR)/boot/swi.o: $(SRCDIR)/boot/swi.c $(OBJDIR) $(OBJDIR)/boot
	$(CC) $(CCFLAGS) $(CCINC) $<

$(OBJDIR)/boot/cstartup.o: $(SRCDIR)/boot/cstartup.c $(OBJDIR) $(OBJDIR)/boot
	$(CC) $(CCFLAGS) $(CCINC) $<

$(OBJDIR)/kernel.o: $(SRCDIR)/kernel.c $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

# memory
$(OBJDIR)/memory.o: $(SRCDIR)/memory/memory.c $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

# processor
$(OBJDIR)/processor.o: $(SRCDIR)/processor/processor.c $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

# pi
$(OBJDIR)/rpi-armtimer.o: $(SRCDIR)/arch/pi/rpi-armtimer.c $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<
    
$(OBJDIR)/rpi-gpio.o: $(SRCDIR)/arch/pi/rpi-gpio.c $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

$(OBJDIR)/rpi-irq.o: $(SRCDIR)/arch/pi/rpi-irq.c $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

$(OBJDIR)/rpi-uart.o: $(SRCDIR)/arch/pi/rpi-uart.c $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

# lib
$(OBJDIR)/syscall.o: $(SRCDIR)/syscall.c $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

clean:
	-$(RM) $(BINDIR)/*.*
	-$(RM) $(OBJDIR)/*.*
