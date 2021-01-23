# ARCHIVED!
This is no longer actively devevloped, and has not been for many years.
Modern projects now use ARM Cortex microcontrollers with the mbed HAL.
The code is made available in case anyone is curious, or wants to see one approach to background SD card operations with DMA but without an RTOS.
No guarantees that this is a clean approach, or even clean code - I don't recommend using this codebase as a starting point for future code, but it might be a source for ideas.

This code supported a datalogger board (record CAN traffic to SD card) build around PIC24 series microcontrollers, and implemented an SD card + FAT file system layer where bulk transfers happened in the background using DMA and cooperative multitasking / polling.
Such an architecture allows high throughput and makes efficient use of the available compute power, by not having the CPU be blocked waiting for SD card IO operations (and not doing useful / "interesting" work).
It's also fairly complex.
And incomplete - it's write-only and makes other assumptions about the filesystem structure.


# datalogger

Datalogger with an optimized SD card and FAT32 filesystem layer using DMA.
