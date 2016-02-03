

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

CCINC   = -I$(OBJDIR)
APP_DEP = 
#$(SRCDIR)/rpi-interrupts.h

CCFLAGS = -g -c -O0 -DRPI2 -nostartfiles -o$@

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
	$(OBJDIR)/start.o \
	$(OBJDIR)/notmain.o \
	$(OBJDIR)/irq.o \
	$(OBJDIR)/memory.o \
	$(OBJDIR)/processor.o \
	$(OBJDIR)/uart.o
	$(LINK) \
	$(OBJDIR)/start.o \
	$(OBJDIR)/notmain.o \
	$(OBJDIR)/irq.o \
	$(OBJDIR)/memory.o \
	$(OBJDIR)/processor.o \
	$(OBJDIR)/uart.o \
	$(LINKFLAGS)

$(BINDIR): 
	mkdir $(BINDIR)

$(OBJDIR): 
	mkdir $(OBJDIR)

$(OBJDIR)/start.o: $(SRCDIR)/boot/start.s $(OBJDIR)
	$(ASM) $(ASMFLAGS) $<

$(OBJDIR)/irq.o: $(SRCDIR)/boot/irq.c $(APP_DEP) $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

$(OBJDIR)/notmain.o: $(SRCDIR)/boot/notmain.c $(APP_DEP) $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

$(OBJDIR)/memory.o: $(SRCDIR)/memory/memory.c $(APP_DEP) $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

$(OBJDIR)/processor.o: $(SRCDIR)/processor/processor.c $(APP_DEP) $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

$(OBJDIR)/uart.o: $(SRCDIR)/device/uart.c $(APP_DEP) $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

clean:
	-$(RM) $(BINDIR)/*.*
	-$(RM) $(OBJDIR)/*.*
