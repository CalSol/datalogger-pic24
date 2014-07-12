#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-Datalogger1.4_Development.mk)" "nbproject/Makefile-local-Datalogger1.4_Development.mk"
include nbproject/Makefile-local-Datalogger1.4_Development.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Datalogger1.4_Development
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/calsol-datalogger.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/calsol-datalogger.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Datalogger/datalogger-autoterminate.c Datalogger/datalogger-can.c Datalogger/datalogger-file.c Datalogger/datalogger-perflogger.c Datalogger/datalogger-stringutil.c Datalogger/datalogger.c Datalogger/datalogger-accelerometer.c Datalogger/datalogger-voltagelogger-run3.c Datalogger/datalogger-voltagelogger-datalogger-1-4.c debug-common.c debug-log.c uart-dma.c ecan.c FAT32/fat32-file-create.c FAT32/fat32-file-tasks.c FAT32/fat32-file-util.c FAT32/fat32-file-write.c FAT32/fat32-init.c FAT32/fat32-util.c ftm/ftm.c Hardware/board-run3.c Hardware/board-datalogger-1-4.c I2CDevices/i2c-hardware.c I2CDevices/mcp23018.c I2CDevices/pcf8523.c I2CDevices/lis331.c SD-SPI-DMA/sd-dma-multipleblockwrite.c SD-SPI-DMA/sd-dma-singleblockread.c SD-SPI-DMA/sd-dma-singleblockwrite.c SD-SPI-DMA/sd-events.c SD-SPI-DMA/sd-hardware.c SD-SPI-DMA/sd-initialize.c timing-run2.c timing-run3.c UserInterface/datalogger-ui-hardware-canbridge.c UserInterface/datalogger-ui-hardware-run3.c UserInterface/datalogger-ui-leds.c UserInterface/datalogger-ui-hardware-datalogger-1-4.c main.c configuration_bits.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Datalogger/datalogger-autoterminate.o ${OBJECTDIR}/Datalogger/datalogger-can.o ${OBJECTDIR}/Datalogger/datalogger-file.o ${OBJECTDIR}/Datalogger/datalogger-perflogger.o ${OBJECTDIR}/Datalogger/datalogger-stringutil.o ${OBJECTDIR}/Datalogger/datalogger.o ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o ${OBJECTDIR}/debug-common.o ${OBJECTDIR}/debug-log.o ${OBJECTDIR}/uart-dma.o ${OBJECTDIR}/ecan.o ${OBJECTDIR}/FAT32/fat32-file-create.o ${OBJECTDIR}/FAT32/fat32-file-tasks.o ${OBJECTDIR}/FAT32/fat32-file-util.o ${OBJECTDIR}/FAT32/fat32-file-write.o ${OBJECTDIR}/FAT32/fat32-init.o ${OBJECTDIR}/FAT32/fat32-util.o ${OBJECTDIR}/ftm/ftm.o ${OBJECTDIR}/Hardware/board-run3.o ${OBJECTDIR}/Hardware/board-datalogger-1-4.o ${OBJECTDIR}/I2CDevices/i2c-hardware.o ${OBJECTDIR}/I2CDevices/mcp23018.o ${OBJECTDIR}/I2CDevices/pcf8523.o ${OBJECTDIR}/I2CDevices/lis331.o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o ${OBJECTDIR}/SD-SPI-DMA/sd-events.o ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o ${OBJECTDIR}/timing-run2.o ${OBJECTDIR}/timing-run3.o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o ${OBJECTDIR}/main.o ${OBJECTDIR}/configuration_bits.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.d ${OBJECTDIR}/Datalogger/datalogger-can.o.d ${OBJECTDIR}/Datalogger/datalogger-file.o.d ${OBJECTDIR}/Datalogger/datalogger-perflogger.o.d ${OBJECTDIR}/Datalogger/datalogger-stringutil.o.d ${OBJECTDIR}/Datalogger/datalogger.o.d ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.d ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.d ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.d ${OBJECTDIR}/debug-common.o.d ${OBJECTDIR}/debug-log.o.d ${OBJECTDIR}/uart-dma.o.d ${OBJECTDIR}/ecan.o.d ${OBJECTDIR}/FAT32/fat32-file-create.o.d ${OBJECTDIR}/FAT32/fat32-file-tasks.o.d ${OBJECTDIR}/FAT32/fat32-file-util.o.d ${OBJECTDIR}/FAT32/fat32-file-write.o.d ${OBJECTDIR}/FAT32/fat32-init.o.d ${OBJECTDIR}/FAT32/fat32-util.o.d ${OBJECTDIR}/ftm/ftm.o.d ${OBJECTDIR}/Hardware/board-run3.o.d ${OBJECTDIR}/Hardware/board-datalogger-1-4.o.d ${OBJECTDIR}/I2CDevices/i2c-hardware.o.d ${OBJECTDIR}/I2CDevices/mcp23018.o.d ${OBJECTDIR}/I2CDevices/pcf8523.o.d ${OBJECTDIR}/I2CDevices/lis331.o.d ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.d ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.d ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.d ${OBJECTDIR}/SD-SPI-DMA/sd-events.o.d ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.d ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.d ${OBJECTDIR}/timing-run2.o.d ${OBJECTDIR}/timing-run3.o.d ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.d ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.d ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.d ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/configuration_bits.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Datalogger/datalogger-autoterminate.o ${OBJECTDIR}/Datalogger/datalogger-can.o ${OBJECTDIR}/Datalogger/datalogger-file.o ${OBJECTDIR}/Datalogger/datalogger-perflogger.o ${OBJECTDIR}/Datalogger/datalogger-stringutil.o ${OBJECTDIR}/Datalogger/datalogger.o ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o ${OBJECTDIR}/debug-common.o ${OBJECTDIR}/debug-log.o ${OBJECTDIR}/uart-dma.o ${OBJECTDIR}/ecan.o ${OBJECTDIR}/FAT32/fat32-file-create.o ${OBJECTDIR}/FAT32/fat32-file-tasks.o ${OBJECTDIR}/FAT32/fat32-file-util.o ${OBJECTDIR}/FAT32/fat32-file-write.o ${OBJECTDIR}/FAT32/fat32-init.o ${OBJECTDIR}/FAT32/fat32-util.o ${OBJECTDIR}/ftm/ftm.o ${OBJECTDIR}/Hardware/board-run3.o ${OBJECTDIR}/Hardware/board-datalogger-1-4.o ${OBJECTDIR}/I2CDevices/i2c-hardware.o ${OBJECTDIR}/I2CDevices/mcp23018.o ${OBJECTDIR}/I2CDevices/pcf8523.o ${OBJECTDIR}/I2CDevices/lis331.o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o ${OBJECTDIR}/SD-SPI-DMA/sd-events.o ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o ${OBJECTDIR}/timing-run2.o ${OBJECTDIR}/timing-run3.o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o ${OBJECTDIR}/main.o ${OBJECTDIR}/configuration_bits.o

