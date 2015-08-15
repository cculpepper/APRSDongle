            TTL CMPE 250 Lab Exercise Eleven
;****************************************************************
; Tests mixed C and assembly language programming to add 128-bit
; unsigned numbers.  Prompts user to enter two numbers in hex
; format to add, computes the result, and prints it.
;Name:  R. W. Melton
;Date:  April 20, 2015
;Class:  CMPE-250
;Section:  All sections
;---------------------------------------------------------------
;Keil Template for KL46
;R. W. Melton
;February 16, 2015
;****************************************************************
;Assembler directives
            THUMB
;---------------------------------------------------------------
            GBLL  MIXED_ASM_C
MIXED_ASM_C SETL   {TRUE}
;---------------------------------------------------------------
            OPT    64  ;Turn on listing macro expansions
;****************************************************************
;Include files
	;include MKL05Z4.h;
            OPT  1   ;Turn on listing
			GET MKL05.s
;****************************************************************
;EQUates
MAX_STRING  EQU  79
;Characters
BS          EQU  0x08
CR          EQU  0x0D
LF          EQU  0x0A
NULL        EQU  0x00
;---------------------------------------------------------------
; Queue management record field offsets
IN_PTR      EQU   0
OUT_PTR     EQU   4
BUF_STRT    EQU   8
BUF_PAST    EQU   12
BUF_SIZE    EQU   16
NUM_ENQD    EQU   17
; Queue structure sizes
Q_BUF_SZ    EQU   4   ;Queue contents
XQ_BUF_SZ   EQU   80  ;Xmit queue contents
Q_REC_SZ    EQU   18  ;Queue management record
; Queue delimiters for printed output
Q_BEGIN_CH  EQU   '>'
Q_END_CH    EQU   '<'
;---------------------------------------------------------------
;PORTx_PCRn (Port x pin control register n [for pin n])
;___->10-08:Pin mux control (select 0 to 8)
PORT_PCR_PIN_MUX_SELECT_3  EQU  0x00000300
;---------------------------------------------------------------
;Port E
;---------------------------------------------------------------
;UARTx_C1
;0-->7:LOOPS=loops select (normal)
;0-->6:UARTSWAI=UART stop in wait mode (disabled)
;0-->5:RSRC=receiver source select (internal--no effect LOOPS=0)
;0-->4:M=9- or 8-bit mode select (1 start, 8 data [lsb first], 1 stop)
;0-->3:WAKE=receiver wakeup method select (idle)
;0-->2:IDLE=idle line type select (idle begins after start bit)
;0-->1:PE=parity enable (disabled)
;0-->0:PT=parity type (even parity--no effect PE=0)
UART_C1_8N1  EQU  0x00
;---------------------------------------------------------------
;UARTx_C2
;0-->7:TIE=transmit IE for TDRE (disabled)
;0-->6:TCIE=trasmission complete IE for TC (disabled)
;0-->5:RIE=receiver IE for RDRF (disabled)
;0-->4:ILIE=idle line IE for IDLE (disabled)
;1-->3:TE=transmitter enable (enabled)
;1-->2:RE=receiver enable (enabled)
;0-->1:RWU=receiver wakeup control (normal)
;0-->0:SBK=send break (disabled, normal)
UART_C2_T_R    EQU  (UART_C2_TE_MASK :OR: UART_C2_RE_MASK)
UART_C2_T_RI   EQU  (UART_C2_RIE_MASK :OR: UART_C2_T_R)
UART_C2_TI_RI  EQU  (UART_C2_TIE_MASK :OR: UART_C2_T_RI)
;---------------------------------------------------------------
;UARTx_C3
;0-->7:R8=9th data bit for receiver (not used M=0)
;0-->6:T8=9th data bit for transmitter (not used M=0)
;0-->5:TXDIR=TxD pin direction in single-wire mode (no effect LOOPS=0)
;0-->4:TXINV=transmit data inversion (not invereted)
;0-->3:ORIE=overrun IE for OR (disabled)
;0-->2:NEIE=noise error IE for NF (disabled)
;0-->1:FEIE=framing error IE for FE (disabled)
;0-->0:PEIE=parity error IE for PF (disabled)
UART_C3_NO_TXINV  EQU  0x00
;---------------------------------------------------------------
;UARTx_C4
;0-->  7:TDMAS=transmitter DMA select (disabled)
;0-->  6:Reserved; read-only; always 0
;0-->  5:RDMAS=receiver full DMA select (disabled)
;0-->  4:Reserved; read-only; always 0
;0-->  3:Reserved; read-only; always 0
;0-->2-0:Reserved; read-only; always 0
UART_C4_NO_DMA  EQU  0x00
;---------------------------------------------------------------
;UARTx_S2
;0-->7:LBKDIF=LIN break detect interrupt flag
;0-->6:RXEDGIF=RxD pin active edge interrupt flag
;0-->5:(reserved);read-only; always 0
;0-->4:RXINV=receive data inversion (disabled)
;0-->3:RWUID=receive wake-up idle detect
;0-->2:BRK13=break character generation length (10)
;0-->1:LBKDE=LIN break detect enable (disabled)
;0-->0:RAF=receiver active flag
UART_S2_NO_RXINV_BRK10_NO_LBKDETECT  EQU  0x00
;---------------------------------------------------------------
UART0_IRQ_PRI  EQU  3  ;lowest priority
;****************************************************************
; Macros
            MACRO
            MOVC  $Value
