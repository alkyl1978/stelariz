//*****************************************************************************
//
// buttons.h - Prototypes for the evaluation board buttons driver.
//
// Copyright (c) 2012 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 9453 of the EK-LM4F120XL Firmware Package.
//
//*****************************************************************************

#ifndef __COMMANDS_H__
#define __COMMANDS_H__

//*****************************************************************************
//
// Defines for the command line argument parser provided as a standard part of 
// StellarisWare.  qs-rgb application uses the command line parser to extend
// functionality to the serial port.
//
//*****************************************************************************

#define CMDLINE_MAX_ARGS 3

//*****************************************************************************
//
// Declaration for the callback functions that will implement the command line
// functionality.  These functions get called by the command line interpreter
// when the corresponding command is typed into the command line.
//
//*****************************************************************************
extern int CMD_POZ_R0 (int argc, char **argv);
extern int CMD_help (int argc, char **argv);
extern int CMD_POZ_X (int argc, char **argv);
extern int CMD_POZ_Y (int argc, char **argv);
extern int CMD_POZ_Z (int argc, char **argv);
extern int CMD_R0 (int argc, char **argv);
extern int CMD_R1 (int argc, char **argv);
extern int CMD_R1_N (int argc, char **argv);
extern int CMD_R0_N (int argc, char **argv);
extern int CMD_STOP (int argc, char **argv);

#endif //__COMMANDS_H__