# Source Files
SOURCEFILES=Datalogger/datalogger-autoterminate.c Datalogger/datalogger-can.c Datalogger/datalogger-file.c Datalogger/datalogger-perflogger.c Datalogger/datalogger-stringutil.c Datalogger/datalogger.c Datalogger/datalogger-accelerometer.c Datalogger/datalogger-voltagelogger-run3.c Datalogger/datalogger-voltagelogger-datalogger-1-4.c debug-common.c debug-log.c uart-dma.c ecan.c FAT32/fat32-file-create.c FAT32/fat32-file-tasks.c FAT32/fat32-file-util.c FAT32/fat32-file-write.c FAT32/fat32-init.c FAT32/fat32-util.c ftm/ftm.c Hardware/board-run3.c Hardware/board-datalogger-1-4.c I2CDevices/i2c-hardware.c I2CDevices/mcp23018.c I2CDevices/pcf8523.c I2CDevices/lis331.c SD-SPI-DMA/sd-dma-multipleblockwrite.c SD-SPI-DMA/sd-dma-singleblockread.c SD-SPI-DMA/sd-dma-singleblockwrite.c SD-SPI-DMA/sd-events.c SD-SPI-DMA/sd-hardware.c SD-SPI-DMA/sd-initialize.c timing-run2.c timing-run3.c UserInterface/datalogger-ui-hardware-canbridge.c UserInterface/datalogger-ui-hardware-run3.c UserInterface/datalogger-ui-leds.c UserInterface/datalogger-ui-hardware-datalogger-1-4.c main.c configuration_bits.c


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
	${MAKE}  -f nbproject/Makefile-Datalogger1.4_Development.mk dist/${CND_CONF}/${IMAGE_TYPE}/calsol-datalogger.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP256MU806
