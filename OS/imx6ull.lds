SECTIONS {
    . = 0x80100000;

    . = ALIGN(4);
    .text      :
    {
  
      *(.text)
    }

    . = ALIGN(4);

    rodata_start = .;
    .rodata   : 
    { 
      *(.rodata)
    }
    

    . = ALIGN(4);
    rodata_end = .;

    data_start = .;
    .data : 
    {
       *(.data) 
    }

    . = ALIGN(4);
    __bss_start = .;
    .bss : 
    { 
      *(.bss) *(.COMMON) 
    }
    __bss_end = .;
    . = 0x80400000;
    Kernel_end = .;
}
