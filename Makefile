

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
APP_DEP = $(SRCDIR)\rpi-interrupts.h

CCFLAGS = -c -O0 -DRPI2 -mfpu=neon-vfpv4 -mfloat-abi=hard \
    -march=armv7-a -mtune=cortex-a7 -nostartfiles -o$@

ASMFLAGS = -o$@

LINKFLAGS = -T $(LINKER) -mfloat-abi=hard -o $(ELF) \
	-Wl,-Map,$(OBJDIR)/$(APP_NAME).map,--cref -lm -nostartfiles

all: $(NM) $(LIST) $(IMAGE)

$(NM) : $(ELF)
	arm-none-eabi-nm $(ELF) > $(NM)

$(LIST) : $(ELF)
	arm-none-eabi-objdump -d $(ELF) > $(LIST)

$(IMAGE) : $(ELF)
	arm-none-eabi-objcopy $(ELF) -O binary $(IMAGE) 
    
$(ELF) : \
	./$(LINKER) \
	$(OBJDIR)/boot/start.o \
	$(OBJDIR)/boot/cstartup.o \
	$(OBJDIR)/kernel.o \
	$(OBJDIR)/rpi-armtimer.o \
	$(OBJDIR)/rpi-gpio.o \
	$(OBJDIR)/rpi-interrupts.o \
	$(OBJDIR)/rpi-systimer.o \
	$(OBJDIR)/cstubs.o
	$(LINK) \
	$(OBJDIR)/boot/start.o \
	$(OBJDIR)/boot/cstartup.o \
	$(OBJDIR)/kernel.o \
	$(OBJDIR)/rpi-armtimer.o \
	$(OBJDIR)/rpi-gpio.o \
	$(OBJDIR)/rpi-interrupts.o \
	$(OBJDIR)/rpi-systimer.o \
	$(OBJDIR)/cstubs.o \
	$(LINKFLAGS)

$(BINDIR): 
	mkdir $(BINDIR)

$(OBJDIR): 
	mkdir $(OBJDIR)

$(OBJDIR)/boot: 
	mkdir $(OBJDIR)/boot

$(OBJDIR)/boot/start.o: $(SRCDIR)/boot/start.s $(OBJDIR) $(OBJDIR)/boot
	$(ASM) $(ASMFLAGS) $<

$(OBJDIR)/boot/cstartup.o: $(SRCDIR)/boot/cstartup.c $(APP_DEP) $(OBJDIR) $(OBJDIR)/boot
	$(CC) $(CCFLAGS) $(CCINC) $<

$(OBJDIR)/kernel.o: $(SRCDIR)/kernel.c $(APP_DEP) $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

$(OBJDIR)/rpi-armtimer.o: $(SRCDIR)/rpi-armtimer.c $(APP_DEP) $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

$(OBJDIR)/rpi-gpio.o: $(SRCDIR)/rpi-gpio.c $(APP_DEP) $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

$(OBJDIR)/rpi-interrupts.o: $(SRCDIR)/rpi-interrupts.c $(APP_DEP) $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

$(OBJDIR)/rpi-systimer.o: $(SRCDIR)/rpi-systimer.c $(APP_DEP)
	$(CC) $(CCFLAGS) $(CCINC) $<

$(OBJDIR)/cstubs.o: $(SRCDIR)/cstubs.c $(OBJDIR)
	$(CC) $(CCFLAGS) $(CCINC) $<

clean:
	-$(RM) $(BINDIR)/*.*
	-$(RM) $(OBJDIR)/*.*
