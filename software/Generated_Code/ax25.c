
#include "WAIT1.h"
#include "DA1.h"
#include "ax25.h"
#include "TI1.h"
#include "LED1.h"
#ifdef __cplusplus
extern "C" {
#endif 
/*#define CLOCKRATE 48000000*/
/*#define AX25FUDGECYCLES 10000  [>Just a number of cycles to fudge the delay closer<] */
/*#define AX25MARKFREQ 1200*/
/*[>#define AX25MARKDELAYNS (( 1/ AX25MARKFREQ )*( 1/AX25SINDATALENGTH )*1000000000)<]*/
/*#define AX25MARKDELAY 167*/
/*[>#define AX25MARKDELAY ( CLOCKRATE * (1 / AX25MARKFREQ) * ( 1 / AX25SINDATALENGTH ) - AX25FUDGECYCLES)<]*/
/*#define AX25SPACEFREQ 2200*/
/*#define AX25SPACEDELAY 60*/
/*[>#define AX25SPACEDELAYNS (( 1/ AX25SPACEFREQ )*( 1/AX25SINDATALENGTH )*1000000000)<]*/
/*[>#define AX25SPACEDELAY ( CLOCKRATE * (1 / AX25SPACEFREQ) * ( 1 / AX25SINDATALENGTH ) - AX25FUDGECYCLES)<]*/
/*#define AX25MARKSINSEGMENTS 64000 [> Number of sin segments before changing tones<] */
/*#define AX25SPACESINSEGMENTS 117000*/
/*[>#define AX25MARKSINSEGMENTS 64 [> Number of sin segments before changing tones<] <]*/
/*[>#define AX25SPACESINSEGMENTS 117<]*/
/*[>#define AX25MARKDELAY 625<]*/
/*[>#define AX25MARKDELAY 3255<]*/
/*[>#define AX25SPACEDELAY 340<]*/
/*[>#define AX25SPACEDELAY 1775<]*/

/*volatile char 	ax25CurrBit; //the index of the current bit.*/
/*volatile char*	ax25DataPtr; //points to the current byte*/
/*volatile int 		ax25ToneDelay; //ns delay between tone changes. 1775 for the space and 3255 for mark*/
/*volatile int 		cycleDelay;		//Numbers of cycles left to delay*/
void ax25StartSinTimer(void);
void ax25StartToneTimer(void);
void ax25StopTimer(void);
const short ax25SinData[AX25SINDATALENGTH] = {
	2248u,
	2447u,
	2642u,
	2831u,
	3013u,
	3185u,
	3347u,
	3496u,
	3631u,
	3750u,
	3854u,
	3940u,
	4007u,
	4056u,
	4086u,
	4094u,
	4086u,
	4056u,
	4007u,
	3940u,
	3854u,
	3750u,
	3631u,
	3496u,
	3347u,
	3185u,
	3013u,
	2831u,
	2642u,
	2447u,
	2248u,
	2048u,
	1847u,
	1648u,
	1453u,
	1264u,
	1082u,
	910u,
	748u,
	599u,
	464u,
	345u,
	241u,
	155u,
	88u,
	39u,
	9u,
	0u,
	9u,
	39u,
	88u,
	155u,
	241u,
	345u,
	464u,
	599u,
	748u,
	910u,
	1082u,
	1264u,
	1453u,
	1648u,
	1847u,
	2048u};

LDD_TDeviceData* ax25DacPtr;
volatile int ax25BytesLeft;
volatile char* ax25DataPtr;
volatile int ax25SinIndex;
volatile signed char ax25CurrBit;
volatile char ax25Padding;
volatile char ax25CRC; /* Not sure about this*/ 
volatile signed char ax25CurrByte;
volatile char ax25Sending;
volatile uint32_t ax25CurrDelay;  /* Ticks of a 24 MHz clock we are currently delaying.  */ 
volatile char ax25OnesCount;
void ax25Enable_irq (int irq)                                                                                                                                                                       
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
void ax25Disable_irq (int irq)
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
/*char ax25SendNoInt(char* data, int len, LDD_TDeviceData* ax25DacPtr){*/
	/*//sends stuff...*/
	/*int sinIndex;*/
	/*unsigned short sinIndexChange; // The number of sin indices left until a change. Janky as shit. */
	/*int delayFudgeCycles; // Number of cycles to remove from the current delay. */
	/*unsigned char oneCount;*/
	/*oneCount = 0;  [> This is for bitstuffing<] */
	/*[>LED1_On();<]*/
	/*delayFudgeCycles = 0;*/
	/*sinIndexChange = AX25SPACESINSEGMENTS;*/
	/*ax25CurrBit = 7;*/
	/*ax25DataPtr = data;*/
	/*ax25ToneDelay = AX25SPACEDELAY; //Dont know if this is right.;*/
	/*sinIndex = 0;*/
	/*DA1_SetValue(ax25DacPtr, SinusOutputData[sinIndex]);*/
	
	/*while ((data+len) > ax25DataPtr){*/
		/*DA1_SetValue(ax25DacPtr, SinusOutputData[sinIndex]);*/
		/*WAIT1_WaitCycles(ax25ToneDelay-delayFudgeCycles);*/
		/*[>WAIT1_Waitns(2000);<]*/
		/*[>WAIT1_Waitns(abs(ax25ToneDelay-delayFudgeCycles));<]*/
		/*[>WAIT1_WaitCycles(60);<]*/
		/*[>WAIT1_WaitCycles(168);<]*/
		/*delayFudgeCycles = 0;*/
		/*sinIndex++;*/
		/*if (sinIndex >= AX25SINDATALENGTH){*/
			/*sinIndex = 0;*/
		/*}*/
		/*sinIndexChange--;*/
		/*if (sinIndexChange <=0){*/
			/*if((0x80 >> ax25CurrBit) & *ax25DataPtr){ */
				/*[> Then we have a 1<] */
				/*oneCount++;*/
				/*if (oneCount > 5){*/
					/*[> Stuff a bit<] */
					/*oneCount = 0;*/

					/*cwSend("Z",1,ax25DacPtr);*/
					/*if (ax25ToneDelay == AX25MARKDELAY){*/
						/*ax25ToneDelay = AX25SPACEDELAY;*/
						/*sinIndexChange = AX25SPACESINSEGMENTS;*/
						/*[>LED1_Off();<]*/
						/*[>cwSend("S",1,ax25DacPtr);<]*/
					/*} else {*/
						/*ax25ToneDelay = AX25MARKDELAY;*/
						/*sinIndexChange = AX25MARKSINSEGMENTS;*/
						/*[>LED1_On();<]*/
						/*[>cwSend("M",1,ax25DacPtr);<]*/
					/*} */

					
				/*} else {*/

					/*ax25CurrBit --;*/
					/*[>Go to the next bit, bit stuffing doesnt go to the next bit. <]*/
					/*cwSend("H",1,ax25DacPtr);*/
				/*}*/
				/*delayFudgeCycles +=8; // The above takes about 8 cycles..................*/
			/*} else {*/
				/*//We need to change the freq*/
				/*oneCount = 0;*/
				/*cwSend("S",1,ax25DacPtr);*/
				/*if (ax25ToneDelay == AX25MARKDELAY){*/
					/*ax25ToneDelay = AX25SPACEDELAY;*/
					/*sinIndexChange = AX25SPACESINSEGMENTS;*/
					/*[>LED1_Off();<]*/
				/*} else {*/
					/*ax25ToneDelay = AX25MARKDELAY;*/
					/*sinIndexChange = AX25MARKSINSEGMENTS;*/
					/*[>LED1_On();<]*/
				/*}*/
				/*delayFudgeCycles +=8; // The above takes about 8 cycles..................*/
				/*ax25CurrBit --;*/
			/*}*/
			/*if (ax25CurrBit == 0){*/
				/*//we need to inc the data ptr and set the currbit to 7*/
				/*ax25CurrBit = 7;*/
				/*ax25DataPtr++;*/
				/*[>cwSend(ax25DataPtr, 1, ax25DacPtr);<]*/
				/*delayFudgeCycles += 4;//The above takes about 4 cycles....*/
			/*}	*/
		/*}*/
	/*}*/
	/*[>LED1_Off();<]*/
	/*return 0;*/

/*}*/
char ax25GetSending(void){
	char locSend;
	locSend = ax25Sending;
	if (locSend + 1 == 1){
		return 0;
	} else {
		return 1;
	}
}
void ax25IntSend(char* dataPtr, int len, LDD_TDeviceData* dacPtr){
	volatile char *locSending;
	locSending = &ax25Sending;
	ax25DacPtr = dacPtr;
	ax25BytesLeft = len;
	ax25DataPtr = dataPtr;
	ax25SinIndex = 0;
	ax25CurrBit = 7;
	ax25Padding = 0;
	ax25CRC = 0;  /* TODO more here. No idea how this works...*/ 
	ax25CurrByte = 0x7E;  /* The flag */ 
	ax25Sending = 1;
	ax25OnesCount = 0;
	ax25CurrDelay = AX25SPACEDELAY;
	/* Now we need to set up the 1.2 KHz timer up for regular sending...*/ 
	ax25StartSinTimer();
	ax25StartToneTimer();
	/*while (ax25CurrByte == 0x7E){;}  [> Wait for the current byte to chonge.... Hacky. Sorry...<] */
	while (ax25CurrByte == 0x7E);  /*[> Wait for the current byte to chonge.... Hacky. Sorry...<] */
	ax25Padding = 1;
	/*ax25Sending = 1;*/

	while (ax25Sending && ax25BytesLeft > 0){
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
        __asm("nop");//printf("\nERR! Invalid IRQ value passed to enable irq function!\n");
		WAIT1_Waitms(100);
		if (ax25GetSending() == 0){
			break;
		}
	}
	PIT_LDVAL0 = 12000000; //This may fix the issues
	PIT_LDVAL1 = 12000000; //This may fix the issues
	ax25StopTimer();
	cwSend("AB1TJ", 5, dacPtr);
}

#define PIT_TIE 0x40000000
#define PIT_TEN 0x80000000
void ax25StartSinTimer(void){
/* No idea what to do here*/ 
	/* Note this uses the 24 MHz bus clock */ 
	PIT_MCR = 0; /* Enables the timer and allows the timer to stop in debug mode? Disables timer in debug. */ 
	PIT_LDVAL0 = ax25CurrDelay;   /* One second, for testing purpeses.  */ 
	/*PIT_TFLG0 = 0x00000001; [> clear the interrupt if one is pending.  <] */
	/*PIT_TCTRL0 = 0xC0000000*/

	/*PIT_MCR =  0x00; //PIT_MCR_FRZ_MASK; [> Enables the timer and allows the timer to stop in debug mode? Disables timer in debug. <] */
	/*PIT_LDVAL0 = 2400;   [> One second, for testing purpeses.  <] */
	PIT_TCTRL0 = PIT_TCTRL_TIE_MASK;
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
	ax25Enable_irq(INT_PIT - 16);
}
void ax25StartToneTimer(void){
	/* starts the timer to change the tone, 1200 times a second.  */ 

	PIT_MCR = 0; /* Enables the timer and allows the timer to stop in debug mode? Disables timer in debug. */ 
	PIT_LDVAL1 = 20000;  /* How many 24MHz ticks in 1200Hz.  */ 
	/*PIT_LDVAL1 = 12000000;//20000;  [> How many 24MHz ticks in 1200Hz.  <] */
	PIT_TCTRL1 = PIT_TCTRL_TIE_MASK;
	PIT_TCTRL1 |= PIT_TCTRL_TEN_MASK;
	/*PIT_TFLG1 = 0x00000001; [> clear the interrupt if one is pending.  <] */
	/*PIT_TCTRL0 = 0xC0000000*/
	ax25Enable_irq(INT_PIT - 16);
}
void ax25StopTimer(void){
	PIT_LDVAL0 = 12000000; //This may fix the issues
	PIT_LDVAL1 = 12000000; //This may fix the issues
	ax25Disable_irq(INT_PIT - 16);
	PIT_TCTRL1 &= ~PIT_TCTRL_TIE_MASK;
	PIT_TCTRL0 &= ~PIT_TCTRL_TIE_MASK;
	PIT_TCTRL1 &= ~PIT_TCTRL_TEN_MASK;
	PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	PIT_MCR = PIT_MCR_MDIS_MASK;
}

void ax25SwitchFreq(void){
	if (ax25CurrDelay == AX25MARKDELAY){
		ax25CurrDelay = AX25SPACEDELAY;
	} else {
		ax25CurrDelay = AX25MARKDELAY;
	}
}

void ax25ChangeBit(void){

	if ((0x80 >> ax25CurrBit) & ax25CurrByte){
		/*[> If a one, keep frequencies<] */
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
	if (ax25CurrBit <= 0){  /*We check after because its easier. If we need to increment the current byte*/
		/*then weve already sent it.  */
		/*[> Then we need to move onto the next thing<] */
		ax25BytesLeft--;
		ax25CurrByte = *ax25DataPtr;
		ax25DataPtr++;
		if (ax25BytesLeft <= 0){
			ax25Sending = 0;
			/*return;  [> Nothing left ta do<] */
		}
		ax25CurrBit = 7;
	} else {
		ax25CurrBit--;
	}
}

extern void ax25ChangeDac(void){
   /*Write your code here ... */
	/*ax25TimerIntHand();*/
	/*This is for the sin wave */
	DA1_SetValue(ax25DacPtr, ax25SinData[ax25SinIndex++]);
	if (ax25SinIndex >= AX25SINDATALENGTH){
		ax25SinIndex = 0;
	}
	PIT_LDVAL0 = ax25CurrDelay;
}

/*char ax25Send(char* data, int len, LDD_TDeviceData* ax25DacPtr){*/
	/*//sends stuff...*/
	/*int sinIndex;*/
	/*LDD_TError Error;*/
	/*ax25CurrBit = 7;*/
	/*ax25DataPtr = data;*/
	/*ax25ToneDelay = AX25MARKDELAY; //Dont know if this is right.;*/
	/*sinIndex = 0;*/
	/*Error = DA1_SetValue(ax25DacPtr, SinusOutputData[sinIndex]);*/
	/*ax25TimerInit();*/
	/*while ((data+len) > ax25DataPtr){*/
		/*Error = DA1_SetValue(ax25DacPtr, SinusOutputData[sinIndex]);*/
		/*cycleDelay = ax25ToneDelay;*/
		/*[>__asm volitile (<]*/
				/*[>ax25DelayLoop:<]*/
				/*[>add %[cycleDelay], %[cycleDelay], #-4<]*/
				/*[>cmp %[cycleDelay], 0<]*/
				/*[>[>bgt ax25DelayLoop<]<]*/
				/*[>);<]*/
		/*WAIT1_Waitns(ax25ToneDelay);*/
		/*sinIndex++;*/
		/*if (sinIndex >= AX25SINDATALENGTH){*/
			/*sinIndex = 0;*/
		/*}*/
	/*}*/
	/*return 0;*/
/*}*/
/*char ax25TimerIntHand(){*/
	/*char bitMask = 0;*/
	/*//bitMask = (0x80 >> ax25CurrBit);*/
	/*if(!((0x80 >> ax25CurrBit) & *ax25DataPtr)){ */
		/*//We need to change the freq*/
		/*if (ax25ToneDelay == AX25MARKDELAY){*/
			/*ax25ToneDelay = AX25SPACEDELAY;*/
		/*} else {*/
			/*ax25ToneDelay = AX25MARKDELAY;*/
		/*}*/
	/*}*/
	/*if (ax25CurrBit == 0){*/
		/*//we need to inc the data ptr and set the currbit to 7*/
		/*ax25CurrBit = 7;*/
		/*ax25DataPtr++;*/
	/*}	*/
	/*return 0;*/
/*}*/
/*char ax25TimerInit(){*/
	/*//need to set up the timer for 0.833333 ms. */
	/*TI1_Enable(TI1_DeviceData);*/
	/*return 1;*/
/*}*/
