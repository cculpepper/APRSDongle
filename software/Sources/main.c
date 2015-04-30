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
#include "uart.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "ax25.h"
#include "cw.h"
#define INITPTBPOW SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
#define PORTBLEDINIT(x) PORTB_PCR(X) = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
#define PORTBOUT(x) PORTB_PDDR(x) = (1<<(x));
#define PORTBTOGGLE(x) GPIOB_PTOR = (1<< (x));
// SBR = 24 MHz / (16 x 9600) = 156.25 --> 156
#define UART_BDH_9600 0
#define UART_BDL_9600 156
#define UART_C1_8N1 0x00
#define UART_C3_NO_TXINV 0x00
#define UART_C4_NO_DMA 0x00
#define UART_S2_NO_RXINV_BRK10_NO_LBKDETECT 0x00
#define UART_C2_T_R ( UART0_C2_TE_MASK | UART0_C2_RE_MASK)
#define UART_C2_T_RI (UART0_C2_RIE_MASK | UART_C2_T_R)
char initPCUart(void){
	/*Need to select PTB4 as a rxd pin for uart0*/
	 /* Thats ALT3, 0x3*/ 
	PORTB_PCR4 = PORT_PCR_MUX(3) || PORT_PCR_ISF_MASK;
	/*PORTB_PCR1 = PORT_PCR_MUX(2); Dont need TX for gps*/
/* Also need to disable the rxd for the other pins. I think?*/ 
	/*Might as well initialize the UART too. */
	SIM_SOPT5 = 0;
	UART0_BDH = UART_BDH_9600;
	UART0_BDL = UART_BDL_9600;
	UART0_C1 = UART_C1_8N1;
	UART0_C3 = UART_C3_NO_TXINV;
	UART0_C4 = UART_C4_NO_DMA;
	UART0_S2 = UART_S2_NO_RXINV_BRK10_NO_LBKDETECT;
	UART0_C2 = UART_C2_T_RI;
	SerialDriverInit();
}


#define PIT_TIE 0x40000000
#define PIT_TEN 0x80000000
static LDD_TError Error;
static LDD_TDeviceData *MyDacPtr;
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
void enable_irq (int irq)                                                                                                                                                                       
{   
    /* Make sure that the IRQ is an allowable number. Up to 32 is 
     * used.
     *
     * NOTE: If you are using the interrupt definitions from the header
     * file, you MUST SUBTRACT 16!!!
     */
    if (irq > 32) 
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
    else
    {   
      /* Set the ICPR and ISER registers accordingly */
      NVIC_ICPR |= 1 << (irq%32);
      NVIC_ISER |= 1 << (irq%32);
    }   
}
/***********************************************************************/
/*
 * Initialize the NVIC to disable the specified IRQ.
 * 
 * NOTE: The function only initializes the NVIC to disable a single IRQ. 
 * If you want to disable all interrupts, then use the DisableInterrupts
 * macro instead. 
 *
 * Parameters:
 * irq    irq number to be disabled (the irq number NOT the vector number)
 */

void disable_irq (int irq)
{
        
    /* Make sure that the IRQ is an allowable number. Right now up to 32 is 
     * used.
     *
     * NOTE: If you are using the interrupt definitions from the header
     * file, you MUST SUBTRACT 16!!!
     */
    if (irq > 32) 
        __asm("nop");
       // printf("\nERR! Invalid IRQ value passed to disable irq function!\n");
    else
      /* Set the ICER register accordingly */
      NVIC_ICER = 1 << (irq%32);
}
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
  /*LED1_On();*/
  SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;  /* Enable the PIT clock */
	/*PIT_MCR =  0x00; //PIT_MCR_FRZ_MASK; [> Enables the timer and allows the timer to stop in debug mode? Disables timer in debug. <] */
	/*PIT_LDVAL0 = 2400;   [> One second, for testing purpeses.  <] */
	/*[>PIT_TFLG0 = 0x00000001; [> clear the interrupt if one is pending.  <] <]*/
	/*PIT_TCTRL0 = PIT_TCTRL_TIE_MASK;*/
	/*PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;*/
	/*[>PIT_TCTRL0 = 0xC0000000;<]*/
	/*[>PIT_TCTRL0 |= PIT_TEN;<]*/
	/*enable_irq(INT_PIT - 16);*/
  initPCUart();
  for (;;){
	  PutChar('a');
  }

	dataptr = data;
	cwSend("FUCKYOUUUUUU",15, DA1_DeviceData);
	/*ax25IntSend(dataptr, 5, DA1_DeviceData);*/
	for (;;){

	//cwSend("FUCKYOUUUUUU",15, DA1_DeviceData);
		/*LED1_Neg();*/
			/*WAIT1_Waitms(2000);*/
ax25IntSend("WB4APR-14>APRS,RELAY*,WIDE::G3NRWVVVV:Hi Ian{001", 47,  DA1_DeviceData);
	/*ax25IntSend(dataptr, 5, DA1_DeviceData);*/
		//ax25IntSend("}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}a", 30,DA1_DeviceData);
	
	/*cwSend(dataptr, 5, DA1_DeviceData);*/
	/*ax25SendNoInt(dataptr, 5, DA1_DeviceData);*/
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

