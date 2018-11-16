/*******************************************************************
*                                                                  *
* This file is a generic include file controlled by                *
* compiler/assembler IDE generated defines                         *
*                                                                  *
*******************************************************************/

#ifndef __esp32
#define __esp32


#define __ESP32DOITDEVKITV1__

/*
 * We arrive here after the bootloader finished loading the program from flash. The hardware is mostly uninitialized,
 * and the app CPU is in reset. We do have a stack, so we can do the initialization in C.
 */


//#include "cpu_startup.h"

#if defined (__ESP32DOITDEVKITV1__)
#include "esp32doitdevkitv1.h"

#elif defined (__MSP430C111__)
#include "msp430c111.h"

#elif defined (__MSP430C1111__)
#include "msp430c1111.h"


/********************************************************************
 *  msp430 generic
 ********************************************************************/
#elif defined (__MSP430GENERIC__)
#error "msp430 generic device does not have a default include file"

#elif defined (__MSP430XGENERIC__)
#error "msp430X generic device does not have a default include file"


/********************************************************************
 *
 ********************************************************************/
#else
#error "Failed to match a default include file"
#endif

#endif /* #ifndef __msp430 */


