/*********************************************************************/
/* Lab Exercise Eleven                                               */
/* Tests mixed C and assembly language programming to add 96-bit     */
/* unsigned numbers.  Prompts user to enter two numbers in hex       */
/* format to add, computes the result, and prints it.                */
/* Name:  R. W. Melton                                               */
/* Date:  April 20, 2015                                             */
/* Class:  CMPE 250                                                  */
/* Section:  All sections                                            */
/*********************************************************************/
#include "uart.h"

#define FALSE      (0)
#define TRUE       (1)
#define MAX_HEX_STRING ((sizeof(UInt96) << 1) + 1)
#define MAX_STRING (79)

int GetHexIntMulti (UInt32 *Number, int NumWords) {
/*********************************************************************/
/* Gets user string input of hex representation of an multiword      */
/* unsigned number of NumWords words, and converts it to a binary    */
/* unsigned NumWords-word number.                                    */
/* If user input is invalid, returns 1; otherwise returns 0.         */  
/* Calls:  GetString                                                 */
/*********************************************************************/
	char  *StringPtr;
	char  Digit;
	char  String[MAX_STRING];
	UInt8 *BytePtr;
	UInt8 ByteValue;
	int   NoError;  /* Used for index and error condition */
	/* Initialize *Number to 0 */
	for (NoError = 0; NoError < NumWords; NoError++) {
		((UInt96 *) Number)->Word[NoError] = (UInt32) 0;
	}

	GetString (String);

	/* Find end of string */
	NoError = 0;
	while (String[NoError] != 0) {
		NoError++;
	}
	if (NoError < MAX_HEX_STRING) {
		StringPtr = &(String[NoError]);
		NoError = TRUE;

		/* Convert each hex digit to binary */
		BytePtr = ((UInt96 *) Number)->Byte;
		ByteValue = (UInt8) 0;
		while (NoError && (StringPtr > String)) {
			/* Convert least significant digit of byte*/
			Digit = *(--StringPtr);
			/* Convert ASCII value to binary  value */
			if ((Digit >= '0') && (Digit <= '9')) {
				ByteValue =  (UInt8) (Digit - '0');
			}
			else if ((Digit >= 'A') && (Digit <= 'F')) {
				ByteValue =  (UInt8) (Digit - 'A' + (char) 10);
			}
			else if ((Digit >= 'a') && (Digit <= 'f')) {
				ByteValue =  (UInt8) (Digit - 'a' + (char) 10);
			}
			else {
				NoError = FALSE;
				ByteValue = (char) 0;
			}

			/* Convert most significant digit of byte */
			if (NoError && (StringPtr > String)) {
				Digit = *(--StringPtr);
				/* Convert ASCII value to binary  value */
				if ((Digit >= '0') && (Digit <= '9')) {
					Digit -= '0';
				}
				else if ((Digit >= 'A') && (Digit <= 'F')) {
					Digit = Digit - 'A' + (char) 10;
				}
				else if ((Digit >= 'a') && (Digit <= 'f')) {
					Digit = Digit - 'a' + (char) 10;
				}
				else {
					Digit = (char) 0;
					NoError = FALSE;
				}
			}
			else { /*no more digits typed */
				Digit = (char) 0;
			}
			/* Pack nibbles values into byte */
			*(BytePtr++) = ByteValue | (UInt8) (Digit << 4);
		} /* while */
	} /* if */
	else {
		/* String contains too many characters */
		NoError = FALSE;
	}

	/* complement of NoError is return result */
	return (NoError ^ 1);  
} /* GetHexIntMulti */

void PutHexIntMulti (UInt32 *Number, int NumWords) {
	/*********************************************************************/
	/* Prints hex representation of an unsigned multi-word number of     */
	/* NumWords words.                                                   */
	/* Calls:  PutString                                                 */
	/*********************************************************************/
	char *StringPtr;
	char Digit;
	char String[MAX_HEX_STRING];
	UInt8 *BytePtr;
	UInt8 ByteValue;

	StringPtr = String;
	BytePtr = &(((UInt96 *) Number)->Byte[NumWords << 2]);
	while (BytePtr > ((UInt96 *)Number)->Byte) {
		/* Get value of next byte */
		ByteValue = *(--BytePtr);
		/* Extract value of most significant nibble */
		Digit = (char) (ByteValue >> 4);
		/* Convert binary digit value to ASCII digit in string */
		if (Digit < 10) {
			*(StringPtr++) = Digit + '0';
		}
		else {
			*(StringPtr++) = Digit - (char) 10 + 'A';
		}
		/* Extract value of least significant nibble */
		ByteValue &= (UInt8) 0x0F;
		/* Convert binary digit value to ASCII digit in string */
		if (ByteValue < (UInt8) 10) {
			*(StringPtr++) = ((char) ByteValue) + '0';
		}
		else {
			*(StringPtr++) = ((char) ByteValue) - (char) 10 + 'A';
		}
	} /* while */

	/* Null-terminate string */
	*StringPtr = (char) 0;

	PutString (String);
} /* PutHexIntMulti */

int main (void) {
	int NotFinished = TRUE;
	UInt96 Addend,
		   Augend,
		   Sum;

	__asm("CPSID   I");  /* mask interrupts */
	Startup ();
	SerialDriverInit ();
	__asm("CPSIE   I");  /* unmask interrupts */

	while (NotFinished) {
		/* Get first number */
		PutString (" Enter first 96-bit hex number:  0x");
		while (GetHexIntMulti (Augend.Word, (96 >> 5))) {
			PutString ("Invalid number--try again:       0x");
		} /* while GetHexIntMulti */

		/* Get second number */
		PutString ("Enter 96-bit hex number to add:  0x");
		while (GetHexIntMulti (Addend.Word, (96 >> 5))) {
			PutString ("Invalid number--try again:       0x");
		} /* while GetHexIntMulti */

		/* Output sum */
		PutString ("                           Sum:  0x");
		if (AddIntMultiU (Sum.Word, Augend.Word, Addend.Word, (96 >> 5))) {
			PutString ("OVERFLOW\r\n");
		}
		else { /* result was valid */
			PutHexIntMulti (Sum.Word, (96 >> 5));
			PutString ("\r\n");
		}
	} /* while (NotFinished) */
	return (0);
} /* main */

