STM32 template for CodeBlocks

1 - This template was made with STM32F0 drivers (HAL) and the code is fully functional on
STM32F0 Discovery. Running this project the two LEDs will blink.

2 - Despite the CB has been designed to run on cross platforms ,  this template is made on Linux.

3 - You will need install:

	a) arm-none-eabi* (gcc, binutils,...)
	b) OpenOCD to debug
	c) stlink (st-flash, ...)  to flash without debug : https://github.com/texane/stlink
	    
4 - Setup gcc-arm:

a)	Go CodeBlocks Menu Settings->Compiler
	In "Selected Compiler" press button Copy and rename it
	Select your new compiler in "Selected Compiler"
	
	On Tab "Search Directories" add the includes path of your arm-none-eabi-* includes 
installed on "Compiler" and lib path on "Linker"
	On Tab "ToolChain executables" set the name e path (if necessary) of each executable
	
	on my machine (archlinux) 
	
	C compiler : arm-none-eabi-gcc
	C++ compiler: arm-none-eabi-g++
	Linker for dyn...: arm-none-eabi-g++
	Linker for static ...: arm-none-eabi-ar
	Make program: make

a-3)	Debugger, you will setup later (don't forget!)

b)   Go Menu Settings->Debugger

	Select GDB/CDB debugger and click "Create Config". Write a name.
        On new created config fill "Executable path:" with your arm-none-eabi-gdb path 
        In my machine (archlinux): /usr/bin/arm-none-eabi-gdb
	Click on "Do *not* run de debugee"
	Return to previous Compiler setting and select your new Debugger config (a-3)

6 - Before debugging any code is necessary run OpenOCD from terminal or - the best choice - 
from a configured Tools in the CB menu

	Run Openoncd with: openocd -f board/stm32f0discovery.cfg	

## ADD More MCU
	
	Download STM32Cube for your MCU.
	Copy content of Driver folder to Drivers of this template
	Correct includes path, MCU Define....


	
