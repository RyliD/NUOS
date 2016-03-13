#include "init.h"
#include "debug-write.h"

#define EMMC_BASE		0x3F300000
#define	EMMC_ARG2		0
#define EMMC_BLKSIZECNT		4
#define EMMC_ARG1		8
#define EMMC_CMDTM		0xC
#define EMMC_RESP0		0x10
#define EMMC_RESP1		0x14
#define EMMC_RESP2		0x18
#define EMMC_RESP3		0x1C
#define EMMC_DATA		0x20
#define EMMC_STATUS		0x24
#define EMMC_CONTROL0		0x28
#define EMMC_CONTROL1		0x2C
#define EMMC_INTERRUPT		0x30
#define EMMC_IRPT_MASK		0x34
#define EMMC_IRPT_EN		0x38
#define EMMC_CONTROL2		0x3C
#define EMMC_CAPABILITIES_0	0x40
#define EMMC_CAPABILITIES_1	0x44
#define EMMC_FORCE_IRPT		0x50
#define EMMC_BOOT_TIMEOUT	0x70
#define EMMC_DBG_SEL		0x74
#define EMMC_EXRDFIFO_CFG	0x80
#define EMMC_EXRDFIFO_EN	0x84
#define EMMC_TUNE_STEP		0x88
#define EMMC_TUNE_STEPS_STD	0x8C
#define EMMC_TUNE_STEPS_DDR	0x90
#define EMMC_SPI_INT_SPT	0xF0
#define EMMC_SLOTISR_VER	0xFC

//extern void memory_barrier();

unsigned int mmio_read(unsigned int reg)
{
	//memory_barrier();
	return *(volatile unsigned int *)(reg);
	//memory_barrier();
}

void sd_card_init()
{
	debug_write_string("+", 1);
  // Read the controller version
	unsigned int ver = mmio_read(EMMC_BASE + EMMC_SLOTISR_VER);
	unsigned int vendor = ver >> 24;
	unsigned int sdversion = (ver >> 16) & 0xff;
	unsigned int slot_status = ver & 0xff;
	//printf("EMMC: vendor %x, sdversion %x, slot_status %x\n", vendor, sdversion, slot_status);
	unsigned int hci_ver = sdversion;
	debug_write_hex(ver);
	if(hci_ver < 2)
	{
		//printf("EMMC: only SDHCI versions >= 3.0 are supported\n");
	}
}