;--------------------------
;Puts $Value in C bit of PSR
            PUSH  {R0}
            MOVS  R0,$Value
            LSRS  R0,R0,#1
            POP   {R0}
;--------------------------
            MEND
;****************************************************************
;Program
;Linker requires Reset_Handler
            AREA    MyCode,CODE,READONLY
;>>>>> begin subroutine code <<<<<
;---------------------------------------------------------------
            EXPORT  AddIntMultiU
AddIntMultiU
;**********************************************************************
;Adds two 128-bit unsigned numbers:  Sum = Augend + Addend
;If result overflows, returns 1; otherwie returns 0.
;Input:   R0: Address of Sum
;         R1: Address of Augend
;         R2: Address of Addend
;         R3: Number of words in each number
;Output:  R0: Error result
;Modify:  R0, PSR
;Usage:   R4: Auguend word; Sum word
;         R5: Addend word
;         R6: Temp
;**********************************************************************
;Save registers
            PUSH    {R1-R6}            ;save used registers
            MOVC    #0                 ;clear initial carry
            MRS     R6,APSR            ;preserve condition flags
AddIntMultiULoop                       ;do {
            MSR     APSR,R6            ;  restore condition flags
            LDM     R1!,{R4}           ;  get next augend word
            LDM     R2!,{R5}           ;  get next addend word
            ADCS    R4,R4,R5           ;  add for next sum word
            STM     R0!,{R4}           ;  store result
            MRS     R6,APSR            ;  preserve condition flags
            SUBS    R3,R3,#1           ;} while (LoopCounter-- > 0)
            BHI     AddIntMultiULoop     
            MSR     APSR,R6            ;restore condition flags
            BCS     AddIntMultiUOver   ;if (C clear)
            MOVS    R0,#0              ;  Report no error
            B       AddIntMultiUDone     
AddIntMultiUOver                       ;else (C set)
            MOVS    R0,#1              ;  Report overflow
AddIntMultiUDone                         
            POP     {R1-R6}            ;restore registers
            BX      LR                 ;return
;---------------------------------------------------------------
Dequeue
;**********************************************************************
; Dequeues a character to R0 from queue referenced by R1.
; Sets/clears CCR bit C to reflect failure/success of dequeue.
; Input:   R1: Address of queue management record structure
; Output:  R0: Character dequeued
;          PSR.C = (Boolean) Failure
; Modify:  R0, PSR
;**********************************************************************
;Save registers
            PUSH    {R2-R3}
;Dequeue
            LDRB    R2,[R1,#NUM_ENQD] ;check queue count
            CMP     R2,#0             ;if (queue not empty) {
            BEQ     DequeueFail
            LDR     R3,[R1,#OUT_PTR]  ;  get address of character
            LDRB    R0,[R3,#0]        ;  dequeue character
            ADDS    R3,R3,#1          ;  OutPointer++
            SUBS    R2,R2,#1          ;  NumberEnqueued--
            STRB    R2,[R1,#NUM_ENQD]
            LDR     R2,[R1,#BUF_PAST]  ;  if (OutPointer past buffer) {
            CMP     R3,R2
            BLO     DequeueOutPtr
            LDR     R3,[R1,#BUF_STRT] ;    adjust to start of buffer
DequeueOutPtr                         ;  }end if (OutPointer)
            STR     R3,[R1,#OUT_PTR]  ;  store updated OutPointer
            MOVS    R2,#0             ;  clear C flag (report successful)
            LSRS    R2,R2,#1
            B       DequeueDone       ;}end if (queue)
DequeueFail                           ;else { ;nothing to dequeue
            MOVS    R2,#1             ;  set C flag (report failure)
            LSRS    R2,R2,#1          ;}end else
DequeueDone                        
;Restore registers
            POP     {R2-R3}
            BX      LR
;---------------------------------------------------------------
Enqueue
;**********************************************************************
; Enqueue character from R0.
; Sets/clears CCR bit C to reflect failure/success of dequeue.
; Input:   R0: Character to enqueue
;          R1: Address of queue management record structure
; Output:  CCR.C = (Boolean) Failure
; Modify:  CCR
;**********************************************************************
;Save registers
            PUSH    {R2-R3}
;Enqueue
            LDRB    R2,[R1,#NUM_ENQD] ;check queue count
            LDRB    R3,[R1,#BUF_SIZE] ;against queue capacity
            CMP     R2,R3             ;if queue not full
            BHS     EnqueueFail
            LDR     R3,[R1,#IN_PTR]   ;  address for character
            STRB    R0,[R3,#0]        ;  enqueue character
            ADDS    R3,R3,#1          ;  InPointer++
            ADDS    R2,R2,#1          ;  NumberEnqueued++
            STRB    R2,[R1,#NUM_ENQD]
            LDR     R2,[R1,#BUF_PAST] ;  if (InPointer past buffer) {
            CMP     R3,R2
            BLO     EnqueueInPtr
            LDR     R3,[R1,#BUF_STRT] ;    adjust to start of buffer
EnqueueInPtr                          ;  }end if (InPointer)
            STR     R3,[R1,#IN_PTR]   ;  store updated InPointer
            MOVS    R2,#0             ;  clear C flag (report successful)
            LSRS    R2,R2,#1
            B       EnqueueDone       ;}end if (queue)
EnqueueFail                           ;else {;no room in queue
            MOVS    R2,#1             ;  set C flag (report failure)
            LSRS    R2,R2,#1          ;}end else
EnqueueDone                        
;Restore registers
            POP     {R2-R3}
            BX      LR
;---------------------------------------------------------------
GetChar
;**********************************************************************
;Gets a character from receive queue buffer
;Calls:  Dequeue
;Output:  R0: Character received from queue buffer
;Modifies:  R0, PSR
;**********************************************************************
            PUSH  {R1,LR}         ;save temporary register
            LDR   R1,=RxQRecord   ;setup dequeue parameter
GetCharWait                       ;repeat {
            CPSID I               ;  mask interrupts
            BL    Dequeue         ;  attempt dequeue
            CPSIE I               ;  unmask interrupts
            BCS   GetCharWait     ;} until dequeue successful
            POP   {R1,PC}         ;restore temporary register
;---------------------------------------------------------------
            EXPORT  GetString
GetString
;**********************************************************************
;Receives each character in string from UART0 and adds NULL 
;termination.  Input of CR (from pressing "Enter" key) terminates
;input.  Handles backspace (BS) control code, but all other control 
;codes are ignored.
;Calls:  GetChar
;        PutChar
;EQUate:  MAX_STRING (assumed >= 1)
;Input:  R0: Address of string to transmit
;Modifies:  PSR
;**********************************************************************
            PUSH  {R0-R3,LR}    ;save registers modified
            MOV   R1,R0         ;base address of string
            MOVS  R2,#0         ;character count
            MOVS  R3,#(MAX_STRING - 1) ;maximum characters
            BEQ   GetStringFull  ;while (space for a character) {
GetStringChar
            BL    GetChar        ;  receive character
            CMP   R0,#BS         ;  if backspace
            BEQ   GetStringBS    ;    evaluate position
            CMP   R0,#CR         ;  elseif CR
            BEQ   GetStringDone  ;    done
            CMP   R0,#' '        ;  elseif other control character
            BLO   GetStringChar  ;    ignore
            CMP   R0,#0x7F
            BHI   GetStringChar  ;  else {
            BL    PutChar        ;    echo character
            STRB  R0,[R1,R2]     ;    store in string
            ADDS  R2,R2,#1       ;    character count ++
            CMP   R2,R3          ;  }end else
            BLO   GetStringChar  ;}end while (space for a character)
GetStringFull                    ;repeat {
            BL    GetChar        ;  receive character
            CMP   R0,#BS         ;  if backspace
            BEQ   GetStringBS    ;    evaluate position            
            CMP   R0,#CR
            BNE   GetStringFull  ;} until CR received
GetStringDone
            BL    PutChar        ;echo CR
            MOVS  R0,#LF         ;print LF
            BL    PutChar
            MOVS  R0,#NULL       ;terminate with NULL
            STRB  R0,[R1,R2]
            POP   {R0-R3,PC}     ;restore modified registers and return
GetStringBS CMP   R2,#0          ;if (not at start of string) {
            BEQ   GetStringChar
            BL    PutChar        ;  echo backspace
            SUBS  R2,R2,#1       ;  character count  --
            MOVS  R0,#' '        ;  overwrite with space
            BL    PutChar
            MOVS  R0,#BS         ;  back space
            BL    PutChar
            B     GetStringChar  ;}end if and resume while
;---------------------------------------------------------------
Init_Queue
;**********************************************************************
; Initializes FIFO queue management record structure where R1 points
; for byte queue buffer where R0 points and whose size is in R2.
; Input:  None
; Output:  None
; Modifies:  PSR
;**********************************************************************
            PUSH    {R0}
            STR     R0,[R1,#IN_PTR]
            STR     R0,[R1,#OUT_PTR]
            STR     R0,[R1,#BUF_STRT]
            ADDS    R0,R0,R2
            STR     R0,[R1,#BUF_PAST]
            STRB    R2,[R1,#BUF_SIZE]
            MOVS    R0,#0
            STRB    R0,[R1,#NUM_ENQD]
            POP     {R0}
            BX      LR
;---------------------------------------------------------------
Init_UART0
;**********************************************************************
; Initializes UART0 for 9600 baud and 8N1 format
; Input:  None
; Output:  None
; Modifies:  PSR
;**********************************************************************
;Initialize UART0
            ;Preserve registers used
            PUSH    {R0-R2}
;           ;Set UART0 for external connection
;           LDR     R0,=SIM_SOPT5
;           LDR     R1,=SIM_SOPT5_UART0_EXTERN_MASK_CLEAR
;           LDR     R2,[R0,#0]
;           BICS    R2,R2,R1
;           STR     R2,[R0,#0]
;           ;Enable UART0 module clock
;           LDR     R0,=SIM_SCGC4
;           LDR     R1,=SIM_SCGC4_UART0CGC_MASK
;           LDR     R2,[R0,#0]
;           ORRS    R2,R2,R1
;           STR     R2,[R0,#0]
;           ;Enable PORT E module clock
;   		; CHECK THIS
;           LDR     R0,=SIM_SCGC5
;           LDR     R1,=SIM_SCGC5_PORTECGC_MASK
;           LDR     R2,[R0,#0]
;           ORRS    R2,R2,R1
;           STR     R2,[R0,#0]
;           ;Select PORT E Pin 1 (J2 Pin 20) for UART0 RX
;           LDR     R0,=PORTE_PCR1
;           LDR     R1,=PORT_PCR_SET_PTE1_UART0_RX
;           STR     R1,[R0,#0]
;           ;Select PORT E Pin 0 (J2 Pin 18) for UART0 TX
;           LDR     R0,=PORTE_PCR0
;           LDR     R1,=PORT_PCR_SET_PTE0_UART0_TX
;           STR     R1,[R0,#0]
;   		;THROUGH THIS.

;           ;Set for 9600 baud from 96MHz PLL clock
;           LDR     R0,=UART0_BASE
;           MOVS    R1,#UART_BDH_38400
;           STRB    R1,[R0,#UART_BDH_OFFSET]
;           MOVS    R1,#UART_BDL_38400
;           STRB    R1,[R0,#UART_BDL_OFFSET]
;           MOVS    R1,#UART_C1_8N1
;           STRB    R1,[R0,#UART_C1_OFFSET]
;           MOVS    R1,#UART_C3_NO_TXINV
;           STRB    R1,[R0,#UART_C3_OFFSET]
;           MOVS    R1,#UART_C4_NO_DMA
;           STRB    R1,[R0,#UART_C4_OFFSET]
;           MOVS    R1,#UART_S2_NO_RXINV_BRK10_NO_LBKDETECT
;           STRB    R1,[R0,#UART_S2_OFFSET]
;           MOVS    R1,#UART_C2_T_RI
;           STRB    R1,[R0,#UART_C2_OFFSET]
;           ;Restore registers used
            POP     {R0-R2}
            BX      LR
;---------------------------------------------------------------
PutChar
;**********************************************************************
;Puts character in transmit queue buffer
;Calls:  Enqueue
;Input:  R0: Character to transmit
;Modifies:  PSR
;**********************************************************************
            PUSH  {R1-R2,LR}      ;save temporary registers
            LDR   R1,=TxQRecord   ;setup enqueue parameter
PutCharWait                       ;repeat {
            CPSID I               ;  mask interrupts
            BL    Enqueue         ;  enqueue character
            CPSIE I               ;  unmask interrupts
            BCS   PutCharWait     ;} until successful
            LDR   R1,=UART0_BASE  ;Enable transmit interrupt
            MOVS  R2,#UART_C2_TI_RI
            STRB  R2,[R1,#UART_C2_OFFSET]
            POP   {R1-R2,PC}      ;restore temporary registers
;---------------------------------------------------------------
            EXPORT  PutString
PutString
;**********************************************************************
;Transmits each character in null-terminated string to UART0.
;Calls:  PutChar
;Input:  R0: Address of string to transmit
;Modifies:  PSR
;**********************************************************************
;Save registers
            PUSH   {R0-R2,LR}    
            MOV    R1,R0          ;R0 needed for parameter
PutStringLoop                     ;repeat {
            LDRB   R0,[R1,#0]     ;  CurrentChar of string
            CMP    R0,#NULL       ;  if (CurrentChar != NULL) {
            BEQ    PutStringDone
            BL     PutChar        ;    Send current char to terminal
            ADDS   R1,R1,#1       ;    CurrentCharPtr++
            B      PutStringLoop  ;} until (CurrentChar == NULL)
;Restore registers
PutStringDone
            POP    {R0-R2,PC}
;---------------------------------------------------------------
            EXPORT  SerialDriverInit
SerialDriverInit
;**********************************************************************
;Initializes UART0 and queues for serial driver
;Calls:  InitQueue
;Modifies:  PSR
;**********************************************************************
            PUSH    {R0-R2,LR}
            ;Initialize UART0 for 8N1, 9600 with RIE
            BL      Init_UART0
            ;Unmask UART0 interrupts
            LDR     R0,=NVIC_ISER
            LDR     R1,=UART0_IRQ_MASK
            STR     R1,[R0,#0]
            ;Set UART0 interrupt priority
            LDR     R0,=UART0_IPR
            LDR     R1,=(UART0_IRQ_PRI << UART0_PRI_POS)
            STR     R1,[R0,#0]
;---------------------------------------------------------------
;Initialize circular FIFO queue management record structures
            ;Rx queue
            LDR     R0,=RxQBuffer
            LDR     R1,=RxQRecord
            MOVS    R2,#XQ_BUF_SZ
            BL      Init_Queue  ;initialize queue record
            ;Tx queue
            LDR     R0,=TxQBuffer
            LDR     R1,=TxQRecord
            ;MOVS    R2,#XQ_BUF_SZ
            BL      Init_Queue  ;initialize queue record
            POP     {R0-R2,PC}
;---------------------------------------------------------------
UART0_ISR
;**********************************************************************
;UART0 Interrupt Service Routine
;**********************************************************************
            CPSID I                       ;mask all KL46 interrupts
            PUSH  {LR}                    ;save modified register
            LDR   R2,=UART0_BASE          ;if TxIRQ enabled {
            MOVS  R0,#UART_C2_TIE_MASK
            LDRB  R3,[R2,#UART_C2_OFFSET]
            TST   R3,R0
            BEQ   UART0_ISR_RxCheck
            MOVS  R0,#UART_S1_TDRE_MASK   ;  if TxIRQ { 
            LDRB  R3,[R2,#UART_S1_OFFSET]
            TST   R3,R0
            BEQ   UART0_ISR_RxCheck
            LDR   R1,=TxQRecord           ;    setup TxQ dequeue
            BL    Dequeue                 ;    dequeue
            BCS   UART0_ISR_TxIRQDisable  ;    if successful {
            STRB  R0,[R2,#UART_D_OFFSET]  ;      transmit character
                                          ;    } endif successful
                                          ;  } endif TxIRQ
                                          ;} endif TxIRQ enabled
UART0_ISR_RxCheck                         ;if RxIRQ {
            MOVS  R0,#UART_S1_RDRF_MASK
            LDRB  R3,[R2,#UART_S1_OFFSET]
            TST   R3,R0
            BEQ   UART0_ISR_Done
            LDRB  R0,[R2,#UART_D_OFFSET]  ;  receive character
            LDR   R1,=RxQRecord           ;  setup RxQ enequeue
            BL    Enqueue                 ;  enqueue
UART0_ISR_Done                            ;}end if RxIRQ
            CPSIE I                       ;unmask all KL46 interrupts
            POP   {PC}
UART0_ISR_TxIRQDisable                    ;TxIRQ dequeue unsuccessful {
            MOVS  R3,#UART_C2_T_RI        ;  disable TxIRQ
            STRB  R3,[R2,#UART_C2_OFFSET]
            B     UART0_ISR_RxCheck       ;}
;---------------------------------------------------------------
;>>>>>   end subroutine code <<<<<
            ALIGN
;****************************************************************
            ALIGN
;****************************************************************
;Constants
            AREA    MyConst,DATA,READONLY
;>>>>> begin constants here <<<<<
;>>>>>   end constants here <<<<<
;****************************************************************
;Variables
            AREA    MyData,DATA,READWRITE
;>>>>> begin variables here <<<<<
RxQBuffer   SPACE   XQ_BUF_SZ  ; FIFO queue buffer
            ALIGN
RxQRecord   SPACE   Q_REC_SZ  ; FIFO queue management record
TxQBuffer   SPACE   XQ_BUF_SZ  ; FIFO queue buffer
            ALIGN
TxQRecord   SPACE   Q_REC_SZ  ; FIFO queue management record
;>>>>>   end variables here <<<<<
            END

