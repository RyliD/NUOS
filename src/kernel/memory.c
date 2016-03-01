#include "init.h"
#include "memory.h"

void init_memory()
{
//    static volatile __attribute__ ((aligned (0x4000))) unsigned PageTable[4096];
//    
//    unsigned base;
//    for (base = 0; base < 1024-16; base++)
//    {
//        // section descriptor (1 MB)
//        // outer and inner write back, write allocate, not shareable (fast but unsafe)
//        //PageTable[base] = base << 20 | 0x0140E;
//        // outer and inner write through, no write allocate, shareable (safe but slower)
//        PageTable[base] = base << 20 | 0x1040A;
//    }
//    for (; base < 4096; base++)
//    {
//        // shared device, never execute
//        PageTable[base] = base << 20 | 0x10416;
//    }
//
//    // set SMP bit in ACTLR
    unsigned auxctrl;
    asm volatile ("mrc p15, 0, %0, c1, c0,  1" : "=r" (auxctrl));
    auxctrl |= 1 << 6;
    asm volatile ("mcr p15, 0, %0, c1, c0,  1" :: "r" (auxctrl));
//
//    // set domain 0 to client
//    asm volatile ("mcr p15, 0, %0, c3, c0, 0" :: "r" (1));
//
//    // always use TTBR0
//    asm volatile ("mcr p15, 0, %0, c2, c0, 2" :: "r" (0));
//
//    // set TTBR0 (page table walk inner and outer non-cacheable, non-shareable memory)
//    asm volatile ("mcr p15, 0, %0, c2, c0, 0" :: "r" (0 | (unsigned) &PageTable));

    //asm volatile ("isb" ::: "memory");

    // enable MMU, caches and branch prediction in SCTLR
    unsigned mode;
    asm volatile ("mrc p15, 0, %0, c1, c0, 0" : "=r" (mode));
    mode |= 0x1805;
    asm volatile ("mcr p15, 0, %0, c1, c0, 0" :: "r" (mode) : "memory");
	
	_invalidate_tlbs();
}

#define MMUTABLEBASE 0x00004000

//-------------------------------------------------------------------
unsigned int mmu_section ( unsigned int vadd, unsigned int padd, unsigned int flags )
{
    unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    ra=vadd>>20;
    rb=MMUTABLEBASE|(ra<<2);
    rc=(padd&0xFFF00000)|0xC00|flags|2;
    //hexstrings(rb); hexstring(rc);
    _put32(rb,rc);
    return(0);
}
//-------------------------------------------------------------------
unsigned int mmu_small ( unsigned int vadd, unsigned int padd, unsigned int flags, unsigned int mmubase )
{
    unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    ra=vadd>>20;
    rb=MMUTABLEBASE|(ra<<2);
    rc=(mmubase&0xFFFFFC00)/*|(domain<<5)*/|1;
    //hexstrings(rb); hexstring(rc);
    _put32(rb,rc); //first level descriptor
    ra=(vadd>>12)&0xFF;
    rb=(mmubase&0xFFFFFC00)|(ra<<2);
    rc=(padd&0xFFFFF000)|(0xFF0)|flags|2;
    //hexstrings(rb); hexstring(rc);
    _put32(rb,rc); //second level descriptor
    return(0);
}
//------------------------------------------------------------------------