MP_LINKER_FILE_OPTION=,--script=p33EP256MU806.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Datalogger/datalogger-autoterminate.o: Datalogger/datalogger-autoterminate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-autoterminate.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger-autoterminate.c  -o ${OBJECTDIR}/Datalogger/datalogger-autoterminate.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Datalogger/datalogger-can.o: Datalogger/datalogger-can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-can.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-can.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger-can.c  -o ${OBJECTDIR}/Datalogger/datalogger-can.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-can.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-can.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Datalogger/datalogger-file.o: Datalogger/datalogger-file.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-file.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-file.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger-file.c  -o ${OBJECTDIR}/Datalogger/datalogger-file.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-file.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-file.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Datalogger/datalogger-perflogger.o: Datalogger/datalogger-perflogger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-perflogger.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-perflogger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger-perflogger.c  -o ${OBJECTDIR}/Datalogger/datalogger-perflogger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-perflogger.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-perflogger.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Datalogger/datalogger-stringutil.o: Datalogger/datalogger-stringutil.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-stringutil.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-stringutil.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger-stringutil.c  -o ${OBJECTDIR}/Datalogger/datalogger-stringutil.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-stringutil.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-stringutil.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Datalogger/datalogger.o: Datalogger/datalogger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger.c  -o ${OBJECTDIR}/Datalogger/datalogger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Datalogger/datalogger-accelerometer.o: Datalogger/datalogger-accelerometer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger-accelerometer.c  -o ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o: Datalogger/datalogger-voltagelogger-run3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger-voltagelogger-run3.c  -o ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o: Datalogger/datalogger-voltagelogger-datalogger-1-4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger-voltagelogger-datalogger-1-4.c  -o ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/debug-common.o: debug-common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/debug-common.o.d 
	@${RM} ${OBJECTDIR}/debug-common.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debug-common.c  -o ${OBJECTDIR}/debug-common.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/debug-common.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/debug-common.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/debug-log.o: debug-log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/debug-log.o.d 
	@${RM} ${OBJECTDIR}/debug-log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debug-log.c  -o ${OBJECTDIR}/debug-log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/debug-log.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/debug-log.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uart-dma.o: uart-dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/uart-dma.o.d 
	@${RM} ${OBJECTDIR}/uart-dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uart-dma.c  -o ${OBJECTDIR}/uart-dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uart-dma.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uart-dma.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ecan.o: ecan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ecan.o.d 
	@${RM} ${OBJECTDIR}/ecan.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ecan.c  -o ${OBJECTDIR}/ecan.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ecan.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/ecan.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FAT32/fat32-file-create.o: FAT32/fat32-file-create.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-create.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-create.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FAT32/fat32-file-create.c  -o ${OBJECTDIR}/FAT32/fat32-file-create.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FAT32/fat32-file-create.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-file-create.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FAT32/fat32-file-tasks.o: FAT32/fat32-file-tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-tasks.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-tasks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FAT32/fat32-file-tasks.c  -o ${OBJECTDIR}/FAT32/fat32-file-tasks.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FAT32/fat32-file-tasks.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-file-tasks.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FAT32/fat32-file-util.o: FAT32/fat32-file-util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-util.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-util.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FAT32/fat32-file-util.c  -o ${OBJECTDIR}/FAT32/fat32-file-util.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FAT32/fat32-file-util.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-file-util.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FAT32/fat32-file-write.o: FAT32/fat32-file-write.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-write.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-write.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FAT32/fat32-file-write.c  -o ${OBJECTDIR}/FAT32/fat32-file-write.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FAT32/fat32-file-write.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-file-write.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FAT32/fat32-init.o: FAT32/fat32-init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-init.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FAT32/fat32-init.c  -o ${OBJECTDIR}/FAT32/fat32-init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FAT32/fat32-init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FAT32/fat32-util.o: FAT32/fat32-util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-util.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-util.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FAT32/fat32-util.c  -o ${OBJECTDIR}/FAT32/fat32-util.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FAT32/fat32-util.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-util.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ftm/ftm.o: ftm/ftm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ftm 
	@${RM} ${OBJECTDIR}/ftm/ftm.o.d 
	@${RM} ${OBJECTDIR}/ftm/ftm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ftm/ftm.c  -o ${OBJECTDIR}/ftm/ftm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ftm/ftm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/ftm/ftm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Hardware/board-run3.o: Hardware/board-run3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Hardware 
	@${RM} ${OBJECTDIR}/Hardware/board-run3.o.d 
	@${RM} ${OBJECTDIR}/Hardware/board-run3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Hardware/board-run3.c  -o ${OBJECTDIR}/Hardware/board-run3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Hardware/board-run3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Hardware/board-run3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Hardware/board-datalogger-1-4.o: Hardware/board-datalogger-1-4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Hardware 
	@${RM} ${OBJECTDIR}/Hardware/board-datalogger-1-4.o.d 
	@${RM} ${OBJECTDIR}/Hardware/board-datalogger-1-4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Hardware/board-datalogger-1-4.c  -o ${OBJECTDIR}/Hardware/board-datalogger-1-4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Hardware/board-datalogger-1-4.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Hardware/board-datalogger-1-4.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/I2CDevices/i2c-hardware.o: I2CDevices/i2c-hardware.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/I2CDevices 
	@${RM} ${OBJECTDIR}/I2CDevices/i2c-hardware.o.d 
	@${RM} ${OBJECTDIR}/I2CDevices/i2c-hardware.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2CDevices/i2c-hardware.c  -o ${OBJECTDIR}/I2CDevices/i2c-hardware.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/I2CDevices/i2c-hardware.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/I2CDevices/i2c-hardware.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/I2CDevices/mcp23018.o: I2CDevices/mcp23018.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/I2CDevices 
	@${RM} ${OBJECTDIR}/I2CDevices/mcp23018.o.d 
	@${RM} ${OBJECTDIR}/I2CDevices/mcp23018.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2CDevices/mcp23018.c  -o ${OBJECTDIR}/I2CDevices/mcp23018.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/I2CDevices/mcp23018.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/I2CDevices/mcp23018.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/I2CDevices/pcf8523.o: I2CDevices/pcf8523.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/I2CDevices 
	@${RM} ${OBJECTDIR}/I2CDevices/pcf8523.o.d 
	@${RM} ${OBJECTDIR}/I2CDevices/pcf8523.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2CDevices/pcf8523.c  -o ${OBJECTDIR}/I2CDevices/pcf8523.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/I2CDevices/pcf8523.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/I2CDevices/pcf8523.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/I2CDevices/lis331.o: I2CDevices/lis331.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/I2CDevices 
	@${RM} ${OBJECTDIR}/I2CDevices/lis331.o.d 
	@${RM} ${OBJECTDIR}/I2CDevices/lis331.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2CDevices/lis331.c  -o ${OBJECTDIR}/I2CDevices/lis331.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/I2CDevices/lis331.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/I2CDevices/lis331.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o: SD-SPI-DMA/sd-dma-multipleblockwrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SD-SPI-DMA/sd-dma-multipleblockwrite.c  -o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o: SD-SPI-DMA/sd-dma-singleblockread.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SD-SPI-DMA/sd-dma-singleblockread.c  -o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o: SD-SPI-DMA/sd-dma-singleblockwrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SD-SPI-DMA/sd-dma-singleblockwrite.c  -o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/SD-SPI-DMA/sd-events.o: SD-SPI-DMA/sd-events.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-events.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SD-SPI-DMA/sd-events.c  -o ${OBJECTDIR}/SD-SPI-DMA/sd-events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-events.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-events.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o: SD-SPI-DMA/sd-hardware.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SD-SPI-DMA/sd-hardware.c  -o ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o: SD-SPI-DMA/sd-initialize.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SD-SPI-DMA/sd-initialize.c  -o ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/timing-run2.o: timing-run2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timing-run2.o.d 
	@${RM} ${OBJECTDIR}/timing-run2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timing-run2.c  -o ${OBJECTDIR}/timing-run2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/timing-run2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/timing-run2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/timing-run3.o: timing-run3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timing-run3.o.d 
	@${RM} ${OBJECTDIR}/timing-run3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timing-run3.c  -o ${OBJECTDIR}/timing-run3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/timing-run3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/timing-run3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o: UserInterface/datalogger-ui-hardware-canbridge.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/UserInterface 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.d 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UserInterface/datalogger-ui-hardware-canbridge.c  -o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o: UserInterface/datalogger-ui-hardware-run3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/UserInterface 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.d 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UserInterface/datalogger-ui-hardware-run3.c  -o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/UserInterface/datalogger-ui-leds.o: UserInterface/datalogger-ui-leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/UserInterface 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.d 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UserInterface/datalogger-ui-leds.c  -o ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o: UserInterface/datalogger-ui-hardware-datalogger-1-4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/UserInterface 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.d 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UserInterface/datalogger-ui-hardware-datalogger-1-4.c  -o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/configuration_bits.o: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/configuration_bits.o.d 
	@${RM} ${OBJECTDIR}/configuration_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  configuration_bits.c  -o ${OBJECTDIR}/configuration_bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/configuration_bits.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/configuration_bits.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/Datalogger/datalogger-autoterminate.o: Datalogger/datalogger-autoterminate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-autoterminate.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger-autoterminate.c  -o ${OBJECTDIR}/Datalogger/datalogger-autoterminate.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-autoterminate.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Datalogger/datalogger-can.o: Datalogger/datalogger-can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-can.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-can.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger-can.c  -o ${OBJECTDIR}/Datalogger/datalogger-can.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-can.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-can.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Datalogger/datalogger-file.o: Datalogger/datalogger-file.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-file.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-file.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger-file.c  -o ${OBJECTDIR}/Datalogger/datalogger-file.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-file.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-file.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Datalogger/datalogger-perflogger.o: Datalogger/datalogger-perflogger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-perflogger.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-perflogger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger-perflogger.c  -o ${OBJECTDIR}/Datalogger/datalogger-perflogger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-perflogger.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-perflogger.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Datalogger/datalogger-stringutil.o: Datalogger/datalogger-stringutil.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-stringutil.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-stringutil.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger-stringutil.c  -o ${OBJECTDIR}/Datalogger/datalogger-stringutil.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-stringutil.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-stringutil.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Datalogger/datalogger.o: Datalogger/datalogger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger.c  -o ${OBJECTDIR}/Datalogger/datalogger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Datalogger/datalogger-accelerometer.o: Datalogger/datalogger-accelerometer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger-accelerometer.c  -o ${OBJECTDIR}/Datalogger/datalogger-accelerometer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-accelerometer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o: Datalogger/datalogger-voltagelogger-run3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger-voltagelogger-run3.c  -o ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-voltagelogger-run3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o: Datalogger/datalogger-voltagelogger-datalogger-1-4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Datalogger 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.d 
	@${RM} ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Datalogger/datalogger-voltagelogger-datalogger-1-4.c  -o ${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Datalogger/datalogger-voltagelogger-datalogger-1-4.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/debug-common.o: debug-common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/debug-common.o.d 
	@${RM} ${OBJECTDIR}/debug-common.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debug-common.c  -o ${OBJECTDIR}/debug-common.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/debug-common.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/debug-common.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/debug-log.o: debug-log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/debug-log.o.d 
	@${RM} ${OBJECTDIR}/debug-log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debug-log.c  -o ${OBJECTDIR}/debug-log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/debug-log.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/debug-log.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uart-dma.o: uart-dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/uart-dma.o.d 
	@${RM} ${OBJECTDIR}/uart-dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uart-dma.c  -o ${OBJECTDIR}/uart-dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uart-dma.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uart-dma.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ecan.o: ecan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ecan.o.d 
	@${RM} ${OBJECTDIR}/ecan.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ecan.c  -o ${OBJECTDIR}/ecan.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ecan.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/ecan.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FAT32/fat32-file-create.o: FAT32/fat32-file-create.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-create.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-create.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FAT32/fat32-file-create.c  -o ${OBJECTDIR}/FAT32/fat32-file-create.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FAT32/fat32-file-create.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-file-create.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FAT32/fat32-file-tasks.o: FAT32/fat32-file-tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-tasks.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-tasks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FAT32/fat32-file-tasks.c  -o ${OBJECTDIR}/FAT32/fat32-file-tasks.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FAT32/fat32-file-tasks.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-file-tasks.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FAT32/fat32-file-util.o: FAT32/fat32-file-util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-util.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-util.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FAT32/fat32-file-util.c  -o ${OBJECTDIR}/FAT32/fat32-file-util.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FAT32/fat32-file-util.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-file-util.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FAT32/fat32-file-write.o: FAT32/fat32-file-write.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-write.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-file-write.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FAT32/fat32-file-write.c  -o ${OBJECTDIR}/FAT32/fat32-file-write.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FAT32/fat32-file-write.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-file-write.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FAT32/fat32-init.o: FAT32/fat32-init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-init.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FAT32/fat32-init.c  -o ${OBJECTDIR}/FAT32/fat32-init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FAT32/fat32-init.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FAT32/fat32-util.o: FAT32/fat32-util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FAT32 
	@${RM} ${OBJECTDIR}/FAT32/fat32-util.o.d 
	@${RM} ${OBJECTDIR}/FAT32/fat32-util.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FAT32/fat32-util.c  -o ${OBJECTDIR}/FAT32/fat32-util.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FAT32/fat32-util.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/FAT32/fat32-util.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ftm/ftm.o: ftm/ftm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ftm 
	@${RM} ${OBJECTDIR}/ftm/ftm.o.d 
	@${RM} ${OBJECTDIR}/ftm/ftm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ftm/ftm.c  -o ${OBJECTDIR}/ftm/ftm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ftm/ftm.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/ftm/ftm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Hardware/board-run3.o: Hardware/board-run3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Hardware 
	@${RM} ${OBJECTDIR}/Hardware/board-run3.o.d 
	@${RM} ${OBJECTDIR}/Hardware/board-run3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Hardware/board-run3.c  -o ${OBJECTDIR}/Hardware/board-run3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Hardware/board-run3.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Hardware/board-run3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Hardware/board-datalogger-1-4.o: Hardware/board-datalogger-1-4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Hardware 
	@${RM} ${OBJECTDIR}/Hardware/board-datalogger-1-4.o.d 
	@${RM} ${OBJECTDIR}/Hardware/board-datalogger-1-4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Hardware/board-datalogger-1-4.c  -o ${OBJECTDIR}/Hardware/board-datalogger-1-4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Hardware/board-datalogger-1-4.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Hardware/board-datalogger-1-4.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/I2CDevices/i2c-hardware.o: I2CDevices/i2c-hardware.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/I2CDevices 
	@${RM} ${OBJECTDIR}/I2CDevices/i2c-hardware.o.d 
	@${RM} ${OBJECTDIR}/I2CDevices/i2c-hardware.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2CDevices/i2c-hardware.c  -o ${OBJECTDIR}/I2CDevices/i2c-hardware.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/I2CDevices/i2c-hardware.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/I2CDevices/i2c-hardware.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/I2CDevices/mcp23018.o: I2CDevices/mcp23018.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/I2CDevices 
	@${RM} ${OBJECTDIR}/I2CDevices/mcp23018.o.d 
	@${RM} ${OBJECTDIR}/I2CDevices/mcp23018.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2CDevices/mcp23018.c  -o ${OBJECTDIR}/I2CDevices/mcp23018.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/I2CDevices/mcp23018.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/I2CDevices/mcp23018.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/I2CDevices/pcf8523.o: I2CDevices/pcf8523.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/I2CDevices 
	@${RM} ${OBJECTDIR}/I2CDevices/pcf8523.o.d 
	@${RM} ${OBJECTDIR}/I2CDevices/pcf8523.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2CDevices/pcf8523.c  -o ${OBJECTDIR}/I2CDevices/pcf8523.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/I2CDevices/pcf8523.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/I2CDevices/pcf8523.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/I2CDevices/lis331.o: I2CDevices/lis331.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/I2CDevices 
	@${RM} ${OBJECTDIR}/I2CDevices/lis331.o.d 
	@${RM} ${OBJECTDIR}/I2CDevices/lis331.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2CDevices/lis331.c  -o ${OBJECTDIR}/I2CDevices/lis331.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/I2CDevices/lis331.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/I2CDevices/lis331.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o: SD-SPI-DMA/sd-dma-multipleblockwrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SD-SPI-DMA/sd-dma-multipleblockwrite.c  -o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-dma-multipleblockwrite.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o: SD-SPI-DMA/sd-dma-singleblockread.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SD-SPI-DMA/sd-dma-singleblockread.c  -o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockread.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o: SD-SPI-DMA/sd-dma-singleblockwrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SD-SPI-DMA/sd-dma-singleblockwrite.c  -o ${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-dma-singleblockwrite.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/SD-SPI-DMA/sd-events.o: SD-SPI-DMA/sd-events.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-events.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SD-SPI-DMA/sd-events.c  -o ${OBJECTDIR}/SD-SPI-DMA/sd-events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-events.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-events.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o: SD-SPI-DMA/sd-hardware.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SD-SPI-DMA/sd-hardware.c  -o ${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-hardware.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o: SD-SPI-DMA/sd-initialize.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/SD-SPI-DMA 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SD-SPI-DMA/sd-initialize.c  -o ${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI-DMA/sd-initialize.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/timing-run2.o: timing-run2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timing-run2.o.d 
	@${RM} ${OBJECTDIR}/timing-run2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timing-run2.c  -o ${OBJECTDIR}/timing-run2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/timing-run2.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/timing-run2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/timing-run3.o: timing-run3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timing-run3.o.d 
	@${RM} ${OBJECTDIR}/timing-run3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timing-run3.c  -o ${OBJECTDIR}/timing-run3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/timing-run3.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/timing-run3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o: UserInterface/datalogger-ui-hardware-canbridge.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/UserInterface 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.d 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UserInterface/datalogger-ui-hardware-canbridge.c  -o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-canbridge.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o: UserInterface/datalogger-ui-hardware-run3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/UserInterface 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.d 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UserInterface/datalogger-ui-hardware-run3.c  -o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-run3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/UserInterface/datalogger-ui-leds.o: UserInterface/datalogger-ui-leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/UserInterface 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.d 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UserInterface/datalogger-ui-leds.c  -o ${OBJECTDIR}/UserInterface/datalogger-ui-leds.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/UserInterface/datalogger-ui-leds.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o: UserInterface/datalogger-ui-hardware-datalogger-1-4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/UserInterface 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.d 
	@${RM} ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UserInterface/datalogger-ui-hardware-datalogger-1-4.c  -o ${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/UserInterface/datalogger-ui-hardware-datalogger-1-4.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/configuration_bits.o: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/configuration_bits.o.d 
	@${RM} ${OBJECTDIR}/configuration_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  configuration_bits.c  -o ${OBJECTDIR}/configuration_bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/configuration_bits.o.d"        -g -omf=elf -fno-short-double -O3 -DHARDWARE_DATALOGGER_1_4 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/configuration_bits.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/calsol-datalogger.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/calsol-datalogger.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--heap=2048,--stack=512,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/calsol-datalogger.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/calsol-datalogger.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=2048,--stack=512,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/calsol-datalogger.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Datalogger1.4_Development
	${RM} -r dist/Datalogger1.4_Development

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
