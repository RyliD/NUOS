ENTRY(_start)
SECTIONS
{
    . = 0x8000;
    .init : {
        *(.init .init.*)
    }
    
    .text : {
        *(.text .text.*)
        *(.rodata .rodata.*)
    }
    
    .data : {
        *(.data .data.*)
    }
    
    __bss_start__ = .;
    .bss : {
        *(.bss .bss.*)
    }
    __bss_end__ = . ;
    _end = .;
    
    /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) }
}