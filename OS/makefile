
PREFIX=arm-linux-gnueabihf-
CC=$(PREFIX)gcc
LD=$(PREFIX)ld
BUILD_O= $(CC) -nostdlib  -g -c -o 
OBJCOPY=$(PREFIX)objcopy
OBJDUMP=$(PREFIX)objdump
PRINT = my_printf.o string_utils.o uart.o
KERNEL = bootloader.o main.o
MEMMORY = kalloc.o vm.o 
GENERAL = string.o print_test.o
EXCEPTION = trap.o trapasm.o 
os.img: $(PRINT) $(KERNEL) $(MEMMORY) $(GENERAL) $(EXCEPTION)
	$(LD) -T imx6ull.lds -g $(KERNEL) $(PRINT) $(MEMMORY) $(GENERAL) $(EXCEPTION) -o os.elf -lgcc -L ~/ToolChain/gcc-linaro-6.2.1-2016.11-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/6.2.1
	
	$(OBJCOPY) -O binary -S os.elf  os.bin
	$(OBJDUMP) -D -m arm  os.elf  > os.dis	
	mkimage -n ./tools/imximage.cfg.cfgtmp -T imximage -e 0x80100000 -d os.bin os.imx
	dd if=/dev/zero of=1k.bin bs=1024 count=1
	cat 1k.bin os.imx > os.img



#uart

	
my_printf.o:./uart/my_printf.c 
	$(BUILD_O) my_printf.o ./uart/my_printf.c

string_utils.o:./uart/string_utils.c 
	$(BUILD_O)  string_utils.o ./uart/string_utils.c 

uart.o:./uart/uart.c 
	$(BUILD_O)  uart.o ./uart/uart.c

#kernel
bootloader.o:./Kernel/bootloader.S
	$(BUILD_O) bootloader.o ./Kernel/bootloader.S
main.o:./Kernel/main.c
	$(BUILD_O) main.o ./Kernel/main.c
#memory
kalloc.o:./Memory_Manage/kalloc.c
	$(BUILD_O) kalloc.o ./Memory_Manage/kalloc.c

vm.o:./Memory_Manage/vm.c
	$(BUILD_O) vm.o ./Memory_Manage/vm.c

#general
string.o:./General/string.c
	$(BUILD_O) string.o ./General/string.c

print_test.o:./General/print_test.c
	$(BUILD_O) print_test.o ./General/print_test.c

#exception
trap.o:./EXCEPTION/trap.c
	$(BUILD_O) trap.o ./EXCEPTION/trap.c 

trapasm.o:./EXCEPTION/trapasm.S 
	$(BUILD_O) trapasm.o ./EXCEPTION/trapasm.S


clean:
	rm -f $(EXCEPTION) $(MEMMORY) $(GENERAL) $(PRINT) $(KERNEL) os.bin os.dis os.elf os.img os.imx