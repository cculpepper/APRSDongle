/*********************************************************************/
/* Lab Exercise Eleven header file                                   */
/* Tests mixed C and assembly language programming to add 96-bit     */
/* unsigned numbers.  Prompts user to enter two numbers in hex       */
/* format to add, computes the result, and prints it.                */
/* Name:  R. W. Melton                                               */
/* Date:  April 20, 2015                                             */
/* Class:  CMPE 250                                                  */
/*  Sectio  All sections                                            */
/*********************************************************************/
typedef int Int32;
typedef unsigned int UInt32;
typedef char Int8;
typedef unsigned char UInt8;

typedef union {
	UInt32 Word[3];
	UInt8  Byte[12];
} UInt96;

/* assembly language subroutines */
int AddIntMultiU (UInt32 *Sum, UInt32 *Augend, UInt32 *Addend, 
		                  int NumWords);
void GetString (char String[]);
void PutString (char String[]);
void SerialDriverInit (void);
void Startup (void);

/* C subroutines */
int GetHexIntMulti (UInt32 *Number, int NumWords);
void PutHexIntMulti (UInt32 *Number, int NumWords);
int main (void);
int Reset_Handler (void) __attribute__((alias("main")));

