#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-CanBridge_Production.mk)" "nbproject/Makefile-local-CanBridge_Production.mk"
include nbproject/Makefile-local-CanBridge_Production.mk
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=CanBridge_Production
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/calsol-datalogger-pic24h.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/calsol-datalogger-pic24h.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Datalogger/datalogger-autoterminate.o ${OBJECTDIR}/Datalogger/datalogger-can.o ${OBJECTDIR}/Datalogger/datalogger-file.o ${OBJECTDIR}/Datalogger/datalogger-perflogger.o ${OBJECTDIR}/Datalogger/datalogger-stringutil.o ${OBJECTDIR}/Datalogger/datalogger.o ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o ${OBJECTDIR}/debug-common.o ${OBJECTDIR}/debug-log.o ${OBJECTDIR}/uart-dma.o ${OBJECTDIR}/ecan.o ${OBJECTDIR}/FAT32/fat32-file-create.o ${OBJECTDIR}/FAT32/fat32-file-tasks.o ${OBJECTDIR}/FAT32/fat32-file-util.o ${OBJECTDIR}/FAT32/fat32-file-write.o ${OBJECTDIR}/FAT32/fat32-init.o ${OBJECTDIR}/FAT32/fat32-util.o ${OBJECTDIR}/Hardware/board-run3.o ${OBJECTDIR}/Hardware/board-datalogger-1-4.o ${OBJECTDIR}/I2CDevices/i2c-hardware.o ${OBJECTDIR}/I2CDevices/mcp23018.o ${OBJECTDIR}/I2CDevices/pcf8523.o ${OBJECTDIR}/I2CDevices/lis331.o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o ${OBJECTDIR}/SD-SPI-DMA/sd-events.o ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o ${OBJECTDIR}/timing-run2.o ${OBJECTDIR}/timing-run3.o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o ${OBJECTDIR}/main.o ${OBJECTDIR}/configuration_bits.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.d ${OBJECTDIR}/Datalogger/datalogger-can.o.d ${OBJECTDIR}/Datalogger/datalogger-file.o.d ${OBJECTDIR}/Datalogger/datalogger-perflogger.o.d ${OBJECTDIR}/Datalogger/datalogger-stringutil.o.d ${OBJECTDIR}/Datalogger/datalogger.o.d ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.d ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.d ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.d ${OBJECTDIR}/debug-common.o.d ${OBJECTDIR}/debug-log.o.d ${OBJECTDIR}/uart-dma.o.d ${OBJECTDIR}/ecan.o.d ${OBJECTDIR}/FAT32/fat32-file-create.o.d ${OBJECTDIR}/FAT32/fat32-file-tasks.o.d ${OBJECTDIR}/FAT32/fat32-file-util.o.d ${OBJECTDIR}/FAT32/fat32-file-write.o.d ${OBJECTDIR}/FAT32/fat32-init.o.d ${OBJECTDIR}/FAT32/fat32-util.o.d ${OBJECTDIR}/Hardware/board-run3.o.d ${OBJECTDIR}/Hardware/board-datalogger-1-4.o.d ${OBJECTDIR}/I2CDevices/i2c-hardware.o.d ${OBJECTDIR}/I2CDevices/mcp23018.o.d ${OBJECTDIR}/I2CDevices/pcf8523.o.d ${OBJECTDIR}/I2CDevices/lis331.o.d ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.d ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.d ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.d ${OBJECTDIR}/SD-SPI-DMA/sd-events.o.d ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.d ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.d ${OBJECTDIR}/timing-run2.o.d ${OBJECTDIR}/timing-run3.o.d ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.d ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.d ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.d ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/configuration_bits.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Datalogger/datalogger-autoterminate.o ${OBJECTDIR}/Datalogger/datalogger-can.o ${OBJECTDIR}/Datalogger/datalogger-file.o ${OBJECTDIR}/Datalogger/datalogger-perflogger.o ${OBJECTDIR}/Datalogger/datalogger-stringutil.o ${OBJECTDIR}/Datalogger/datalogger.o ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o ${OBJECTDIR}/debug-common.o ${OBJECTDIR}/debug-log.o ${OBJECTDIR}/uart-dma.o ${OBJECTDIR}/ecan.o ${OBJECTDIR}/FAT32/fat32-file-create.o ${OBJECTDIR}/FAT32/fat32-file-tasks.o ${OBJECTDIR}/FAT32/fat32-file-util.o ${OBJECTDIR}/FAT32/fat32-file-write.o ${OBJECTDIR}/FAT32/fat32-init.o ${OBJECTDIR}/FAT32/fat32-util.o ${OBJECTDIR}/Hardware/board-run3.o ${OBJECTDIR}/Hardware/board-datalogger-1-4.o ${OBJECTDIR}/I2CDevices/i2c-hardware.o ${OBJECTDIR}/I2CDevices/mcp23018.o ${OBJECTDIR}/I2CDevices/pcf8523.o ${OBJECTDIR}/I2CDevices/lis331.o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o ${OBJECTDIR}/SD-SPI-DMA/sd-events.o ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o ${OBJECTDIR}/timing-run2.o ${OBJECTDIR}/timing-run3.o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o ${OBJECTDIR}/main.o ${OBJECTDIR}/configuration_bits.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-CanBridge_Production.mk dist/${CND_CONF}/${IMAGE_TYPE}/calsol-datalogger-pic24h.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC802
MP_LINKER_FILE_OPTION=,-Tp33FJ128MC802.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Datalogger/datalogger-autoterminate.o: Datalogger/datalogger-autoterminate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.ok ${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.d" -o ${OBJECTDIR}/Datalogger/datalogger-autoterminate.o Datalogger/datalogger-autoterminate.c  
	
${OBJECTDIR}/Datalogger/datalogger-can.o: Datalogger/datalogger-can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-can.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-can.o.ok ${OBJECTDIR}/Datalogger/datalogger-can.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-can.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-can.o.d" -o ${OBJECTDIR}/Datalogger/datalogger-can.o Datalogger/datalogger-can.c  
	
${OBJECTDIR}/Datalogger/datalogger-file.o: Datalogger/datalogger-file.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-file.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-file.o.ok ${OBJECTDIR}/Datalogger/datalogger-file.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-file.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-file.o.d" -o ${OBJECTDIR}/Datalogger/datalogger-file.o Datalogger/datalogger-file.c  
	
${OBJECTDIR}/Datalogger/datalogger-perflogger.o: Datalogger/datalogger-perflogger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-perflogger.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-perflogger.o.ok ${OBJECTDIR}/Datalogger/datalogger-perflogger.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-perflogger.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-perflogger.o.d" -o ${OBJECTDIR}/Datalogger/datalogger-perflogger.o Datalogger/datalogger-perflogger.c  
	
${OBJECTDIR}/Datalogger/datalogger-stringutil.o: Datalogger/datalogger-stringutil.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-stringutil.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-stringutil.o.ok ${OBJECTDIR}/Datalogger/datalogger-stringutil.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-stringutil.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-stringutil.o.d" -o ${OBJECTDIR}/Datalogger/datalogger-stringutil.o Datalogger/datalogger-stringutil.c  
	
${OBJECTDIR}/Datalogger/datalogger.o: Datalogger/datalogger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger.o.ok ${OBJECTDIR}/Datalogger/datalogger.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger.o.d" -o ${OBJECTDIR}/Datalogger/datalogger.o Datalogger/datalogger.c  
	
${OBJECTDIR}/Datalogger/datalogger-accelerometer.o: Datalogger/datalogger-accelerometer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.ok ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.d" -o ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o Datalogger/datalogger-accelerometer.c  
	
${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o: Datalogger/datalogger-voltagelogger-run3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.ok ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.d" -o ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o Datalogger/datalogger-voltagelogger-run3.c  
	
${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o: Datalogger/datalogger-voltagelogger-datalogger-1-4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.ok ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.d" -o ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o Datalogger/datalogger-voltagelogger-datalogger-1-4.c  
	
${OBJECTDIR}/debug-common.o: debug-common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/debug-common.o.d 
	@${RM} ${OBJECTDIR}/debug-common.o.ok ${OBJECTDIR}/debug-common.o.err 
	@${FIXDEPS} "${OBJECTDIR}/debug-common.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/debug-common.o.d" -o ${OBJECTDIR}/debug-common.o debug-common.c  
	
${OBJECTDIR}/debug-log.o: debug-log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/debug-log.o.d 
	@${RM} ${OBJECTDIR}/debug-log.o.ok ${OBJECTDIR}/debug-log.o.err 
	@${FIXDEPS} "${OBJECTDIR}/debug-log.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/debug-log.o.d" -o ${OBJECTDIR}/debug-log.o debug-log.c  
	
${OBJECTDIR}/uart-dma.o: uart-dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/uart-dma.o.d 
	@${RM} ${OBJECTDIR}/uart-dma.o.ok ${OBJECTDIR}/uart-dma.o.err 
	@${FIXDEPS} "${OBJECTDIR}/uart-dma.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/uart-dma.o.d" -o ${OBJECTDIR}/uart-dma.o uart-dma.c  
	
${OBJECTDIR}/ecan.o: ecan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ecan.o.d 
	@${RM} ${OBJECTDIR}/ecan.o.ok ${OBJECTDIR}/ecan.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ecan.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/ecan.o.d" -o ${OBJECTDIR}/ecan.o ecan.c  
	
${OBJECTDIR}/FAT32/fat32-file-create.o: FAT32/fat32-file-create.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-create.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-create.o.ok ${OBJECTDIR}/FAT32/fat32-file-create.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-file-create.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/FAT32/fat32-file-create.o.d" -o ${OBJECTDIR}/FAT32/fat32-file-create.o FAT32/fat32-file-create.c  
	
${OBJECTDIR}/FAT32/fat32-file-tasks.o: FAT32/fat32-file-tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-tasks.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-tasks.o.ok ${OBJECTDIR}/FAT32/fat32-file-tasks.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-file-tasks.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/FAT32/fat32-file-tasks.o.d" -o ${OBJECTDIR}/FAT32/fat32-file-tasks.o FAT32/fat32-file-tasks.c  
	
${OBJECTDIR}/FAT32/fat32-file-util.o: FAT32/fat32-file-util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-util.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-util.o.ok ${OBJECTDIR}/FAT32/fat32-file-util.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-file-util.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/FAT32/fat32-file-util.o.d" -o ${OBJECTDIR}/FAT32/fat32-file-util.o FAT32/fat32-file-util.c  
	
${OBJECTDIR}/FAT32/fat32-file-write.o: FAT32/fat32-file-write.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-write.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-write.o.ok ${OBJECTDIR}/FAT32/fat32-file-write.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-file-write.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/FAT32/fat32-file-write.o.d" -o ${OBJECTDIR}/FAT32/fat32-file-write.o FAT32/fat32-file-write.c  
	
${OBJECTDIR}/FAT32/fat32-init.o: FAT32/fat32-init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-init.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-init.o.ok ${OBJECTDIR}/FAT32/fat32-init.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-init.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/FAT32/fat32-init.o.d" -o ${OBJECTDIR}/FAT32/fat32-init.o FAT32/fat32-init.c  
	
${OBJECTDIR}/FAT32/fat32-util.o: FAT32/fat32-util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-util.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-util.o.ok ${OBJECTDIR}/FAT32/fat32-util.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-util.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/FAT32/fat32-util.o.d" -o ${OBJECTDIR}/FAT32/fat32-util.o FAT32/fat32-util.c  
	
${OBJECTDIR}/Hardware/board-run3.o: Hardware/board-run3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Hardware 
	@${RM} ${OBJECTDIR}/Hardware/board-run3.o.d 
	@${RM} ${OBJECTDIR}/Hardware/board-run3.o.ok ${OBJECTDIR}/Hardware/board-run3.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Hardware/board-run3.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Hardware/board-run3.o.d" -o ${OBJECTDIR}/Hardware/board-run3.o Hardware/board-run3.c  
	
${OBJECTDIR}/Hardware/board-datalogger-1-4.o: Hardware/board-datalogger-1-4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Hardware 
	@${RM} ${OBJECTDIR}/Hardware/board-datalogger-1-4.o.d 
	@${RM} ${OBJECTDIR}/Hardware/board-datalogger-1-4.o.ok ${OBJECTDIR}/Hardware/board-datalogger-1-4.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Hardware/board-datalogger-1-4.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Hardware/board-datalogger-1-4.o.d" -o ${OBJECTDIR}/Hardware/board-datalogger-1-4.o Hardware/board-datalogger-1-4.c  
	
${OBJECTDIR}/I2CDevices/i2c-hardware.o: I2CDevices/i2c-hardware.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/I2CDevices 
	@${RM} ${OBJECTDIR}/I2CDevices/i2c-hardware.o.d 
	@${RM} ${OBJECTDIR}/I2CDevices/i2c-hardware.o.ok ${OBJECTDIR}/I2CDevices/i2c-hardware.o.err 
	@${FIXDEPS} "${OBJECTDIR}/I2CDevices/i2c-hardware.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/I2CDevices/i2c-hardware.o.d" -o ${OBJECTDIR}/I2CDevices/i2c-hardware.o I2CDevices/i2c-hardware.c  
	
${OBJECTDIR}/I2CDevices/mcp23018.o: I2CDevices/mcp23018.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/I2CDevices 
	@${RM} ${OBJECTDIR}/I2CDevices/mcp23018.o.d 
	@${RM} ${OBJECTDIR}/I2CDevices/mcp23018.o.ok ${OBJECTDIR}/I2CDevices/mcp23018.o.err 
	@${FIXDEPS} "${OBJECTDIR}/I2CDevices/mcp23018.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/I2CDevices/mcp23018.o.d" -o ${OBJECTDIR}/I2CDevices/mcp23018.o I2CDevices/mcp23018.c  
	
${OBJECTDIR}/I2CDevices/pcf8523.o: I2CDevices/pcf8523.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/I2CDevices 
	@${RM} ${OBJECTDIR}/I2CDevices/pcf8523.o.d 
	@${RM} ${OBJECTDIR}/I2CDevices/pcf8523.o.ok ${OBJECTDIR}/I2CDevices/pcf8523.o.err 
	@${FIXDEPS} "${OBJECTDIR}/I2CDevices/pcf8523.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/I2CDevices/pcf8523.o.d" -o ${OBJECTDIR}/I2CDevices/pcf8523.o I2CDevices/pcf8523.c  
	
${OBJECTDIR}/I2CDevices/lis331.o: I2CDevices/lis331.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/I2CDevices 
	@${RM} ${OBJECTDIR}/I2CDevices/lis331.o.d 
	@${RM} ${OBJECTDIR}/I2CDevices/lis331.o.ok ${OBJECTDIR}/I2CDevices/lis331.o.err 
	@${FIXDEPS} "${OBJECTDIR}/I2CDevices/lis331.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/I2CDevices/lis331.o.d" -o ${OBJECTDIR}/I2CDevices/lis331.o I2CDevices/lis331.c  
	
${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o: SD-SPI-DMA/sd-dma-multipleblockwrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.ok ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.err 
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.d" -o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o SD-SPI-DMA/sd-dma-multipleblockwrite.c  
	
${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o: SD-SPI-DMA/sd-dma-singleblockread.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.ok ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.err 
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.d" -o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o SD-SPI-DMA/sd-dma-singleblockread.c  
	
${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o: SD-SPI-DMA/sd-dma-singleblockwrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.ok ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.err 
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.d" -o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o SD-SPI-DMA/sd-dma-singleblockwrite.c  
	
${OBJECTDIR}/SD-SPI-DMA/sd-events.o: SD-SPI-DMA/sd-events.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-events.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-events.o.ok ${OBJECTDIR}/SD-SPI-DMA/sd-events.o.err 
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-events.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-events.o.d" -o ${OBJECTDIR}/SD-SPI-DMA/sd-events.o SD-SPI-DMA/sd-events.c  
	
${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o: SD-SPI-DMA/sd-hardware.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.ok ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.err 
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.d" -o ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o SD-SPI-DMA/sd-hardware.c  
	
${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o: SD-SPI-DMA/sd-initialize.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.ok ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.err 
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.d" -o ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o SD-SPI-DMA/sd-initialize.c  
	
${OBJECTDIR}/timing-run2.o: timing-run2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timing-run2.o.d 
	@${RM} ${OBJECTDIR}/timing-run2.o.ok ${OBJECTDIR}/timing-run2.o.err 
	@${FIXDEPS} "${OBJECTDIR}/timing-run2.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/timing-run2.o.d" -o ${OBJECTDIR}/timing-run2.o timing-run2.c  
	
${OBJECTDIR}/timing-run3.o: timing-run3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timing-run3.o.d 
	@${RM} ${OBJECTDIR}/timing-run3.o.ok ${OBJECTDIR}/timing-run3.o.err 
	@${FIXDEPS} "${OBJECTDIR}/timing-run3.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/timing-run3.o.d" -o ${OBJECTDIR}/timing-run3.o timing-run3.c  
	
${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o: UserInterface/datalogger-ui-hardware-canbridge.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/UserInterface 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.d 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.ok ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.err 
	@${FIXDEPS} "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.d" -o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o UserInterface/datalogger-ui-hardware-canbridge.c  
	
${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o: UserInterface/datalogger-ui-hardware-run3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/UserInterface 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.d 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.ok ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.err 
	@${FIXDEPS} "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.d" -o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o UserInterface/datalogger-ui-hardware-run3.c  
	
${OBJECTDIR}/UserInterface/datalogger-ui-leds.o: UserInterface/datalogger-ui-leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/UserInterface 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.d 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.ok ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.err 
	@${FIXDEPS} "${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.d" -o ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o UserInterface/datalogger-ui-leds.c  
	
${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o: UserInterface/datalogger-ui-hardware-datalogger-1-4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/UserInterface 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.d 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.ok ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.err 
	@${FIXDEPS} "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.d" -o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o UserInterface/datalogger-ui-hardware-datalogger-1-4.c  
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o.ok ${OBJECTDIR}/main.o.err 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c  
	
${OBJECTDIR}/configuration_bits.o: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/configuration_bits.o.d 
	@${RM} ${OBJECTDIR}/configuration_bits.o.ok ${OBJECTDIR}/configuration_bits.o.err 
	@${FIXDEPS} "${OBJECTDIR}/configuration_bits.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/configuration_bits.o.d" -o ${OBJECTDIR}/configuration_bits.o configuration_bits.c  
	
else
${OBJECTDIR}/Datalogger/datalogger-autoterminate.o: Datalogger/datalogger-autoterminate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.ok ${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.d" -o ${OBJECTDIR}/Datalogger/datalogger-autoterminate.o Datalogger/datalogger-autoterminate.c  
	
${OBJECTDIR}/Datalogger/datalogger-can.o: Datalogger/datalogger-can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-can.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-can.o.ok ${OBJECTDIR}/Datalogger/datalogger-can.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-can.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-can.o.d" -o ${OBJECTDIR}/Datalogger/datalogger-can.o Datalogger/datalogger-can.c  
	
${OBJECTDIR}/Datalogger/datalogger-file.o: Datalogger/datalogger-file.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-file.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-file.o.ok ${OBJECTDIR}/Datalogger/datalogger-file.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-file.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-file.o.d" -o ${OBJECTDIR}/Datalogger/datalogger-file.o Datalogger/datalogger-file.c  
	
${OBJECTDIR}/Datalogger/datalogger-perflogger.o: Datalogger/datalogger-perflogger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-perflogger.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-perflogger.o.ok ${OBJECTDIR}/Datalogger/datalogger-perflogger.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-perflogger.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-perflogger.o.d" -o ${OBJECTDIR}/Datalogger/datalogger-perflogger.o Datalogger/datalogger-perflogger.c  
	
${OBJECTDIR}/Datalogger/datalogger-stringutil.o: Datalogger/datalogger-stringutil.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-stringutil.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-stringutil.o.ok ${OBJECTDIR}/Datalogger/datalogger-stringutil.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-stringutil.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-stringutil.o.d" -o ${OBJECTDIR}/Datalogger/datalogger-stringutil.o Datalogger/datalogger-stringutil.c  
	
${OBJECTDIR}/Datalogger/datalogger.o: Datalogger/datalogger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger.o.ok ${OBJECTDIR}/Datalogger/datalogger.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger.o.d" -o ${OBJECTDIR}/Datalogger/datalogger.o Datalogger/datalogger.c  
	
${OBJECTDIR}/Datalogger/datalogger-accelerometer.o: Datalogger/datalogger-accelerometer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.ok ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.d" -o ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o Datalogger/datalogger-accelerometer.c  
	
${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o: Datalogger/datalogger-voltagelogger-run3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.ok ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.d" -o ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o Datalogger/datalogger-voltagelogger-run3.c  
	
${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o: Datalogger/datalogger-voltagelogger-datalogger-1-4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.ok ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.d" -o ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o Datalogger/datalogger-voltagelogger-datalogger-1-4.c  
	
${OBJECTDIR}/debug-common.o: debug-common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/debug-common.o.d 
	@${RM} ${OBJECTDIR}/debug-common.o.ok ${OBJECTDIR}/debug-common.o.err 
	@${FIXDEPS} "${OBJECTDIR}/debug-common.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/debug-common.o.d" -o ${OBJECTDIR}/debug-common.o debug-common.c  
	
${OBJECTDIR}/debug-log.o: debug-log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/debug-log.o.d 
	@${RM} ${OBJECTDIR}/debug-log.o.ok ${OBJECTDIR}/debug-log.o.err 
	@${FIXDEPS} "${OBJECTDIR}/debug-log.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/debug-log.o.d" -o ${OBJECTDIR}/debug-log.o debug-log.c  
	
${OBJECTDIR}/uart-dma.o: uart-dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/uart-dma.o.d 
	@${RM} ${OBJECTDIR}/uart-dma.o.ok ${OBJECTDIR}/uart-dma.o.err 
	@${FIXDEPS} "${OBJECTDIR}/uart-dma.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/uart-dma.o.d" -o ${OBJECTDIR}/uart-dma.o uart-dma.c  
	
${OBJECTDIR}/ecan.o: ecan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ecan.o.d 
	@${RM} ${OBJECTDIR}/ecan.o.ok ${OBJECTDIR}/ecan.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ecan.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/ecan.o.d" -o ${OBJECTDIR}/ecan.o ecan.c  
	
${OBJECTDIR}/FAT32/fat32-file-create.o: FAT32/fat32-file-create.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-create.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-create.o.ok ${OBJECTDIR}/FAT32/fat32-file-create.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-file-create.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/FAT32/fat32-file-create.o.d" -o ${OBJECTDIR}/FAT32/fat32-file-create.o FAT32/fat32-file-create.c  
	
${OBJECTDIR}/FAT32/fat32-file-tasks.o: FAT32/fat32-file-tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-tasks.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-tasks.o.ok ${OBJECTDIR}/FAT32/fat32-file-tasks.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-file-tasks.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/FAT32/fat32-file-tasks.o.d" -o ${OBJECTDIR}/FAT32/fat32-file-tasks.o FAT32/fat32-file-tasks.c  
	
${OBJECTDIR}/FAT32/fat32-file-util.o: FAT32/fat32-file-util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-util.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-util.o.ok ${OBJECTDIR}/FAT32/fat32-file-util.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-file-util.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/FAT32/fat32-file-util.o.d" -o ${OBJECTDIR}/FAT32/fat32-file-util.o FAT32/fat32-file-util.c  
	
${OBJECTDIR}/FAT32/fat32-file-write.o: FAT32/fat32-file-write.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-write.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-write.o.ok ${OBJECTDIR}/FAT32/fat32-file-write.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-file-write.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/FAT32/fat32-file-write.o.d" -o ${OBJECTDIR}/FAT32/fat32-file-write.o FAT32/fat32-file-write.c  
	
${OBJECTDIR}/FAT32/fat32-init.o: FAT32/fat32-init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-init.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-init.o.ok ${OBJECTDIR}/FAT32/fat32-init.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-init.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/FAT32/fat32-init.o.d" -o ${OBJECTDIR}/FAT32/fat32-init.o FAT32/fat32-init.c  
	
${OBJECTDIR}/FAT32/fat32-util.o: FAT32/fat32-util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-util.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-util.o.ok ${OBJECTDIR}/FAT32/fat32-util.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-util.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/FAT32/fat32-util.o.d" -o ${OBJECTDIR}/FAT32/fat32-util.o FAT32/fat32-util.c  
	
${OBJECTDIR}/Hardware/board-run3.o: Hardware/board-run3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Hardware 
	@${RM} ${OBJECTDIR}/Hardware/board-run3.o.d 
	@${RM} ${OBJECTDIR}/Hardware/board-run3.o.ok ${OBJECTDIR}/Hardware/board-run3.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Hardware/board-run3.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Hardware/board-run3.o.d" -o ${OBJECTDIR}/Hardware/board-run3.o Hardware/board-run3.c  
	
${OBJECTDIR}/Hardware/board-datalogger-1-4.o: Hardware/board-datalogger-1-4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Hardware 
	@${RM} ${OBJECTDIR}/Hardware/board-datalogger-1-4.o.d 
	@${RM} ${OBJECTDIR}/Hardware/board-datalogger-1-4.o.ok ${OBJECTDIR}/Hardware/board-datalogger-1-4.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Hardware/board-datalogger-1-4.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/Hardware/board-datalogger-1-4.o.d" -o ${OBJECTDIR}/Hardware/board-datalogger-1-4.o Hardware/board-datalogger-1-4.c  
	
${OBJECTDIR}/I2CDevices/i2c-hardware.o: I2CDevices/i2c-hardware.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/I2CDevices 
	@${RM} ${OBJECTDIR}/I2CDevices/i2c-hardware.o.d 
	@${RM} ${OBJECTDIR}/I2CDevices/i2c-hardware.o.ok ${OBJECTDIR}/I2CDevices/i2c-hardware.o.err 
	@${FIXDEPS} "${OBJECTDIR}/I2CDevices/i2c-hardware.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/I2CDevices/i2c-hardware.o.d" -o ${OBJECTDIR}/I2CDevices/i2c-hardware.o I2CDevices/i2c-hardware.c  
	
${OBJECTDIR}/I2CDevices/mcp23018.o: I2CDevices/mcp23018.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/I2CDevices 
	@${RM} ${OBJECTDIR}/I2CDevices/mcp23018.o.d 
	@${RM} ${OBJECTDIR}/I2CDevices/mcp23018.o.ok ${OBJECTDIR}/I2CDevices/mcp23018.o.err 
	@${FIXDEPS} "${OBJECTDIR}/I2CDevices/mcp23018.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/I2CDevices/mcp23018.o.d" -o ${OBJECTDIR}/I2CDevices/mcp23018.o I2CDevices/mcp23018.c  
	
${OBJECTDIR}/I2CDevices/pcf8523.o: I2CDevices/pcf8523.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/I2CDevices 
	@${RM} ${OBJECTDIR}/I2CDevices/pcf8523.o.d 
	@${RM} ${OBJECTDIR}/I2CDevices/pcf8523.o.ok ${OBJECTDIR}/I2CDevices/pcf8523.o.err 
	@${FIXDEPS} "${OBJECTDIR}/I2CDevices/pcf8523.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/I2CDevices/pcf8523.o.d" -o ${OBJECTDIR}/I2CDevices/pcf8523.o I2CDevices/pcf8523.c  
	
${OBJECTDIR}/I2CDevices/lis331.o: I2CDevices/lis331.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/I2CDevices 
	@${RM} ${OBJECTDIR}/I2CDevices/lis331.o.d 
	@${RM} ${OBJECTDIR}/I2CDevices/lis331.o.ok ${OBJECTDIR}/I2CDevices/lis331.o.err 
	@${FIXDEPS} "${OBJECTDIR}/I2CDevices/lis331.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/I2CDevices/lis331.o.d" -o ${OBJECTDIR}/I2CDevices/lis331.o I2CDevices/lis331.c  
	
${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o: SD-SPI-DMA/sd-dma-multipleblockwrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.ok ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.err 
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.d" -o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o SD-SPI-DMA/sd-dma-multipleblockwrite.c  
	
${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o: SD-SPI-DMA/sd-dma-singleblockread.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.ok ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.err 
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.d" -o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o SD-SPI-DMA/sd-dma-singleblockread.c  
	
${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o: SD-SPI-DMA/sd-dma-singleblockwrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.ok ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.err 
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.d" -o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o SD-SPI-DMA/sd-dma-singleblockwrite.c  
	
${OBJECTDIR}/SD-SPI-DMA/sd-events.o: SD-SPI-DMA/sd-events.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-events.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-events.o.ok ${OBJECTDIR}/SD-SPI-DMA/sd-events.o.err 
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-events.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-events.o.d" -o ${OBJECTDIR}/SD-SPI-DMA/sd-events.o SD-SPI-DMA/sd-events.c  
	
${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o: SD-SPI-DMA/sd-hardware.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.ok ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.err 
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.d" -o ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o SD-SPI-DMA/sd-hardware.c  
	
${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o: SD-SPI-DMA/sd-initialize.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.ok ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.err 
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.d" -o ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o SD-SPI-DMA/sd-initialize.c  
	
${OBJECTDIR}/timing-run2.o: timing-run2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timing-run2.o.d 
	@${RM} ${OBJECTDIR}/timing-run2.o.ok ${OBJECTDIR}/timing-run2.o.err 
	@${FIXDEPS} "${OBJECTDIR}/timing-run2.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/timing-run2.o.d" -o ${OBJECTDIR}/timing-run2.o timing-run2.c  
	
${OBJECTDIR}/timing-run3.o: timing-run3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timing-run3.o.d 
	@${RM} ${OBJECTDIR}/timing-run3.o.ok ${OBJECTDIR}/timing-run3.o.err 
	@${FIXDEPS} "${OBJECTDIR}/timing-run3.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/timing-run3.o.d" -o ${OBJECTDIR}/timing-run3.o timing-run3.c  
	
${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o: UserInterface/datalogger-ui-hardware-canbridge.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/UserInterface 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.d 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.ok ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.err 
	@${FIXDEPS} "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.d" -o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o UserInterface/datalogger-ui-hardware-canbridge.c  
	
${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o: UserInterface/datalogger-ui-hardware-run3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/UserInterface 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.d 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.ok ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.err 
	@${FIXDEPS} "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.d" -o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o UserInterface/datalogger-ui-hardware-run3.c  
	
${OBJECTDIR}/UserInterface/datalogger-ui-leds.o: UserInterface/datalogger-ui-leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/UserInterface 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.d 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.ok ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.err 
	@${FIXDEPS} "${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.d" -o ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o UserInterface/datalogger-ui-leds.c  
	
${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o: UserInterface/datalogger-ui-hardware-datalogger-1-4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/UserInterface 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.d 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.ok ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.err 
	@${FIXDEPS} "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.d" -o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o UserInterface/datalogger-ui-hardware-datalogger-1-4.c  
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o.ok ${OBJECTDIR}/main.o.err 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c  
	
${OBJECTDIR}/configuration_bits.o: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/configuration_bits.o.d 
	@${RM} ${OBJECTDIR}/configuration_bits.o.ok ${OBJECTDIR}/configuration_bits.o.err 
	@${FIXDEPS} "${OBJECTDIR}/configuration_bits.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DHARDWARE_CANBRIDGE -DDEBUG_UART_DISABLE -MMD -MF "${OBJECTDIR}/configuration_bits.o.d" -o ${OBJECTDIR}/configuration_bits.o configuration_bits.c  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/calsol-datalogger-pic24h.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/calsol-datalogger-pic24h.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1,--heap=0,--stack=0,--no-check-sections$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/calsol-datalogger-pic24h.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/calsol-datalogger-pic24h.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1,--heap=0,--stack=0,--no-check-sections$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/calsol-datalogger-pic24h.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/CanBridge_Production
	${RM} -r dist/CanBridge_Production

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
