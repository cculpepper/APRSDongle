/* ###################################################################
**     Filename    : Events.c
**     Project     : kl05test
**     Processor   : MKL05Z32VLC4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : Keil ARM C/C++ Compiler
**     Date/Time   : 2015-02-08, 14:24, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

#include "ax25.h"
/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL05Z32LF4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  TI1InterruptHand (module Events)
**
**     Component   :  TI1 [TimerInt_LDD]
*/
/*!
**     @brief
**         Called if periodic event occur. Component and OnInterrupt
**         event must be enabled. See [SetEventMask] and [GetEventMask]
**         methods. This event is available only if a [Interrupt
**         service/event] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TI3InterruptHand(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	/*ax25TimerIntHand();*/
	 /* This is for the sin wave*/ 
	if (ax25Sending){
		DA1_SetValue(ax25GlobalDacPtr, ax25SinData[ax25SinIndex++]);
		if (ax25SinIndex >= AX25SINDATALENGTH){
			ax25SinIndex = 0;
		}
	}

}

void TI2InterruptHand(LDD_TUserData *UserDataPtr){
	if (ax25Sending){
		if ((0x80 >> ax25CurrBit) & ax25CurrByte){
			/* If a one, keep frequencies*/ 
			if (ax25Padding){
				ax25OnesCount++;
				if (ax25OnesCount > 5){
					ax25SwitchFreq();
					ax25OnesCount = 0;
				}
			} 
		} else {
			ax25OnesCount = 0;
			ax25SwitchFreq();
		}
		if (ax25CurrBit <= 0){ /* We check after because its easier. If the current bit is a 0
		then weve already sent it. */ 
			/* Then we need to move onto the next thing*/ 
			ax25BytesLeft--;
			ax25DataPtr++;
			if (ax25BytesLeft < 0){
				ax25Sending = 0;
				return;  /* Nothing left ta do*/ 
			}
			ax25CurrBit = 7;
		} else {
			ax25CurrBit--;
		}
	}
}

	
/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
