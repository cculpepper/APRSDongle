/* ###################################################################
**     Filename    : main.c
**     Project     : kl05test
**     Processor   : MKL05Z32VLC4
**     Version     : Driver 01.01
**     Compiler    : Keil ARM C/C++ Compiler
**     Date/Time   : 2015-02-08, 14:24, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "WAIT1.h"
#include "DA1.h"
#include "TI1.h"
#include "TU1.h"
#include "CS1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "ax25.h"
#include "cw.h"

static LDD_TError Error;
static LDD_TDeviceData *MyDacPtr;
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  unsigned int i;
	char data[] = "AB1TJ";
	char* dataptr;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
	dataptr = data;
	cwSend(dataptr, 5, DA1_DeviceData);
	ax25SendNoInt(dataptr, 5, DA1_DeviceData);
	for (;;){

	ax25SendNoInt(dataptr, 5, DA1_DeviceData);
		ax25SendNoInt("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa", 30,DA1_DeviceData);
	
	ax25SendNoInt(dataptr, 5, DA1_DeviceData);
	}
  MyDacPtr = DA1_Init(NULL);                                            /* Initialization of DA1 component */
  for (;;) {
#if 1
	  /* Sawtooth */  
    for (i = 0; i < DATA_LENGTH; i++) {
      //Error = DA1_SetValue(MyDacPtr, OutputData[i]); /* Set converter output */
			WAIT1_Waitus(100);
    }
#else /* Sinus */  
    for (i = 0; i < SINUS_LENGTH; i++) {
    	//Error = DA1_SetValue(MyDacPtr, SinusOutputData[i]);
               /* Set converter output */
			WAIT1_Waitus(2);
    }
#endif
	//Error = DA1_SetValue(MyDacPtr,0x55555554);  //1.1 if Vin = 3.3 , 0.95 if Vin = 2.86
  //Error = DA1_SetValue(MyDacPtr,0xAAAAAAA8);  //2.2 if Vin = 3.3 , 1.9  if Vin = 2.86
  //Error = DA1_SetValue(MyDacPtr,0xFFFFFFFF);  //3.3 if Vin = 3.3 , 2.86 if Vin = 2.86
	//Error = DA1_SetValue(MyDacPtr,0xDFC6B699);  //2.5 if Vin = 2.86
  }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
