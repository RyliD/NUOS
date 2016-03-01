#ifndef MEMORY_H
#define MEMORY_H

extern void _invalidate_tlbs( void );
unsigned int mmu_section( unsigned int vadd, unsigned int padd, unsigned int flags );

#endif