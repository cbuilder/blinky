#******************************************************************************
#
# Makefile - Rules for building the blinky example.
#
# Copyright (c) 2013-2016 Texas Instruments Incorporated.  All rights reserved.
# Software License Agreement
# 
# Texas Instruments (TI) is supplying this software for use solely and
# exclusively on TI's microcontroller products. The software is owned by
# TI and/or its suppliers, and is protected under applicable copyright
# laws. You may not combine this software with "viral" open-source
# software in order to form a larger program.
# 
# THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
# NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
# NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
# CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
# DAMAGES, FOR ANY REASON WHATSOEVER.
# 
# This is part of revision 2.1.3.156 of the EK-TM4C1294XL Firmware Package.
#
#******************************************************************************

#
# Defines the part type that this project uses.
#
PART=TM4C1294NCPDT

#
# The library directories
#
TIVAWARE=/home/dima/workspace/tiva/lib/tivaware
CMSIS=/home/dima/workspace/tiva/lib/CMSIS_5/CMSIS/Core/Include:\
/home/dima/workspace/tiva/lib/CMSIS_5/Device/ARM/ARMCM4/Include:\
/home/dima/workspace/tiva/lib

#
# Programmers and debuggers
#
FLASHER=/home/dima/workspace/tiva/tools/bin/lm4flash
OPENOCD=/home/dima/workspace/tiva/tools/bin/openocd
CFG=/home/dima/workspace/tiva/tools/openocd/tcl/board/ek-tm4c1294xl.cfg
GDB=/usr/bin/arm-none-eabi-gdb

#
# Include the common make definitions.
#
include ./makedefs

#
# Where to find header files that do not live in the source directory.
#
IPATH=$(TIVAWARE):$(CMSIS)

#
# The default rule, which causes the blinky example to be built.
#
all: ${COMPILER}
all: ${COMPILER}/blinky.axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~} openocd.log

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the blinky example.
#
${COMPILER}/blinky.axf: ${COMPILER}/blinky.o
${COMPILER}/blinky.axf: ${COMPILER}/task.o
${COMPILER}/blinky.axf: ${COMPILER}/ps1.o
${COMPILER}/blinky.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/blinky.axf: ${TIVAWARE}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/blinky.axf: blinky.ld
SCATTERgcc_blinky=blinky.ld
ENTRY_blinky=ResetISR
CFLAGSgcc=-DTARGET_IS_TM4C129_RA1 -ggdb

debug: flash
	${GDB} --symbols=./${COMPILER}/blinky.axf -ex 'target extended-remote | ${OPENOCD} -f ${CFG} -c "gdb_port pipe; log_output openocd.log"; monitor reset; monitor halt'

flash: all
	${FLASHER} ${COMPILER}/blinky.bin

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
