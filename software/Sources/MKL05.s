            OPT   2   ;Turn off listing
            IF    :DEF:MIXED_ASM_C
            PRESERVE8
            ELSE
            PRESERVE8   {FALSE}
            ENDIF
;**********************************************************************
;Freescale MKL46Z256xxx4 device values and configuration code
;* Various EQUATES for memory map
;[1] Freescale Semiconductor, <B>Kinetis L Peripheral Module Quick
;    Reference</B>, KLQRUG, Rev. 0, 9/2012.
;[2] ARM, <B>Application Note 48 Scatter Loading</B>, ARM DAI 0048A,
;    Jan. 1998
;[3] Freescale Semiconductor, <B>KL46 Sub-Family Reference Manual</B>,
;    KL46P121M48SF4RM, Rev. 3, 7/2013.
;[4] Freescale Semiconductor, MKL46Z4.h, rev. 2.2, 4/12/2013
;---------------------------------------------------------------
;Author:  R. W. Melton
;Date:  February 16, 2015
;***************************************************************
;EQUates
;Data sizes
WORD_SIZE         EQU  4  ;Cortex-M0+
HALFWORD_SIZE     EQU  2  ;Cortex-M0+
;Return                 
RET_ADDR_T_MASK   EQU  1  ;Bit 0 of ret. addr. must be
                          ;set for BX, BLX, or POP
                          ;mask in thumb
;---------------------------------------------------------------
;Vectors
VECTOR_TABLE_SIZE EQU 0x000000C0  ;KL46
VECTOR_SIZE       EQU 4           ;Bytes per vector
;---------------------------------------------------------------
;CPU PSR:  Program status register
;Combined APSR, EPSR, and IPSR
;----------------------------------------------------------
;APSR:  Application Program Status Register
;31  :N=negative flag
;30  :Z=zero flag
;29  :C=carry flag
;28  :V=overflow flag
;27-0:(reserved)
APSR_MASK     EQU  0xF0000000
APSR_SHIFT    EQU  28
APSR_N_MASK   EQU  0x80000000
APSR_N_SHIFT  EQU  31
APSR_Z_MASK   EQU  0x40000000
APSR_Z_SHIFT  EQU  30
APSR_C_MASK   EQU  0x20000000
APSR_C_SHIFT  EQU  29
APSR_V_MASK   EQU  0x10000000
APSR_V_SHIFT  EQU  28
;----------------------------------------------------------
;EPSR
;31-25:(reserved)
;   24:T=thumb state bit
;23- 0:(reserved)
EPSR_MASK     EQU  0x01000000
EPSR_SHIFT    EQU  24
EPSR_T_MASK   EQU  0x01000000
EPSR_T_SHIFT  EQU  24
;----------------------------------------------------------
;IPSR
;31-6:(reserved)
; 5-0:Exception number=number of current exception
;      0=thread mode
;      1:(reserved)
;      2=NMI
;      3=hard fault
;      4-10:(reserved)
;     11=SVCall
;     12-13:(reserved)
;     14=PendSV
;     15=SysTick
;     16=IRQ0
;     16-47:IRQ(Exception number - 16)
;     47=IRQ31
;     48-63:(reserved)
IPSR_MASK             EQU  0x0000003F
IPSR_SHIFT            EQU  0
IPSR_EXCEPTION_MASK   EQU  0x0000003F
IPSR_EXCEPTION_SHIFT  EQU  0
;----------------------------------------------------------
PSR_N_MASK           EQU  APSR_N_MASK
PSR_N_SHIFT          EQU  APSR_N_SHIFT
PSR_Z_MASK           EQU  APSR_Z_MASK
PSR_Z_SHIFT          EQU  APSR_Z_SHIFT
PSR_C_MASK           EQU  APSR_C_MASK
PSR_C_SHIFT          EQU  APSR_C_SHIFT
PSR_V_MASK           EQU  APSR_V_MASK
PSR_V_SHIFT          EQU  APSR_V_SHIFT
PSR_T_MASK           EQU  EPSR_T_MASK
PSR_T_SHIFT          EQU  EPSR_T_SHIFT
PSR_EXCEPTION_MASK   EQU  IPSR_EXCEPTION_MASK
PSR_EXCEPTION_SHIFT  EQU  IPSR_EXCEPTION_SHIFT
;---------------------------------------------------------------
;ADC
ADC0_BASE         EQU  0x4003B000
ADC_SC1A_OFFSET  EQU  0x00
ADC_SC1B_OFFSET  EQU  0x04
ADC_CFG1_OFFSET  EQU  0x08
ADC_CFG2_OFFSET  EQU  0x0C
ADC_RA_OFFSET    EQU  0x10
ADC_RB_OFFSET    EQU  0x14
ADC_CV1_OFFSET   EQU  0x18
ADC_CV2_OFFSET   EQU  0x1C
ADC_SC2_OFFSET   EQU  0x20
ADC_SC3_OFFSET   EQU  0x24
ADC_OFS_OFFSET   EQU  0x28
ADC_PG_OFFSET    EQU  0x2C
ADC_MG_OFFSET    EQU  0x30
ADC_CLPD_OFFSET  EQU  0x34
ADC_CLPS_OFFSET  EQU  0x38
ADC_CLP4_OFFSET  EQU  0x3C
ADC_CLP3_OFFSET  EQU  0x40
ADC_CLP2_OFFSET  EQU  0x44
ADC_CLP1_OFFSET  EQU  0x48
ADC_CLP0_OFFSET  EQU  0x4C
ADC_CLMD_OFFSET  EQU  0x54
ADC_CLMS_OFFSET  EQU  0x58
ADC_CLM4_OFFSET  EQU  0x5C
ADC_CLM3_OFFSET  EQU  0x60
ADC_CLM2_OFFSET  EQU  0x64
ADC_CLM1_OFFSET  EQU  0x68
ADC_CLM0_OFFSET  EQU  0x6C
ADC0_CFG1         EQU  ( ADC0_BASE + ADC_CFG1_OFFSET)
ADC0_CFG2         EQU  ( ADC0_BASE + ADC_CFG2_OFFSET)
ADC0_CLMD         EQU  ( ADC0_BASE + ADC_CLMD_OFFSET)
ADC0_CLMS         EQU  ( ADC0_BASE + ADC_CLMS_OFFSET)
ADC0_CLM0         EQU  ( ADC0_BASE + ADC_CLM0_OFFSET)
ADC0_CLM1         EQU  ( ADC0_BASE + ADC_CLM1_OFFSET)
ADC0_CLM2         EQU  ( ADC0_BASE + ADC_CLM2_OFFSET)
ADC0_CLM3         EQU  ( ADC0_BASE + ADC_CLM3_OFFSET)
ADC0_CLM4         EQU  ( ADC0_BASE + ADC_CLM4_OFFSET)
ADC0_CLPD         EQU  ( ADC0_BASE + ADC_CLPD_OFFSET)
ADC0_CLPS         EQU  ( ADC0_BASE + ADC_CLPS_OFFSET)
ADC0_CLP0         EQU  ( ADC0_BASE + ADC_CLP0_OFFSET)
ADC0_CLP1         EQU  ( ADC0_BASE + ADC_CLP1_OFFSET)
ADC0_CLP2         EQU  ( ADC0_BASE + ADC_CLP2_OFFSET)
ADC0_CLP3         EQU  ( ADC0_BASE + ADC_CLP3_OFFSET)
ADC0_CLP4         EQU  ( ADC0_BASE + ADC_CLP4_OFFSET)
ADC0_CV1          EQU  ( ADC0_BASE + ADC_CV1_OFFSET)
ADC0_CV2          EQU  ( ADC0_BASE + ADC_CV2_OFFSET)
ADC0_MG           EQU  ( ADC0_BASE + ADC_MG_OFFSET) 
ADC0_OFS          EQU  ( ADC0_BASE + ADC_OFS_OFFSET)
ADC0_PG           EQU  ( ADC0_BASE + ADC_PG_OFFSET) 
ADC0_RA           EQU  ( ADC0_BASE + ADC_RA_OFFSET)  
ADC0_RB           EQU  ( ADC0_BASE + ADC_RB_OFFSET)  
ADC0_SC1A         EQU  ( ADC0_BASE + ADC_SC1A_OFFSET)
ADC0_SC1B         EQU  ( ADC0_BASE + ADC_SC1B_OFFSET)
ADC0_SC2          EQU  ( ADC0_BASE + ADC_SC2_OFFSET)
ADC0_SC3          EQU  ( ADC0_BASE + ADC_SC3_OFFSET)
;---------------------------------------------------------------
;ADC_CFG1:  ADC configuration register 1
;31-8:(reserved):read-only:0
;   7:ADLPC=ADC low-power configuration
; 6-5:ADIV=ADC clock divide select
;     Internal ADC clock = input clock / 2^ADIV
;   4:ADLSMP=ADC long sample time configuration
;            0=short
;            1=long
; 3-2:MODE=conversion mode selection
;          00=(DIFF'):single-ended 8-bit conversion
;             (DIFF):differential 9-bit 2's complement conversion
;          01=(DIFF'):single-ended 12-bit conversion
;             (DIFF):differential 13-bit 2's complement conversion
;          10=(DIFF'):single-ended 10-bit conversion
;             (DIFF):differential 11-bit 2's complement conversion
;          11=(DIFF'):single-ended 16-bit conversion
;             (DIFF):differential 16-bit 2's complement conversion
; 1-0:ADICLK=ADC input clock select
;          00=bus clock
;          01=bus clock / 2
;          10=alternate clock (ALTCLK)
;          11=asynchronous clock (ADACK)
ADC_CFG1_ADLPC_MASK   EQU  0x80
ADC_CFG1_ADLPC_SHIFT  EQU  7
ADC_CFG1_ADIV_MASK    EQU  0x60
ADC_CFG1_ADIV_SHIFT   EQU  5
ADC_CFG1_ADLSMP_MASK  EQU  0x10
ADC_CFG1_ADLSMP_SHIFT EQU  4
ADC_CFG1_MODE_MASK    EQU  0x0C
ADC_CFG1_MODE_SHIFT   EQU  2
ADC_CFG1_ADICLK_MASK  EQU  0x03
ADC_CFG1_ADICLK_SHIFT EQU  0
;---------------------------------------------------------------
;ADC_CFG2:  ADC configuration register 2
;31-8:(reserved):read-only:0
; 7-5:(reserved):read-only:0
;   4:MUXSEL=ADC mux select
;            0=ADxxA channels are selected
;            1=ADxxB channels are selected
;   3:ADACKEN=ADC asynchronous clock output enable
;             0=asynchronous clock determined by ACD0_CFG1.ADICLK 
;             1=asynchronous clock enabled
;   2:ADHSC=ADC high-speed configuration
;           0=normal conversion
;           1=high-speed conversion (only 2 additional ADK cycles)
; 1-0:ADLSTS=ADC long sample time select (ADK cycles)
;          00=default longest sample time:  
;             24 total ADK cycles (20 extra)
;          01=16 total ADK cycles (12 extra)
;          10=10 total ADK cycles (6 extra)
;          11=6 total ADK cycles (2 extra)
ADC_CFG2_MUXSEL_MASK    EQU  0x10
ADC_CFG2_MUXSEL_SHIFT   EQU  4
ADC_CFG2_ADACKEN_MASK   EQU  0x08
ADC_CFG2_ADACKEN_SHIFT  EQU  3
ADC_CFG2_ADHSC_MASK     EQU  0x04
ADC_CFG2_ADHSC_SHIFT    EQU  2
ADC_CFG2_ADLSTS_MASK    EQU  0x03
ADC_CFG2_ADLSTS_SHIFT   EQU  0
;---------------------------------------------------------------
;ADC_CLMD:  ADC minus-side general calibration value register D
;31-6:(reserved):read-only:0
; 5-0:CLMD=calibration value
ADC_CLMD_MASK   EQU  0x3F
ADC_CLMD_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_CLMS:  ADC minus-side general calibration value register S
;31-6:(reserved):read-only:0
; 5-0:CLMS=calibration value
ADC_CLMS_MASK   EQU  0x3F
ADC_CLMS_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_CLM0:  ADC minus-side general calibration value register 0
;31-6:(reserved):read-only:0
; 5-0:CLM0=calibration value
ADC_CLM0_MASK   EQU  0x3F
ADC_CLM0_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_CLM1:  ADC minus-side general calibration value register 1
;31-7:(reserved):read-only:0
; 6-0:CLM1=calibration value
ADC_CLM1_MASK   EQU  0x7F
ADC_CLM1_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_CLM2:  ADC minus-side general calibration value register 2
;31-8:(reserved):read-only:0
; 7-0:CLM2=calibration value
ADC_CLM2_MASK   EQU  0xFF
ADC_CLM2_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_CLM3:  ADC minus-side general calibration value register 3
;31-9:(reserved):read-only:0
; 8-0:CLM3=calibration value
ADC_CLM3_MASK   EQU  0x1FF
ADC_CLM3_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_CLM4:  ADC minus-side general calibration value register 4
;31-10:(reserved):read-only:0
; 9- 0:CLM4=calibration value
ADC_CLM4_MASK   EQU  0x3FF
ADC_CLM4_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_CLPD:  ADC plus-side general calibration value register D
;31-6:(reserved):read-only:0
; 5-0:CLPD=calibration value
ADC_CLPD_MASK   EQU  0x3F
ADC_CLPD_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_CLPS:  ADC plus-side general calibration value register S
;31-6:(reserved):read-only:0
; 5-0:CLPS=calibration value
ADC_CLPS_MASK   EQU  0x3F
ADC_CLPS_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_CLP0:  ADC plus-side general calibration value register 0
;31-6:(reserved):read-only:0
; 5-0:CLP0=calibration value
ADC_CLP0_MASK   EQU  0x3F
ADC_CLP0_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_CLP1:  ADC plus-side general calibration value register 1
;31-7:(reserved):read-only:0
; 6-0:CLP1=calibration value
ADC_CLP1_MASK   EQU  0x7F
ADC_CLP1_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_CLP2:  ADC plus-side general calibration value register 2
;31-8:(reserved):read-only:0
; 7-0:CLP2=calibration value
ADC_CLP2_MASK   EQU  0xFF
ADC_CLP2_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_CLP3:  ADC plus-side general calibration value register 3
;31-9:(reserved):read-only:0
; 8-0:CLP3=calibration value
ADC_CLP3_MASK   EQU  0x1FF
ADC_CLP3_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_CLP4:  ADC plus-side general calibration value register 4
;31-10:(reserved):read-only:0
; 9- 0:CLP4=calibration value
ADC_CLP4_MASK   EQU  0x3FF
ADC_CLP4_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_CVn:  ADC channel n compare value register
;CV1 used to compare result when ADC_SC2.ACFE=1
;CV2 used to compare result when ADC_SC2.ACREN=1
;31-16:(reserved):read-only:0
;15- 0:compare value (sign- or zero-extended if fewer than 16 bits)
ADC_CV_MASK   EQU  0xFFFF
ADC_CV_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_MG:  ADC minus-side gain register
;31-16:(reserved):read-only:0
;15- 0:MG=minus-side gain
ADC_MG_MASK   EQU  0xFFFF
ADC_MG_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_OFS:  ADC offset correction register
;31-16:(reserved):read-only:0
;15- 0:OFS=offset error correction value
ADC_OFS_MASK   EQU  0xFFFF
ADC_OFS_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_PG:  ADC plus-side gain register
;31-16:(reserved):read-only:0
;15- 0:PG=plus-side gain
ADC_PG_MASK   EQU  0xFFFF
ADC_PG_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_Rn:  ADC channel n data result register
;31-16:(reserved):read-only:0
;15- 0:data result (sign- or zero-extended if fewer than 16 bits)
ADC_D_MASK   EQU  0xFFFF
ADC_D_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_SC1n:  ADC channel n status and control register 1
;31-8:(reserved):read-only:0
;   7:COCO=conversion complete flag (read-only)
;   6:AIEN=ADC interrupt enabled
;   5:DIFF=differential mode enable
; 4-0:ADCH=ADC input channel select
;          00000=(DIFF'):DADP0;(DIFF):DAD0
;          00001=(DIFF'):DADP1;(DIFF):DAD1
;          00010=(DIFF'):DADP2;(DIFF):DAD2
;          00011=(DIFF'):DADP3;(DIFF):DAD3
;          00100=(DIFF'):AD4;(DIFF):(reserved)
;          00101=(DIFF'):AD5;(DIFF):(reserved)
;          00110=(DIFF'):AD6;(DIFF):(reserved)
;          00111=(DIFF'):AD7;(DIFF):(reserved)
;          01000=(DIFF'):AD8;(DIFF):(reserved)
;          01001=(DIFF'):AD9;(DIFF):(reserved)
;          01010=(DIFF'):AD10;(DIFF):(reserved)
;          01011=(DIFF'):AD11;(DIFF):(reserved)
;          01100=(DIFF'):AD12;(DIFF):(reserved)
;          01101=(DIFF'):AD13;(DIFF):(reserved)
;          01110=(DIFF'):AD14;(DIFF):(reserved)
;          01111=(DIFF'):AD15;(DIFF):(reserved)
;          10000=(DIFF'):AD16;(DIFF):(reserved)
;          10001=(DIFF'):AD17;(DIFF):(reserved)
;          10010=(DIFF'):AD18;(DIFF):(reserved)
;          10011=(DIFF'):AD19;(DIFF):(reserved)
;          10100=(DIFF'):AD20;(DIFF):(reserved)
;          10101=(DIFF'):AD21;(DIFF):(reserved)
;          10110=(DIFF'):AD22;(DIFF):(reserved)
;          10111=(DIFF'):AD23;(DIFF):(reserved)
;          11000 (reserved)
;          11001 (reserved)
;          11010=(DIFF'):temp sensor (single-ended)
;                (DIFF):temp sensor (differential)
;          11011=(DIFF'):bandgap (single-ended)
;                (DIFF):bandgap (differential)
;          11100 (reserved)
;          11101=(DIFF'):VREFSH (single-ended)
;                (DIFF):-VREFSH (differential)
;          11110=(DIFF'):VREFSL (single-ended)
;                (DIFF):(reserved)
;          11111=disabled
ADC_COCO_MASK   EQU  0x80
ADC_COCO_SHIFT  EQU  7
ADC_AIEN_MASK   EQU  0x40
ADC_AIEN_SHIFT  EQU  6
ADC_DIFF_MASK   EQU  0x20
ADC_DIFF_SHIFT  EQU  5
ADC_ADCH_MASK   EQU  0x1F
ADC_ADCH_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_SC2:  ADC status and control register 2
;31-8:(reserved):read-only:0
;   7:ADACT=ADC conversion active
;   6:ADTRG=ADC conversion trigger select
;           0=software trigger
;           1=hardware trigger
;   5:ACFE=ADC compare function enable
;   4:ACFGT=ADC compare function greater than enable
;           based on values in ADC_CV1 and ADC_CV2
;           0=configure less than threshold and non-inclusive range
;           1=configure greater than threshold and non-inclusive range
;   3:ACREN=ADC compare function range enable
;           0=disabled; only ADC_CV1 compared
;           1=enabled; both ADC_CV1 and ADC_CV2 compared
;   2:DMAEN=DMA enable
; 1-0:REFSEL=voltage reference selection
;            00=default:VREFH and VREFL
;            01=alterantive:VALTH and VALTL
;            10=(reserved)
;            11=(reserved)
ADC_ADACT_MASK    EQU  0x80
ADC_ADACT_SHIFT   EQU  7
ADC_ADTRG_MASK    EQU  0x40
ADC_ADTRG_SHIFT   EQU  6
ADC_ACFE_MASK     EQU  0x20
ADC_ACFE_SHIFT    EQU  5
ADC_ACFGT_MASK    EQU  0x10
ADC_ACFGT_SHIFT   EQU  4
ADC_ACREN_MASK    EQU  0x08
ADC_ACREN_SHIFT   EQU  3
ADC_DMAEN_MASK    EQU  0x04
ADC_DMAEN_SHIFT   EQU  2
ADC_REFSEL_MASK   EQU  0x03
ADC_REFSEL_SHIFT  EQU  0
;---------------------------------------------------------------
;ADC_SC3:  ADC status and control register 3
;31-8:(reserved):read-only:0
;   7:CAL=calibration
;         write:0=(no effect)
;               1=start calibration sequence
;         read:0=calibration sequence complete
;              1=calibration sequence in progress
;   6:CALF=calibration failed flag
; 5-4:(reserved):read-only:0
;   3:ADC=ADC continuous conversion enable (if ADC_SC3.AVGE = 1)
;   2:AVGE=hardware average enable
; 1-0:AVGS=hardware average select:  2^(2+AVGS) samples
ADC_CAL_MASK    EQU  0x80
ADC_CAL_SHIFT   EQU  7
ADC_CALF_MASK   EQU  0x40
ADC_CALF_SHIFT  EQU  6
ADC_ADCO_MASK   EQU  0x08
ADC_ADCO_SHIFT  EQU  3
ADC_AVGE_MASK   EQU  0x04
ADC_AVGE_SHIFT  EQU  2
ADC_AVGS_MASK   EQU  0x03
ADC_AVGS_SHIFT  EQU  0
;---------------------------------------------------------------
;DAC
DAC0_BASE          EQU  0x4003F000
DAC0_DAT0L_OFFSET  EQU  0x00
DAC0_DAT0H_OFFSET  EQU  0x01
DAC0_DAT1L_OFFSET  EQU  0x02
DAC0_DAT1H_OFFSET  EQU  0x03
DAC0_SR_OFFSET     EQU  0x20
DAC0_C0_OFFSET     EQU  0x21
DAC0_C1_OFFSET     EQU  0x22
DAC0_C2_OFFSET     EQU  0x23
DAC0_DAT0L         EQU  (DAC0_BASE + DAC0_DAT0L_OFFSET)
DAC0_DAT0H         EQU  (DAC0_BASE + DAC0_DAT0H_OFFSET)
DAC0_DAT1L         EQU  (DAC0_BASE + DAC0_DAT1L_OFFSET)
DAC0_DAT1H         EQU  (DAC0_BASE + DAC0_DAT1H_OFFSET)
DAC0_SR            EQU  (DAC0_BASE + DAC0_SR_OFFSET)
DAC0_C0            EQU  (DAC0_BASE + DAC0_C0_OFFSET)
DAC0_C1            EQU  (DAC0_BASE + DAC0_C1_OFFSET)
DAC0_C2            EQU  (DAC0_BASE + DAC0_C2_OFFSET)
;---------------------------------------------------------------
;DAC_DAT0H:  DAC data high register 0
;If buffer not enabled, Vout = Vin * (1 + DATA[11:0])/4096.
;7-4:(reserved):read-only:0
;3-0:DATA1=DATA[11:8]
DAC_DAT0H_MASK   EQU  0x0F
DAC_DAT0H_SHIFT  EQU  0
;---------------------------------------------------------------
;DAC_DAT0L:  DAC data low register 0
;If buffer not enabled, Vout = Vin * (1 + DATA[11:0])/4096.
;7-0:DATA0=DATA[7:0]
;---------------------------------------------------------------
;DAC_DAT1H:  DAC data high register 1
;If buffer not enabled, Vout = Vin * (1 + DATA[11:0])/4096.
;7-4:(reserved):read-only:0
;3-0:DATA1=DATA[11:8]
DAC_DAT1H_MASK   EQU  0x0F
DAC_DAT1H_SHIFT  EQU  0
;---------------------------------------------------------------
;DAC_DAT1L:  DAC data low register 1
;If buffer not enabled, Vout = Vin * (1 + DATA[11:0])/4096.
;7-0:DATA0=DATA[7:0]
;---------------------------------------------------------------
;DAC_C0:  DAC control register 0
;7:DACEN=DAC enable
;6:DACRFS=DAC reference select
;         0:DACREF_1=VREFH
;         1:DACREF_2=VDDA (best for ADC operation)
;5:DACTRGSEL=DAC trigger select
;            0:HW
;            1:SW
;4:DACSWTRG=DAC software trigger
;           active-high write-only field that reads 0
;           DACBFEN & DACTRGSEL:  writing 1 advances buffer pointer
;3:LPEN=DAC low power control
;       0:high-power mode
;       1:low-power mode
;2:(reserved):read-only:0
;1:DACBTIEN=DAC buffer read pointer top flag interrupt enable
;0:DACBBIEN=DAC buffer read pointer bottom flag interrupt enable
DAC_C0_DACEN_MASK       EQU  0x80
DAC_C0_DACEN_SHIFT      EQU  7
DAC_C0_DACRFS_MASK      EQU  0x40
DAC_C0_DACRFS_SHIFT     EQU  6
DAC_C0_DACTRGSEL_MASK   EQU  0x20
DAC_C0_DACTRGSEL_SHIFT  EQU  5
DAC_C0_DACSWTRG_MASK    EQU  0x10
DAC_C0_DACSWTRG_SHIFT   EQU  4
DAC_C0_LPEN_MASK        EQU  0x08
DAC_C0_LPEN_SHIFT       EQU  3
DAC_C0_DACBTIEN_MASK    EQU  0x02
DAC_C0_DACBTIEN_SHIFT   EQU  1
DAC_C0_DACBBIEN_MASK    EQU  0x01
DAC_C0_DACBBIEN_SHIFT   EQU  0
;---------------------------------------------------------------
;DAC_C1:  DAC control register 1
;  7:DMAEN=DMA enable select
;6-3:(reserved)
;  2:DACBFMD=DAC buffer work mode select
;            0:normal
;            1:one-time scan
;  1:(reserved)
;  0:DACBFEN=DAC buffer enable
;            0:disabled:data in first word of buffer
;            1:enabled:read pointer points to data
DAC_C1_DMAEN_MASK       EQU  0x80
DAC_C1_DMAEN_SHIFT      EQU  7
DAC_C1_DACBFMD_MASK     EQU  0x04
DAC_C1_DACBFMD_SHIFT    EQU  2
DAC_C1_DACBFEN_MASK     EQU  0x01
DAC_C1_DACBFEN_SHIFT    EQU  0
;---------------------------------------------------------------
;DAC_C2:  DAC control register 2
;7-5:(reserved):read-only:0
;  4:DACBFRP=DAC buffer read pointer
;3-1:(reserved):read-only:0
;  0:DACBFUP=DAC buffer read upper limit
DAC_C2_DACBFRP_MASK   EQU  0x10
DAC_C2_DACBFRP_SHIFT  EQU  4
DAC_C2_DACBFUP_MASK   EQU  0x01
DAC_C2_DACBFUP_SHIFT  EQU  0
;---------------------------------------------------------------
;DAC_SR:  DAC status register
;Writing 0 clears a field; writing 1 has no effect.
;7-2:(reserved):read-only:0
;1:DACBFRPTF=DAC buffer read pointer top position flag
;            Indicates whether pointer is zero
;0:DACBFRPBF=DAC buffer read pointer bottom position flag
;            Indicates whether pointer is equal to DAC0_C2.DACBFUP.
DAC_SR_DACBFRPTF_MASK   EQU 0x02
DAC_SR_DACBFRPTF_SHIFT  EQU 1
DAC_SR_DACBFRPBF_MASK   EQU 0x01
DAC_SR_DACBFRPBF_SHIFT  EQU 0
;---------------------------------------------------------------
;Fast (zero wait state) GPIO (FGPIO) or (IOPORT)
;FGPIOx_PDD: Port x Data Direction Register
;Bit n:  0=Port x pin n configured as input
;        1=Port x pin n configured as output
FGPIO_BASE         EQU  0xF80FF000
;offsets for PDOR, PSOR, PCOR, PTOR, PDIR, and PDDR defined
;  with GPIO EQUates
;offsets for Ports A-E defined with GPIO EQUates
;Port A
FGPIOA_BASE        EQU  0xF80FF000
FGPIOA_PDOR        EQU  (FGPIOA_BASE + GPIO_PDOR_OFFSET)
FGPIOA_PSOR        EQU  (FGPIOA_BASE + GPIO_PSOR_OFFSET)
FGPIOA_PCOR        EQU  (FGPIOA_BASE + GPIO_PCOR_OFFSET)
FGPIOA_PTOR        EQU  (FGPIOA_BASE + GPIO_PTOR_OFFSET)
FGPIOA_PDIR        EQU  (FGPIOA_BASE + GPIO_PDIR_OFFSET)
FGPIOA_PDDR        EQU  (FGPIOA_BASE + GPIO_PDDR_OFFSET)
;Port B
FGPIOB_BASE        EQU  0xF80FF040
FGPIOB_PDOR        EQU  (FGPIOB_BASE + GPIO_PDOR_OFFSET)
FGPIOB_PSOR        EQU  (FGPIOB_BASE + GPIO_PSOR_OFFSET)
FGPIOB_PCOR        EQU  (FGPIOB_BASE + GPIO_PCOR_OFFSET)
FGPIOB_PTOR        EQU  (FGPIOB_BASE + GPIO_PTOR_OFFSET)
FGPIOB_PDIR        EQU  (FGPIOB_BASE + GPIO_PDIR_OFFSET)
FGPIOB_PDDR        EQU  (FGPIOB_BASE + GPIO_PDDR_OFFSET)
;Port C
FGPIOC_BASE        EQU  0xF80FF080
FGPIOC_PDOR        EQU  (FGPIOC_BASE + GPIO_PDOR_OFFSET)
FGPIOC_PSOR        EQU  (FGPIOC_BASE + GPIO_PSOR_OFFSET)
FGPIOC_PCOR        EQU  (FGPIOC_BASE + GPIO_PCOR_OFFSET)
FGPIOC_PTOR        EQU  (FGPIOC_BASE + GPIO_PTOR_OFFSET)
FGPIOC_PDIR        EQU  (FGPIOC_BASE + GPIO_PDIR_OFFSET)
FGPIOC_PDDR        EQU  (FGPIOC_BASE + GPIO_PDDR_OFFSET)
;Port D
FGPIOD_BASE        EQU  0xF80FF0C0
FGPIOD_PDOR        EQU  (FGPIOD_BASE + GPIO_PDOR_OFFSET)
FGPIOD_PSOR        EQU  (FGPIOD_BASE + GPIO_PSOR_OFFSET)
FGPIOD_PCOR        EQU  (FGPIOD_BASE + GPIO_PCOR_OFFSET)
FGPIOD_PTOR        EQU  (FGPIOD_BASE + GPIO_PTOR_OFFSET)
FGPIOD_PDIR        EQU  (FGPIOD_BASE + GPIO_PDIR_OFFSET)
FGPIOD_PDDR        EQU  (FGPIOD_BASE + GPIO_PDDR_OFFSET)
;Port E
FGPIOE_BASE        EQU  0xF80FF100
FGPIOE_PDOR        EQU  (FGPIOE_BASE + GPIO_PDOR_OFFSET)
FGPIOE_PSOR        EQU  (FGPIOE_BASE + GPIO_PSOR_OFFSET)
FGPIOE_PCOR        EQU  (FGPIOE_BASE + GPIO_PCOR_OFFSET)
FGPIOE_PTOR        EQU  (FGPIOE_BASE + GPIO_PTOR_OFFSET)
FGPIOE_PDIR        EQU  (FGPIOE_BASE + GPIO_PDIR_OFFSET)
FGPIOE_PDDR        EQU  (FGPIOE_BASE + GPIO_PDDR_OFFSET)
;---------------------------------------------------------------
;Flash Configuration Field (FCF) 0x400-0x40F
;Following Freescale startup_MKL46Z4.s
;     CMSIS Cortex-M0plus Core Device Startup File for the MKL64Z4
;     v2.2, 4/12/2013
;16-byte flash configuration field that stores default protection settings
;(loaded on reset) and security information that allows the MCU to 
;restrict acces to the FTFL module.
;FCF Backdoor Comparison Key
;8 bytes from 0x400-0x407
;-----------------------------------------------------
;FCF Backdoor Comparison Key 0
;7-0:Backdoor Key 0
FCF_BACKDOOR_KEY0  EQU  0xFF
;-----------------------------------------------------
;FCF Backdoor Comparison Key 1
;7-0:Backdoor Key 1
FCF_BACKDOOR_KEY1  EQU  0xFF
;-----------------------------------------------------
;FCF Backdoor Comparison Key 2
;7-0:Backdoor Key 2
FCF_BACKDOOR_KEY2  EQU  0xFF
;-----------------------------------------------------
;FCF Backdoor Comparison Key 3
;7-0:Backdoor Key 3
FCF_BACKDOOR_KEY3  EQU  0xFF
;-----------------------------------------------------
;FCF Backdoor Comparison Key 4
;7-0:Backdoor Key 4
FCF_BACKDOOR_KEY4  EQU  0xFF
;-----------------------------------------------------
;FCF Backdoor Comparison Key 5
;7-0:Backdoor Key 5
FCF_BACKDOOR_KEY5  EQU  0xFF
;-----------------------------------------------------
;FCF Backdoor Comparison Key 6
;7-0:Backdoor Key 6
FCF_BACKDOOR_KEY6  EQU  0xFF
;-----------------------------------------------------
;FCF Backdoor Comparison Key 7
;7-0:Backdoor Key 7
FCF_BACKDOOR_KEY7  EQU  0xFF
;-----------------------------------------------------
;FCF Flash nonvolatile option byte (FCF_FOPT)
;Allows user to customize operation of the MCU at boot time.
;7-6:11:(reserved)
;  5: 1:FAST_INIT=fast initialization
;4,0:11:LPBOOT=core and system clock divider:  2^(3-LPBOOT)
;  3: 1:RESET_PIN_CFG=enable reset pin following POR
;  2: 1:NMI_DIS=Enable NMI
;  1: 1:(reserved)
;  0:(see bit 4 above)
FCF_FOPT  EQU  0xFF
;-----------------------------------------------------
;FCF Program flash protection bytes (FCF_FPROT)
;Each program flash region can be protected from program and erase 
;operation by setting the associated PROT bit.  Each bit protects a 
;1/32 region of the program flash memory.
;FCF FPROT0
;7:1:FCF_PROT7=Program flash region 7/32 not protected
;6:1:FCF_PROT6=Program flash region 6/32 not protected
;5:1:FCF_PROT5=Program flash region 5/32 not protected
;4:1:FCF_PROT4=Program flash region 4/32 not protected
;3:1:FCF_PROT3=Program flash region 3/32 not protected
;2:1:FCF_PROT2=Program flash region 2/32 not protected
;1:1:FCF_PROT1=Program flash region 1/32 not protected
;0:1:FCF_PROT0=Program flash region 0/32 not protected
FCF_FPROT0  EQU  0xFF
;-----------------------------------------------------
;FCF FPROT1
;7:1:FCF_PROT15=Program flash region 15/32 not protected
;6:1:FCF_PROT14=Program flash region 14/32 not protected
;5:1:FCF_PROT13=Program flash region 13/32 not protected
;4:1:FCF_PROT12=Program flash region 12/32 not protected
;3:1:FCF_PROT11=Program flash region 11/32 not protected
;2:1:FCF_PROT10=Program flash region 10/32 not protected
;1:1:FCF_PROT9=Program flash region 9/32 not protected
;0:1:FCF_PROT8=Program flash region 8/32 not protected
FCF_FPROT1  EQU  0xFF
;-----------------------------------------------------
;FCF FPROT2
;7:1:FCF_PROT23=Program flash region 23/32 not protected
;6:1:FCF_PROT22=Program flash region 22/32 not protected
;5:1:FCF_PROT21=Program flash region 21/32 not protected
;4:1:FCF_PROT20=Program flash region 20/32 not protected
;3:1:FCF_PROT19=Program flash region 19/32 not protected
;2:1:FCF_PROT18=Program flash region 18/32 not protected
;1:1:FCF_PROT17=Program flash region 17/32 not protected
;0:1:FCF_PROT16=Program flash region 16/32 not protected
FCF_FPROT2  EQU  0xFF
;-----------------------------------------------------
;FCF FPROT3
;7:1:FCF_PROT31=Program flash region 31/32 not protected
;6:1:FCF_PROT30=Program flash region 30/32 not protected
;5:1:FCF_PROT29=Program flash region 29/32 not protected
;4:1:FCF_PROT28=Program flash region 28/32 not protected
;3:1:FCF_PROT27=Program flash region 27/32 not protected
;2:1:FCF_PROT26=Program flash region 26/32 not protected
;1:1:FCF_PROT25=Program flash region 25/32 not protected
;0:1:FCF_PROT24=Program flash region 24/32 not protected
FCF_FPROT3  EQU  0xFF
;-----------------------------------------------------
;FCF Flash security byte (FCF_FSEC)
;WARNING: If SEC field is configured as "MCU security status is 
;secure" and MEEN field is configured as "Mass erase is disabled",
;MCU's security status cannot be set back to unsecure state since 
;mass erase via the debugger is blocked !!!
;7-6:01:KEYEN=backdoor key security enable
;            :00=Backdoor key access disabled
;            :01=Backdoor key access disabled (preferred value)
;            :10=Backdoor key access enabled
;            :11=Backdoor key access disabled
;5-4:11:MEEN=mass erase enable bits
;           (does not matter if SEC unsecure)
;           :00=mass erase enabled
;           :01=mass erase enabled
;           :10=mass erase disabled
;           :11=mass erase enabled
;3-2:11:FSLACC=Freescale failure analysis access code
;             (does not matter if SEC unsecure)
;             :00=Freescale factory access granted
;             :01=Freescale factory access denied
;             :10=Freescale factory access denied
;             :11=Freescale factory access granted
;1-0:10:SEC=flash security
;          :00=MCU secure
;          :01=MCU secure
;          :10=MCU unsecure (standard value)
;          :11=MCU secure
FCF_FSEC  EQU  0x7E
;---------------------------------------------------------------
;General-purpose input and output (GPIO)
;GPIOx_PDD: Port x Data Direction Register
;Bit n:  0=Port x pin n configured as input
;        1=Port x pin n configured as output
GPIO_BASE         EQU  0x400FF000
GPIO_PDOR_OFFSET  EQU  0x00
GPIO_PSOR_OFFSET  EQU  0x04
GPIO_PCOR_OFFSET  EQU  0x08
GPIO_PTOR_OFFSET  EQU  0x0C
GPIO_PDIR_OFFSET  EQU  0x10
GPIO_PDDR_OFFSET  EQU  0x14
GPIOA_OFFSET      EQU  0x00
GPIOB_OFFSET      EQU  0x40
GPIOC_OFFSET      EQU  0x80
GPIOD_OFFSET      EQU  0xC0
GPIOE_OFFSET      EQU  0x0100
;Port A
GPIOA_BASE        EQU  0x400FF000
GPIOA_PDOR        EQU  (GPIOA_BASE + GPIO_PDOR_OFFSET)
GPIOA_PSOR        EQU  (GPIOA_BASE + GPIO_PSOR_OFFSET)
GPIOA_PCOR        EQU  (GPIOA_BASE + GPIO_PCOR_OFFSET)
GPIOA_PTOR        EQU  (GPIOA_BASE + GPIO_PTOR_OFFSET)
GPIOA_PDIR        EQU  (GPIOA_BASE + GPIO_PDIR_OFFSET)
GPIOA_PDDR        EQU  (GPIOA_BASE + GPIO_PDDR_OFFSET)
;Port B
GPIOB_BASE         EQU  0x400FF040
GPIOB_PDOR         EQU  (GPIOB_BASE + GPIO_PDOR_OFFSET)
GPIOB_PSOR         EQU  (GPIOB_BASE + GPIO_PSOR_OFFSET)
GPIOB_PCOR         EQU  (GPIOB_BASE + GPIO_PCOR_OFFSET)
GPIOB_PTOR         EQU  (GPIOB_BASE + GPIO_PTOR_OFFSET)
GPIOB_PDIR         EQU  (GPIOB_BASE + GPIO_PDIR_OFFSET)
GPIOB_PDDR         EQU  (GPIOB_BASE + GPIO_PDDR_OFFSET)
;Port C
GPIOC_BASE         EQU  0x400FF080
GPIOC_PDOR         EQU  (GPIOC_BASE + GPIO_PDOR_OFFSET)
GPIOC_PSOR         EQU  (GPIOC_BASE + GPIO_PSOR_OFFSET)
GPIOC_PCOR         EQU  (GPIOC_BASE + GPIO_PCOR_OFFSET)
GPIOC_PTOR         EQU  (GPIOC_BASE + GPIO_PTOR_OFFSET)
GPIOC_PDIR         EQU  (GPIOC_BASE + GPIO_PDIR_OFFSET)
GPIOC_PDDR         EQU  (GPIOC_BASE + GPIO_PDDR_OFFSET)
;Port D
GPIOD_BASE         EQU  0x400FF0C0
GPIOD_PDOR         EQU  (GPIOD_BASE + GPIO_PDOR_OFFSET)
GPIOD_PSOR         EQU  (GPIOD_BASE + GPIO_PSOR_OFFSET)
GPIOD_PCOR         EQU  (GPIOD_BASE + GPIO_PCOR_OFFSET)
GPIOD_PTOR         EQU  (GPIOD_BASE + GPIO_PTOR_OFFSET)
GPIOD_PDIR         EQU  (GPIOD_BASE + GPIO_PDIR_OFFSET)
GPIOD_PDDR         EQU  (GPIOD_BASE + GPIO_PDDR_OFFSET)
;Port E
GPIOE_BASE         EQU  0x400FF100
GPIOE_PDOR         EQU  (GPIOE_BASE + GPIO_PDOR_OFFSET)
GPIOE_PSOR         EQU  (GPIOE_BASE + GPIO_PSOR_OFFSET)
GPIOE_PCOR         EQU  (GPIOE_BASE + GPIO_PCOR_OFFSET)
GPIOE_PTOR         EQU  (GPIOE_BASE + GPIO_PTOR_OFFSET)
GPIOE_PDIR         EQU  (GPIOE_BASE + GPIO_PDIR_OFFSET)
GPIOE_PDDR         EQU  (GPIOE_BASE + GPIO_PDDR_OFFSET)
;---------------------------------------------------------------
;IOPORT:  GPIO alias for zero wait state access to GPIO
;See FGPIO
;---------------------------------------------------------------
;Multipurpose clock generator (MCG)
MCG_BASE          EQU  0x40064000
MCG_C1_OFFSET     EQU  0x00
MCG_C2_OFFSET     EQU  0x01
MCG_C4_OFFSET     EQU  0x03
MCG_C5_OFFSET     EQU  0x04
MCG_C6_OFFSET     EQU  0x05
MCG_S_OFFSET      EQU  0x06
MCG_C1            EQU  (MCG_BASE + MCG_C1_OFFSET)
MCG_C2            EQU  (MCG_BASE + MCG_C2_OFFSET)
MCG_C4            EQU  (MCG_BASE + MCG_C4_OFFSET)
MCG_C5            EQU  (MCG_BASE + MCG_C5_OFFSET)
MCG_C6            EQU  (MCG_BASE + MCG_C6_OFFSET)
MCG_S             EQU  (MCG_BASE + MCG_S_OFFSET)
;---------------------------------------------------------------
;MCG_C1
;7-6:CLKS=clock source select
;        :00=output of FLL of PLL (depends on MCG_C6.PLLS)
;        :01=internal reference clock
;        :10=external reference clock
;        :11=(reserved)
;5-3:FRDIV=FLL external reference divider (depends on MCG_C2.RANGE0)
;         :first divider is for RANGE0=0
;         :second divider is for all other RANGE0 values
;         :000=  1 or   32
;         :001=  2 or   64
;         :010=  4 or  128
;         :011=  8 or  256
;         :100= 16 or  512
;         :101= 32 or 1024
;         :110= 64 or 1280
;         :111=128 or 1536
;  2:IREFS=internal reference select (for FLL)
;         :0=external reference clock
;         :1=slow internal reference clock
;  1:IRCLKEN=internal reference clock (MCGIRCLK) enable
;  0:IREFSTEN=internal reference stop enable
MCG_C1_CLKS_MASK       EQU 0xC0
MCG_C1_CLKS_SHIFT      EQU 6
MCG_C1_FRDIV_MASK      EQU 0x38
MCG_C1_FRDIV_SHIFT     EQU 3
MCG_C1_IREFS_MASK      EQU 0x04
MCG_C1_IREFS_SHIFT     EQU 2
MCG_C1_IRCLKEN_MASK    EQU 0x02
MCG_C1_IRCLKEN_SHIFT   EQU 1
MCG_C1_IREFSTEN_MASK   EQU 0x01
MCG_C1_IREFSTEN_SHIFT  EQU 0
MCG_C1_CLKS_EXT_MASK   EQU 0x80
MCG_C1_CLKS_INT_MASK   EQU 0x40
MCG_C1_CLKS_PLL_MASK   EQU 0x00
MCG_C1_FRDIV_256_MASK  EQU 0x18
MCG_C1_EXT_DIV256      EQU \
               (MCG_C1_CLKS_EXT_MASK :OR: MCG_C1_FRDIV_256_MASK)
;---------------------------------------------------------------
;MCG_C2
;  7:LOCRE0=loss of clock reset enable
;          :0=interrupt request on loss of OCS0 external reference clock
;          :1=reset request on loss of OCS0 external reference clock
;  6:Reserved; read-only; always 0
;5-4:RANGE0=frequency range select
;          :00=low frequency range for crystal oscillator
;          :01=high frequency range for crystal oscillator
;          :1X=very high frequency range for crystal oscillator
;  3:HGO0=high gain oscillator select
;        :0=low-power operation
;        :1=high-gain operation
;  2:EREFS0=external reference select
;          :0=external reference clock
;          :1=oscillator
;  1:LP=low power select
;      :0=FLL or PLL not disabled in bypass modes
;      :1=FLL or PLL disabled in bypass modes (lower power)
;  0:IRCS=internal reference clock select
;        :0=slow internal reference clock
;        :1=fast internal reference clock
MCG_C2_LOCRE0_MASK        EQU  0x80
MCG_C2_LOCRE0_SHIFT       EQU  7
MCG_C2_RANGE0_MASK        EQU  0x30
MCG_C2_RANGE0_SHIFT       EQU  4
MCG_C2_HGO0_MASK          EQU  0x08
MCG_C2_HGO0_SHIFT         EQU  3
MCG_C2_EREFS0_MASK        EQU  0x04
MCG_C2_EREFS0_SHIFT       EQU  2
MCG_C2_LP_MASK            EQU  0x02
MCG_C2_LP_SHIFT           EQU  1
MCG_C2_IRCS_MASK          EQU  0x01
MCG_C2_IRCS_SHIFT         EQU  0
MCG_C2_RANGE0_HIGH_MASK   EQU  0x10
MCG_C2_HF_LP_OSC          EQU  \
               (MCG_C2_RANGE0_HIGH_MASK :OR: MCG_C2_EREFS0_MASK)
;---------------------------------------------------------------
;MCG_C5
;  7:Reserved: read-only; always 0
;  6:PLLCLKEN0=PLL clock (MCGPLLCLK) enable
;  5:PLLSTEN0=PLL stop enable (in normal stop mode)
;4-0:PRDIV0=PLL external reference divider
;          :00000-11000=1-25 (PRDIV0 + 1)
;          :others=(reserved)
MCG_C5_PLLCLKEN0_MASK   EQU  0x40
MCG_C5_PLLCLKEN0_SHIFT  EQU  6
MCG_C5_PLLSTEN0_MASK    EQU  0x20
MCG_C5_PLLSTEN0_SHIFT   EQU  5
MCG_C5_PRDIV0_MASK      EQU  0x1F
MCG_C5_PRDIV0_SHIFT     EQU  0
MCG_C5_PRDIV0_DIV2      EQU  0x01
;---------------------------------------------------------------
;MCG_C6
;  7:LOLIE0=loss of lock interrupt enable
;  6:PLLS=PLL select
;        :0=FLL
;        :1=PLL
;  5:CME0=clock monitor enable
;4-0:VDIV0=VCO 0 divider
;         :24 + VDIV0
MCG_C6_LOLIE0_MASK    EQU  0x80
MCG_C6_LOLIE0_SHIFT   EQU  7
MCG_C6_PLLS_MASK      EQU  0x40
MCG_C6_PLLS_SHIFT     EQU  6
MCG_C6_CME0_MASK      EQU  0x20
MCG_C6_CME0_SHIFT     EQU  5
MCG_C6_VDIV0_MASK     EQU  0x1F
MCG_C6_VDIV0_SHIFT    EQU  0
MCG_C6_VDIV0_MUL24    EQU  0x00
MCG_C6_PLLS_PLL_MASK  EQU  MCG_C6_PLLS_MASK
MCG_C6_PLL_MUL24      EQU  \
                  (MCG_C6_PLLS_PLL_MASK :OR: MCG_C6_VDIV0_MUL24)
;---------------------------------------------------------------
;MCG_S
;  7:LOLS=loss of lock status
;  6:LOCK0=lock status
;  5:PLLST=PLL select status
;         :0=FLL
;         :1=PLL
;  4:IREFST=internal reference status
;          :0=FLL source external
;          :1=FLL source internal
;3-2:CLKST=clock mode status
;         :00=FLL
;         :01=internal reference
;         :10=external reference
;         :11=PLL
;  1:OSCINIT0=OSC initialization (complete)
;  0:IRCST=internal reference clock status
;         :0=slow (32 kHz)
;         :1=fast (4 MHz)
MCG_S_LOLS_MASK        EQU  0x80
MCG_S_LOLS_SHIFT       EQU  7
MCG_S_LOCK0_MASK       EQU  0x40
MCG_S_LOCK0_SHIFT      EQU  6
MCG_S_PLLST_MASK       EQU  0x20
MCG_S_PLLST_SHIFT      EQU  5
MCG_S_IREFST_MASK      EQU  0x10
MCG_S_IREFST_SHIFT     EQU  4
MCG_S_CLKST_MASK       EQU  0x0C
MCG_S_CLKST_SHIFT      EQU  2
MCG_S_OSCINIT0_MASK    EQU  0x02
MCG_S_OSCINIT0_SHIFT   EQU  1
MCG_S_IRCST_MASK       EQU  0x01
MCG_S_IRCST_SHIFT      EQU  0
MCG_S_CLKST_EXT_MASK   EQU  0x08
MCG_S_CLKST_PLL_MASK   EQU  0x0C
;---------------------------------------------------------------
;Nested vectored interrupt controller (NVIC)
;Part of system control space (SCS)
NVIC_BASE         EQU  0xE000E100
NVIC_ISER_OFFSET  EQU  0x00
NVIC_ICER_OFFSET  EQU  0x80
NVIC_ISPR_OFFSET  EQU  0x100
NVIC_ICPR_OFFSET  EQU  0x180
NVIC_IPR0_OFFSET  EQU  0x300
NVIC_IPR1_OFFSET  EQU  0x304
NVIC_IPR2_OFFSET  EQU  0x308
NVIC_IPR3_OFFSET  EQU  0x30C
NVIC_IPR4_OFFSET  EQU  0x310
NVIC_IPR5_OFFSET  EQU  0x314
NVIC_IPR6_OFFSET  EQU  0x318
NVIC_IPR7_OFFSET  EQU  0x31C
NVIC_ISER         EQU  (NVIC_BASE + NVIC_ISER_OFFSET)
NVIC_ICER         EQU  (NVIC_BASE + NVIC_ICER_OFFSET)
NVIC_ISPR         EQU  (NVIC_BASE + NVIC_ISPR_OFFSET)
NVIC_ICPR         EQU  (NVIC_BASE + NVIC_ICPR_OFFSET)
NVIC_IPR0         EQU  (NVIC_BASE + NVIC_IPR0_OFFSET)
NVIC_IPR1         EQU  (NVIC_BASE + NVIC_IPR1_OFFSET)
NVIC_IPR2         EQU  (NVIC_BASE + NVIC_IPR2_OFFSET)
NVIC_IPR3         EQU  (NVIC_BASE + NVIC_IPR3_OFFSET)
NVIC_IPR4         EQU  (NVIC_BASE + NVIC_IPR4_OFFSET)
NVIC_IPR5         EQU  (NVIC_BASE + NVIC_IPR5_OFFSET)
NVIC_IPR6         EQU  (NVIC_BASE + NVIC_IPR6_OFFSET)
NVIC_IPR7         EQU  (NVIC_BASE + NVIC_IPR7_OFFSET)
;---------------------------------------------------------------
;NVIC IPR assignments
DMA0_IPR         EQU   NVIC_IPR0  ;DMA channel 0 xfer complete/error
DMA1_IPR         EQU   NVIC_IPR0  ;DMA channel 1 xfer complete/error
DMA2_IPR         EQU   NVIC_IPR0  ;DMA channel 2 xfer complete/error
DMA3_IPR         EQU   NVIC_IPR0  ;DMA channel 3 xfer complete/error
Reserved20_IPR   EQU   NVIC_IPR1  ;(reserved)
FTFA_IPR         EQU   NVIC_IPR1  ;command complete; read collision
PMC_IPR          EQU   NVIC_IPR1  ;low-voltage detect;low-voltage warning
LLWU_IPR         EQU   NVIC_IPR1  ;low leakage wakeup
I2C0_IPR         EQU   NVIC_IPR2  ;I2C0
I2C1_IPR         EQU   NVIC_IPR2  ;I2C1
SPI0_IPR         EQU   NVIC_IPR2  ;SPI0 (all IRQ sources)
SPI1_IPR         EQU   NVIC_IPR2  ;SPI1 (all IRQ sources)
UART0_IPR        EQU   NVIC_IPR3  ;UART0 (status; error)
UART1_IPR        EQU   NVIC_IPR3  ;UART1 (status; error)
UART2_IPR        EQU   NVIC_IPR3  ;UART2 (status; error)
ADC0_IPR         EQU   NVIC_IPR3  ;ADC0
CMP0_IPR         EQU   NVIC_IPR4  ;CMP0
TMP0_IPR         EQU   NVIC_IPR4  ;TPM0
TPM1_IPR         EQU   NVIC_IPR4  ;TPM1
TPM2_IPR         EQU   NVIC_IPR4  ;TPM2
RTC_IPR          EQU   NVIC_IPR5  ;RTC (alarm)
RTC_Seconds_IPR  EQU   NVIC_IPR5  ;RTC (seconds)
PIT_IPR          EQU   NVIC_IPR5  ;PIT (all IRQ sources)
I2S0_IPR         EQU   NVIC_IPR5  ;(reserved)
USB0_IPR         EQU   NVIC_IPR6  ;USB OTG
DAC0_IPR         EQU   NVIC_IPR6  ;DAC0
TSI0_IPR         EQU   NVIC_IPR6  ;TSI0
MCG_IPR          EQU   NVIC_IPR6  ;MCG
LPTMR0_IPR       EQU   NVIC_IPR7  ;LPTMR0
LCD_IPR          EQU   NVIC_IPR7  ;LCD
PORTA_IPR        EQU   NVIC_IPR7  ;PORTA pin detect
PORTC_PORTD_IPR  EQU   NVIC_IPR7  ;PORTC and PORTD pin detect
;---------------------------------------------------------------
;NVIC IPR position
;priority is a 2-bit value (0-3)
;position EQUates are for LSB of priority
DMA0_PRI_POS         EQU    6  ;DMA channel 0 xfer complete/error
DMA1_PRI_POS         EQU   14  ;DMA channel 1 xfer complete/error
DMA2_PRI_POS         EQU   22  ;DMA channel 2 xfer complete/error
DMA3_PRI_POS         EQU   30  ;DMA channel 3 xfer complete/error
Reserved20_PRI_POS   EQU    6  ;(reserved)
FTFA_PRI_POS         EQU   14  ;command complete; read collision
PMC_PRI_POS          EQU   22  ;low-voltage detect;low-voltage warning
LLWU_PRI_POS         EQU   30  ;low leakage wakeup
I2C0_PRI_POS         EQU    6  ;I2C0
I2C1_PRI_POS         EQU   14  ;I2C1
SPI0_PRI_POS         EQU   22  ;SPI0 (all IRQ sources)
SPI1_PRI_POS         EQU   30  ;SPI1 (all IRQ sources)
UART0_PRI_POS        EQU    6  ;UART0 (status; error)
UART1_PRI_POS        EQU   14  ;UART1 (status; error)
UART2_PRI_POS        EQU   22  ;UART2 (status; error)
ADC0_PRI_POS         EQU   30  ;ADC0
CMP0_PRI_POS         EQU    6  ;CMP0
TMP0_PRI_POS         EQU   14  ;TPM0
TPM1_PRI_POS         EQU   22  ;TPM1
TPM2_PRI_POS         EQU   30  ;TPM2
RTC_PRI_POS          EQU    6  ;RTC (alarm)
RTC_Seconds_PRI_POS  EQU   14  ;RTC (seconds)
PIT_PRI_POS          EQU   22  ;PIT (all IRQ sources)
I2S0_PRI_POS         EQU   30  ;I2S0
USB0_PRI_POS         EQU    6  ;USB OTG
DAC0_PRI_POS         EQU   14  ;DAC0
TSI0_PRI_POS         EQU   22  ;TSI0
MCG_PRI_POS          EQU   30  ;MCG
LPTMR0_PRI_POS       EQU    6  ;LPTMR0
LCD_PRI_POS          EQU   14  ;LCD
PORTA_PRI_POS        EQU   22  ;PORTA pin detect
PORTC_PORTD_PRI_POS  EQU   30  ;PORTC and PORTD pin detect
;---------------------------------------------------------------
;NVIC IRQ assignments
DMA0_IRQ         EQU   00  ;DMA channel 0 xfer complete/error
DMA1_IRQ         EQU   01  ;DMA channel 1 xfer complete/error
DMA2_IRQ         EQU   02  ;DMA channel 2 xfer complete/error
DMA3_IRQ         EQU   03  ;DMA channel 3 xfer complete/error
Reserved20_IRQ   EQU   04  ;(reserved)
FTFA_IRQ         EQU   05  ;command complete; read collision
PMC_IRQ          EQU   06  ;low-voltage detect;low-voltage warning
LLWU_IRQ         EQU   07  ;low leakage wakeup
I2C0_IRQ         EQU   08  ;I2C0
I2C1_IRQ         EQU   09  ;I2C1
SPI0_IRQ         EQU   10  ;SPI0 (all IRQ sources)
SPI1_IRQ         EQU   11  ;SPI1 (all IRQ sources)
UART0_IRQ        EQU   12  ;UART0 (status; error)
UART1_IRQ        EQU   13  ;UART1 (status; error)
UART2_IRQ        EQU   14  ;UART2 (status; error)
ADC0_IRQ         EQU   15  ;ADC0
CMP0_IRQ         EQU   16  ;CMP0
TMP0_IRQ         EQU   15  ;TPM0
TPM1_IRQ         EQU   18  ;TPM1
TPM2_IRQ         EQU   19  ;TPM2
RTC_IRQ          EQU   20  ;RTC (alarm)
RTC_Seconds_IRQ  EQU   21  ;RTC (seconds)
PIT_IRQ          EQU   22  ;PIT (all IRQ sources)
I2S0_IRQ         EQU   23  ;I2S0
USB0_IRQ         EQU   24  ;USB OTG
DAC0_IRQ         EQU   25  ;DAC0
TSI0_IRQ         EQU   26  ;TSI0
MCG_IRQ          EQU   27  ;MCG
LPTMR0_IRQ       EQU   28  ;LPTMR0
LCD_IRQ          EQU   29  ;LCD
PORTA_IRQ        EQU   30  ;PORTA pin detect
PORTC_PORTD_IRQ  EQU   31  ;PORTC and PORTD pin detect
;---------------------------------------------------------------
;NVIC IRQ masks for ICER, ISER, ICPR, and ISPR
DMA0_IRQ_MASK         EQU   (1 << DMA0_IRQ       )  ;DMA channel 0 xfer complete/error
DMA1_IRQ_MASK         EQU   (1 << DMA1_IRQ       )  ;DMA channel 1 xfer complete/error
DMA2_IRQ_MASK         EQU   (1 << DMA2_IRQ       )  ;DMA channel 2 xfer complete/error
DMA3_IRQ_MASK         EQU   (1 << DMA3_IRQ       )  ;DMA channel 3 xfer complete/error
Reserved20_IRQ_MASK   EQU   (1 << Reserved20_IRQ )  ;(reserved)
FTFA_IRQ_MASK         EQU   (1 << FTFA_IRQ       )  ;command complete; read collision
PMC_IRQ_MASK          EQU   (1 << PMC_IRQ        )  ;low-voltage detect;low-voltage warning
LLWU_IRQ_MASK         EQU   (1 << LLWU_IRQ       )  ;low leakage wakeup
I2C0_IRQ_MASK         EQU   (1 << I2C0_IRQ       )  ;I2C0
I2C1_IRQ_MASK         EQU   (1 << I2C1_IRQ       )  ;I2C1
SPI0_IRQ_MASK         EQU   (1 << SPI0_IRQ       )  ;SPI0 (all IRQ sources)
SPI1_IRQ_MASK         EQU   (1 << SPI1_IRQ       )  ;SPI1 (all IRQ sources)
UART0_IRQ_MASK        EQU   (1 << UART0_IRQ      )  ;UART0 (status; error)
UART1_IRQ_MASK        EQU   (1 << UART1_IRQ      )  ;UART1 (status; error)
UART2_IRQ_MASK        EQU   (1 << UART2_IRQ      )  ;UART2 (status; error)
ADC0_IRQ_MASK         EQU   (1 << ADC0_IRQ       )  ;ADC0
CMP0_IRQ_MASK         EQU   (1 << CMP0_IRQ       )  ;CMP0
TMP0_IRQ_MASK         EQU   (1 << TMP0_IRQ       )  ;TPM0
TPM1_IRQ_MASK         EQU   (1 << TPM1_IRQ       )  ;TPM1
TPM2_IRQ_MASK         EQU   (1 << TPM2_IRQ       )  ;TPM2
RTC_IRQ_MASK          EQU   (1 << RTC_IRQ        )  ;RTC (alarm)
RTC_Seconds_IRQ_MASK  EQU   (1 << RTC_Seconds_IRQ)  ;RTC (seconds)
PIT_IRQ_MASK          EQU   (1 << PIT_IRQ        )  ;PIT (all IRQ sources)
I2S0_IRQ_MASK         EQU   (1 << I2S0_IRQ       )  ;I2S0
USB0_IRQ_MASK         EQU   (1 << USB0_IRQ       )  ;USB OTG
DAC0_IRQ_MASK         EQU   (1 << DAC0_IRQ       )  ;DAC0
TSI0_IRQ_MASK         EQU   (1 << TSI0_IRQ       )  ;TSI0
MCG_IRQ_MASK          EQU   (1 << MCG_IRQ        )  ;MCG
LPTMR0_IRQ_MASK       EQU   (1 << LPTMR0_IRQ     )  ;LPTMR0
LCD_IRQ_MASK          EQU   (1 << LCD_IRQ        )  ;LCD
PORTA_IRQ_MASK        EQU   (1 << PORTA_IRQ      )  ;PORTA pin detect
PORTC_PORTD_IRQ_MASK  EQU   (1 << PORTC_PORTD_IRQ)  ;PORTC and PORTD pin detect
;---------------------------------------------------------------
;NVIC vectors
Init_SP_Vector      EQU   00  ;end of stack
Reset_Vector        EQU   01  ;reset vector
NMI_Vector02        EQU   02  ;NMI
Hard_Fault_Vector   EQU   03  ;hard fault
Reserved04_Vector   EQU   04  ;(reserved)
Reserved05_Vector   EQU   05  ;(reserved)
Reserved06_Vector   EQU   06  ;(reserved)
Reserved07_Vector   EQU   07  ;(reserved)
Reserved08_Vector   EQU   08  ;(reserved)
Reserved09_Vector   EQU   09  ;(reserved)
Reserved10_Vector   EQU   10  ;(reserved)
SVCall_Vector       EQU   11  ;SVCall (supervisor call)
Reserved12_Vector   EQU   12  ;(reserved)
Reserved13_Vector   EQU   13  ;(reserved)
PendSR_Vector       EQU   14  ;PendableSrvReq (pendable request for system service)
SysTick_Vector      EQU   15  ;SysTick (system tick timer)
DMA0_Vector         EQU   16  ;DMA channel 0 xfer complete/error
DMA1_Vector         EQU   17  ;DMA channel 1 xfer complete/error
DMA2_Vector         EQU   18  ;DMA channel 2 xfer complete/error
DMA3_Vector         EQU   19  ;DMA channel 3 xfer complete/error
Reserved20_Vector   EQU   20  ;(reserved)
FTFA_Vector         EQU   21  ;command complete; read collision
PMC_Vector          EQU   22  ;low-voltage detect;low-voltage warning
LLWU_Vector         EQU   23  ;low leakage wakeup
I2C0_Vector         EQU   24  ;I2C0
I2C1_Vector         EQU   25  ;I2C1
SPI0_Vector         EQU   26  ;SPI0 (all IRQ sources)
SPI1_Vector         EQU   27  ;SPI1 (all IRQ sources)
UART0_Vector        EQU   28  ;UART0 (status; error)
UART1_Vector        EQU   29  ;UART1 (status; error)
UART2_Vector        EQU   30  ;UART2 (status; error)
ADC0_Vector         EQU   31  ;ADC0
CMP0_Vector         EQU   32  ;CMP0
TMP0_Vector         EQU   33  ;TPM0
TPM1_Vector         EQU   34  ;TPM1
TPM2_Vector         EQU   35  ;TPM2
RTC_Vector          EQU   36  ;RTC (alarm)
RTC_Seconds_Vector  EQU   37  ;RTC (seconds)
PIT_Vector          EQU   38  ;PIT (all IRQ sources)
I2S0_Vector         EQU   39  ;I2S0
USB0_Vector         EQU   40  ;USB OTG
DAC0_Vector         EQU   41  ;DAC0
TSI0_Vector         EQU   42  ;TSI0
MCG_Vector          EQU   43  ;MCG
LPTMR0_Vector       EQU   44  ;LPTMR0
LCD_Vector          EQU   45  ;LCD
PORTA_Vector        EQU   46  ;PORTA pin detect
PORTD_Vector        EQU   47  ;PORTD pin detect
;---------------------------------------------------------------
;PIT
;CAUTION:PIT bit numbers shown in [3] are opposite
;        If bit n is indicated, is should be bit 31 - n.
;[3] Freescale Semiconductor, <B>KL25 Sub-Family Reference Manual</B>,
;    KL25P80M48SFORM, Rev. 3, 9/2013.
PIT_BASE            EQU  0x40037000
PIT_CH0_BASE        EQU  0x40037100
PIT_CH1_BASE        EQU  0x40037110
PIT_LDVAL_OFFSET    EQU 0x00
PIT_CVAL_OFFSET     EQU 0x04
PIT_TCTRL_OFFSET    EQU 0x08
PIT_TFLG_OFFSET     EQU 0x0C
PIT_MCR_OFFSET      EQU  0x00
PIT_LTMR64H_OFFSET  EQU  0xE0
PIT_LTMR64L_OFFSET  EQU  0xE4
PIT_LDVAL0_OFFSET   EQU  0x100
PIT_CVAL0_OFFSET    EQU  0x104
PIT_TCTRL0_OFFSET   EQU  0x108
PIT_TFLG0_OFFSET    EQU  0x10C
PIT_LDVAL2_OFFSET   EQU  0x110
PIT_CVAL2_OFFSET    EQU  0x114
PIT_TCTRL2_OFFSET   EQU  0x118
PIT_TFLG2_OFFSET    EQU  0x11C
PIT_MCR      EQU  (PIT_BASE + PIT_MCR_OFFSET)
PIT_LTMR64H  EQU  (PIT_BASE + PIT_LTMR64H_OFFSET)
PIT_LTMR64L  EQU  (PIT_BASE + PIT_LTMR64L_OFFSET)
PIT_LDVAL0   EQU  (PIT_BASE + PIT_LDVAL0_OFFSET)
PIT_CVAL0    EQU  (PIT_BASE + PIT_CVAL0_OFFSET)
PIT_TCTRL0   EQU  (PIT_BASE + PIT_TCTRL0_OFFSET)
PIT_TFLG0    EQU  (PIT_BASE + PIT_TFLG0_OFFSET)
PIT_LDVAL2   EQU  (PIT_BASE + PIT_LDVAL2_OFFSET)
PIT_CVAL2    EQU  (PIT_BASE + PIT_CVAL2_OFFSET)
PIT_TCTRL2   EQU  (PIT_BASE + PIT_TCTRL2_OFFSET)
PIT_TFLG2    EQU  (PIT_BASE + PIT_TFLG2_OFFSET)
;---------------------------------------------------------------
;PIT_CVALn:  current timer value register (channel n)
;31-0:TVL=current timer value
;---------------------------------------------------------------
;PIT_LDVALn:  timer load value register (channel n)
;31-0:TSV=timer start value
;         PIT chan. n counts down from this value to 0,
;         then sets TIF and loads LDVALn
;---------------------------------------------------------------
;PIT_LTMR64H:  PIT upper lifetime timer register
;for applications chaining timer 0 and timer 1 for 64-bit timer
;31-0:LTH=life timer value (high word)
;         value of timer 1 (CVAL1); read before PIT_LTMR64L
;---------------------------------------------------------------
;PIT_LTMR64L:  PIT lower lifetime timer register
;for applications chaining timer 0 and timer 1 for 64-bit timer
;31-0:LTL=life timer value (low word)
;         value of timer 0 (CVAL0); read after PIT_LTMR64H
;---------------------------------------------------------------
;PIT_MCR:  PIT module control register
;31-3:(reserved):read-only:0
;   2:(reserved)
;   1:MDIS=module disable (PIT section)
;          RTI timer not affected by this field
;          must be enabled before any other setup
;   0:FRZ=freeze:  continue'/stop timers in debug mode
PIT_MCR_MDIS_MASK   EQU  0x00000002
PIT_MCR_MDIS_SHIFT  EQU  1
PIT_MCR_FRZ_MASK    EQU  0x00000001
PIT_MCR_FRZ_SHIFT   EQU  0
;---------------------------------------------------------------
;PIT_TCTRLn:  timer control register (channel n)
;31-3:(reserved):read-only:0
;   2:CHN=chain mode (enable)
;          in chain mode, channel n-1 must expire before
;                         channel n counts
;          timer 0 cannot be changed
;   1:TIE=timer interrupt enable (on TIF)
;   0:TEN=timer enable
PIT_TCTRL_CHN_MASK   EQU  0x00000004
PIT_TCTRL_CHN_SHIFT  EQU  2
PIT_TCTRL_TIE_MASK   EQU  0x00000002
PIT_TCTRL_TIE_SHIFT  EQU  1
PIT_TCTRL_TEN_MASK   EQU  0x00000001
PIT_TCTRL_TEN_SHIFT  EQU  0
;---------------------------------------------------------------
;PIT_TFLGn:  timer flag register (channel n)
;31-1:(reserved):read-only:0
;   0:TIF=timer interrupt flag
;         write 1 to clear
PIT_TFLG_TIF_MASK   EQU  0x00000001
PIT_TFLG_TIF_SHIFT  EQU  0
;---------------------------------------------------------------
;PORTx_PCRn (Port x pin control register n [for pin n])
;31-25:(reserved):read-only:0
;   24:ISF=interrupt status flag; write 1 clears
;23-20:(reserved):read-only:0
;19-16:IRCQ=interrupt configuration
;          :0000=interrupt/DMA request disabled
;          :0001=DMA request on rising edge
;          :0010=DMA request on falling edge
;          :0011=DMA request on either edge
;          :1000=interrupt when logic zero
;          :1001=interrupt on rising edge
;          :1010=interrupt on falling edge
;          :1011=interrupt on either edge
;          :1100=interrupt when logic one
;          :others=reserved
;15-11:(reserved):read-only:0
;10-08:MUX=Pin mux control
;         :000=pin disabled (analog)
;         :001=alternative 1 (GPIO)
;         :010-111=alternatives 2-7 (chip-specific)
;    7:(reserved):read-only:0
;    6:DSE=Drive strength enable
;         :0=low
;         :1=high
;    5:(reserved):read-only:0
;    4:PFE=Passive filter enable
;    3:(reserved):read-only:0
;    2:SRE=Slew rate enable
;         :0=fast
;         :1=slow
;    1:PE=Pull enable
;    0:PS=Pull select (if PE=1)
;        :0=internal pulldown
;        :1=internal pullup
PORT_PCR_ISF_MASK           EQU  0x01000000
PORT_PCR_ISF_SHIFT          EQU  24
PORT_PCR_IRCQ_MASK          EQU  0x000F0000
PORT_PCR_IRCQ_SHIFT         EQU  16
PORT_PCR_MUX_MASK           EQU  0x00000700
PORT_PCR_MUX_SHIFT          EQU  8
PORT_PCR_DSE_MASK           EQU  0x40
PORT_PCR_DSE_SHIFT          EQU  6
PORT_PCR_PFE_MASK           EQU  0x10
PORT_PCR_PFE_SHIFT          EQU  4
PORT_PCR_SRE_MASK           EQU  0x04
PORT_PCR_SRE_SHIFT          EQU  2
PORT_PCR_PE_MASK            EQU  0x02
PORT_PCR_PE_SHIFT           EQU  1
PORT_PCR_PS_MASK            EQU  0x01
PORT_PCR_PS_SHIFT           EQU  0
PORT_PCR_MUX_SELECT_0_MASK  EQU  0x00000000 ;analog
PORT_PCR_MUX_SELECT_1_MASK  EQU  0x00000100 ;GPIO
PORT_PCR_MUX_SELECT_2_MASK  EQU  0x00000200
PORT_PCR_MUX_SELECT_3_MASK  EQU  0x00000300
PORT_PCR_MUX_SELECT_4_MASK  EQU  0x00000400
PORT_PCR_MUX_SELECT_5_MASK  EQU  0x00000500
PORT_PCR_MUX_SELECT_6_MASK  EQU  0x00000600
PORT_PCR_MUX_SELECT_7_MASK  EQU  0x00000700
;---------------------------------------------------------------
;Port A
PORTA_BASE         EQU  0x40049000
PORTA_PCR0_OFFSET  EQU  0x00
PORTA_PCR1_OFFSET  EQU  0x04
PORTA_PCR2_OFFSET  EQU  0x08
PORTA_PCR3_OFFSET  EQU  0x0C
PORTA_PCR4_OFFSET  EQU  0x10
PORTA_PCR5_OFFSET  EQU  0x14
PORTA_PCR6_OFFSET  EQU  0x18
PORTA_PCR7_OFFSET  EQU  0x1C
PORTA_PCR8_OFFSET  EQU  0x20
PORTA_PCR9_OFFSET  EQU  0x24
PORTA_PCR10_OFFSET EQU  0x28
PORTA_PCR11_OFFSET EQU  0x2C
PORTA_PCR12_OFFSET EQU  0x30
PORTA_PCR13_OFFSET EQU  0x34
PORTA_PCR14_OFFSET EQU  0x38
PORTA_PCR15_OFFSET EQU  0x3C
PORTA_PCR16_OFFSET EQU  0x40
PORTA_PCR17_OFFSET EQU  0x44
PORTA_PCR18_OFFSET EQU  0x48
PORTA_PCR19_OFFSET EQU  0x4C
PORTA_PCR20_OFFSET EQU  0x50
PORTA_PCR21_OFFSET EQU  0x54
PORTA_PCR22_OFFSET EQU  0x58
PORTA_PCR23_OFFSET EQU  0x5C
PORTA_PCR24_OFFSET EQU  0x60
PORTA_PCR25_OFFSET EQU  0x64
PORTA_PCR26_OFFSET EQU  0x68
PORTA_PCR27_OFFSET EQU  0x6C
PORTA_PCR28_OFFSET EQU  0x70
PORTA_PCR29_OFFSET EQU  0x74
PORTA_PCR30_OFFSET EQU  0x78
PORTA_PCR31_OFFSET EQU  0x7C
PORTA_GPCLR_OFFSET EQU  0x80
PORTA_GPCHR_OFFSET EQU  0x84
PORTA_ISFR_OFFSET  EQU  0xA0
PORTA_PCR0         EQU  (PORTA_BASE + PORTA_PCR0_OFFSET)
PORTA_PCR1         EQU  (PORTA_BASE + PORTA_PCR1_OFFSET)
PORTA_PCR2         EQU  (PORTA_BASE + PORTA_PCR2_OFFSET)
PORTA_PCR3         EQU  (PORTA_BASE + PORTA_PCR3_OFFSET)
PORTA_PCR4         EQU  (PORTA_BASE + PORTA_PCR4_OFFSET)
PORTA_PCR5         EQU  (PORTA_BASE + PORTA_PCR5_OFFSET)
PORTA_PCR6         EQU  (PORTA_BASE + PORTA_PCR6_OFFSET)
PORTA_PCR7         EQU  (PORTA_BASE + PORTA_PCR7_OFFSET)
PORTA_PCR8         EQU  (PORTA_BASE + PORTA_PCR8_OFFSET)
PORTA_PCR9         EQU  (PORTA_BASE + PORTA_PCR9_OFFSET)
PORTA_PCR10        EQU  (PORTA_BASE + PORTA_PCR10_OFFSET)
PORTA_PCR11        EQU  (PORTA_BASE + PORTA_PCR11_OFFSET)
PORTA_PCR12        EQU  (PORTA_BASE + PORTA_PCR12_OFFSET)
PORTA_PCR13        EQU  (PORTA_BASE + PORTA_PCR13_OFFSET)
PORTA_PCR14        EQU  (PORTA_BASE + PORTA_PCR14_OFFSET)
PORTA_PCR15        EQU  (PORTA_BASE + PORTA_PCR15_OFFSET)
PORTA_PCR16        EQU  (PORTA_BASE + PORTA_PCR16_OFFSET)
PORTA_PCR17        EQU  (PORTA_BASE + PORTA_PCR17_OFFSET)
PORTA_PCR18        EQU  (PORTA_BASE + PORTA_PCR18_OFFSET)
PORTA_PCR19        EQU  (PORTA_BASE + PORTA_PCR19_OFFSET)
PORTA_PCR20        EQU  (PORTA_BASE + PORTA_PCR20_OFFSET)
PORTA_PCR21        EQU  (PORTA_BASE + PORTA_PCR21_OFFSET)
PORTA_PCR22        EQU  (PORTA_BASE + PORTA_PCR22_OFFSET)
PORTA_PCR23        EQU  (PORTA_BASE + PORTA_PCR23_OFFSET)
PORTA_PCR24        EQU  (PORTA_BASE + PORTA_PCR24_OFFSET)
PORTA_PCR25        EQU  (PORTA_BASE + PORTA_PCR25_OFFSET)
PORTA_PCR26        EQU  (PORTA_BASE + PORTA_PCR26_OFFSET)
PORTA_PCR27        EQU  (PORTA_BASE + PORTA_PCR27_OFFSET)
PORTA_PCR28        EQU  (PORTA_BASE + PORTA_PCR28_OFFSET)
PORTA_PCR29        EQU  (PORTA_BASE + PORTA_PCR29_OFFSET)
PORTA_PCR30        EQU  (PORTA_BASE + PORTA_PCR30_OFFSET)
PORTA_PCR31        EQU  (PORTA_BASE + PORTA_PCR31_OFFSET)
PORTA_GPCLR        EQU  (PORTA_BASE + PORTA_GPCLR_OFFSET)
PORTA_GPCHR        EQU  (PORTA_BASE + PORTA_GPCHR_OFFSET)
PORTA_ISFR         EQU  (PORTA_BASE + PORTA_ISFR_OFFSET)
;---------------------------------------------------------------
;Port B
PORTB_BASE         EQU  0x4004A000
PORTB_PCR0_OFFSET  EQU  0x00
PORTB_PCR1_OFFSET  EQU  0x04
PORTB_PCR2_OFFSET  EQU  0x08
PORTB_PCR3_OFFSET  EQU  0x0C
PORTB_PCR4_OFFSET  EQU  0x10
PORTB_PCR5_OFFSET  EQU  0x14
PORTB_PCR6_OFFSET  EQU  0x18
PORTB_PCR7_OFFSET  EQU  0x1C
PORTB_PCR8_OFFSET  EQU  0x20
PORTB_PCR9_OFFSET  EQU  0x24
PORTB_PCR10_OFFSET EQU  0x28
PORTB_PCR11_OFFSET EQU  0x2C
PORTB_PCR12_OFFSET EQU  0x30
PORTB_PCR13_OFFSET EQU  0x34
PORTB_PCR14_OFFSET EQU  0x38
PORTB_PCR15_OFFSET EQU  0x3C
PORTB_PCR16_OFFSET EQU  0x40
PORTB_PCR17_OFFSET EQU  0x44
PORTB_PCR18_OFFSET EQU  0x48
PORTB_PCR19_OFFSET EQU  0x4C
PORTB_PCR20_OFFSET EQU  0x50
PORTB_PCR21_OFFSET EQU  0x54
PORTB_PCR22_OFFSET EQU  0x58
PORTB_PCR23_OFFSET EQU  0x5C
PORTB_PCR24_OFFSET EQU  0x60
PORTB_PCR25_OFFSET EQU  0x64
PORTB_PCR26_OFFSET EQU  0x68
PORTB_PCR27_OFFSET EQU  0x6C
PORTB_PCR28_OFFSET EQU  0x70
PORTB_PCR29_OFFSET EQU  0x74
PORTB_PCR30_OFFSET EQU  0x78
PORTB_PCR31_OFFSET EQU  0x7C
PORTB_GPCLR_OFFSET EQU  0x80
PORTB_GPCHR_OFFSET EQU  0x84
PORTB_ISFR_OFFSET  EQU  0xA0
PORTB_PCR0         EQU  (PORTB_BASE + PORTB_PCR0_OFFSET)
PORTB_PCR1         EQU  (PORTB_BASE + PORTB_PCR1_OFFSET)
PORTB_PCR2         EQU  (PORTB_BASE + PORTB_PCR2_OFFSET)
PORTB_PCR3         EQU  (PORTB_BASE + PORTB_PCR3_OFFSET)
PORTB_PCR4         EQU  (PORTB_BASE + PORTB_PCR4_OFFSET)
PORTB_PCR5         EQU  (PORTB_BASE + PORTB_PCR5_OFFSET)
PORTB_PCR6         EQU  (PORTB_BASE + PORTB_PCR6_OFFSET)
PORTB_PCR7         EQU  (PORTB_BASE + PORTB_PCR7_OFFSET)
PORTB_PCR8         EQU  (PORTB_BASE + PORTB_PCR8_OFFSET)
PORTB_PCR9         EQU  (PORTB_BASE + PORTB_PCR9_OFFSET)
PORTB_PCR10        EQU  (PORTB_BASE + PORTB_PCR10_OFFSET)
PORTB_PCR11        EQU  (PORTB_BASE + PORTB_PCR11_OFFSET)
PORTB_PCR12        EQU  (PORTB_BASE + PORTB_PCR12_OFFSET)
PORTB_PCR13        EQU  (PORTB_BASE + PORTB_PCR13_OFFSET)
PORTB_PCR14        EQU  (PORTB_BASE + PORTB_PCR14_OFFSET)
PORTB_PCR15        EQU  (PORTB_BASE + PORTB_PCR15_OFFSET)
PORTB_PCR16        EQU  (PORTB_BASE + PORTB_PCR16_OFFSET)
PORTB_PCR17        EQU  (PORTB_BASE + PORTB_PCR17_OFFSET)
PORTB_PCR18        EQU  (PORTB_BASE + PORTB_PCR18_OFFSET)
PORTB_PCR19        EQU  (PORTB_BASE + PORTB_PCR19_OFFSET)
PORTB_PCR20        EQU  (PORTB_BASE + PORTB_PCR20_OFFSET)
PORTB_PCR21        EQU  (PORTB_BASE + PORTB_PCR21_OFFSET)
PORTB_PCR22        EQU  (PORTB_BASE + PORTB_PCR22_OFFSET)
PORTB_PCR23        EQU  (PORTB_BASE + PORTB_PCR23_OFFSET)
PORTB_PCR24        EQU  (PORTB_BASE + PORTB_PCR24_OFFSET)
PORTB_PCR25        EQU  (PORTB_BASE + PORTB_PCR25_OFFSET)
PORTB_PCR26        EQU  (PORTB_BASE + PORTB_PCR26_OFFSET)
PORTB_PCR27        EQU  (PORTB_BASE + PORTB_PCR27_OFFSET)
PORTB_PCR28        EQU  (PORTB_BASE + PORTB_PCR28_OFFSET)
PORTB_PCR29        EQU  (PORTB_BASE + PORTB_PCR29_OFFSET)
PORTB_PCR30        EQU  (PORTB_BASE + PORTB_PCR30_OFFSET)
PORTB_PCR31        EQU  (PORTB_BASE + PORTB_PCR31_OFFSET)
PORTB_GPCLR        EQU  (PORTB_BASE + PORTB_GPCLR_OFFSET)
PORTB_GPCHR        EQU  (PORTB_BASE + PORTB_GPCHR_OFFSET)
PORTB_ISFR         EQU  (PORTB_BASE + PORTB_ISFR_OFFSET)
;---------------------------------------------------------------
;Port C
PORTC_BASE         EQU  0x4004B000
PORTC_PCR0_OFFSET  EQU  0x00
PORTC_PCR1_OFFSET  EQU  0x04
PORTC_PCR2_OFFSET  EQU  0x08
PORTC_PCR3_OFFSET  EQU  0x0C
PORTC_PCR4_OFFSET  EQU  0x10
PORTC_PCR5_OFFSET  EQU  0x14
PORTC_PCR6_OFFSET  EQU  0x18
PORTC_PCR7_OFFSET  EQU  0x1C
PORTC_PCR8_OFFSET  EQU  0x20
PORTC_PCR9_OFFSET  EQU  0x24
PORTC_PCR10_OFFSET EQU  0x28
PORTC_PCR11_OFFSET EQU  0x2C
PORTC_PCR12_OFFSET EQU  0x30
PORTC_PCR13_OFFSET EQU  0x34
PORTC_PCR14_OFFSET EQU  0x38
PORTC_PCR15_OFFSET EQU  0x3C
PORTC_PCR16_OFFSET EQU  0x40
PORTC_PCR17_OFFSET EQU  0x44
PORTC_PCR18_OFFSET EQU  0x48
PORTC_PCR19_OFFSET EQU  0x4C
PORTC_PCR20_OFFSET EQU  0x50
PORTC_PCR21_OFFSET EQU  0x54
PORTC_PCR22_OFFSET EQU  0x58
PORTC_PCR23_OFFSET EQU  0x5C
PORTC_PCR24_OFFSET EQU  0x60
PORTC_PCR25_OFFSET EQU  0x64
PORTC_PCR26_OFFSET EQU  0x68
PORTC_PCR27_OFFSET EQU  0x6C
PORTC_PCR28_OFFSET EQU  0x70
PORTC_PCR29_OFFSET EQU  0x74
PORTC_PCR30_OFFSET EQU  0x78
PORTC_PCR31_OFFSET EQU  0x7C
PORTC_GPCLR_OFFSET EQU  0x80
PORTC_GPCHR_OFFSET EQU  0x84
PORTC_ISFR_OFFSET  EQU  0xA0
PORTC_PCR0         EQU  (PORTC_BASE + PORTC_PCR0_OFFSET)
PORTC_PCR1         EQU  (PORTC_BASE + PORTC_PCR1_OFFSET)
PORTC_PCR2         EQU  (PORTC_BASE + PORTC_PCR2_OFFSET)
PORTC_PCR3         EQU  (PORTC_BASE + PORTC_PCR3_OFFSET)
PORTC_PCR4         EQU  (PORTC_BASE + PORTC_PCR4_OFFSET)
PORTC_PCR5         EQU  (PORTC_BASE + PORTC_PCR5_OFFSET)
PORTC_PCR6         EQU  (PORTC_BASE + PORTC_PCR6_OFFSET)
PORTC_PCR7         EQU  (PORTC_BASE + PORTC_PCR7_OFFSET)
PORTC_PCR8         EQU  (PORTC_BASE + PORTC_PCR8_OFFSET)
PORTC_PCR9         EQU  (PORTC_BASE + PORTC_PCR9_OFFSET)
PORTC_PCR10        EQU  (PORTC_BASE + PORTC_PCR10_OFFSET)
PORTC_PCR11        EQU  (PORTC_BASE + PORTC_PCR11_OFFSET)
PORTC_PCR12        EQU  (PORTC_BASE + PORTC_PCR12_OFFSET)
PORTC_PCR13        EQU  (PORTC_BASE + PORTC_PCR13_OFFSET)
PORTC_PCR14        EQU  (PORTC_BASE + PORTC_PCR14_OFFSET)
PORTC_PCR15        EQU  (PORTC_BASE + PORTC_PCR15_OFFSET)
PORTC_PCR16        EQU  (PORTC_BASE + PORTC_PCR16_OFFSET)
PORTC_PCR17        EQU  (PORTC_BASE + PORTC_PCR17_OFFSET)
PORTC_PCR18        EQU  (PORTC_BASE + PORTC_PCR18_OFFSET)
PORTC_PCR19        EQU  (PORTC_BASE + PORTC_PCR19_OFFSET)
PORTC_PCR20        EQU  (PORTC_BASE + PORTC_PCR20_OFFSET)
PORTC_PCR21        EQU  (PORTC_BASE + PORTC_PCR21_OFFSET)
PORTC_PCR22        EQU  (PORTC_BASE + PORTC_PCR22_OFFSET)
PORTC_PCR23        EQU  (PORTC_BASE + PORTC_PCR23_OFFSET)
PORTC_PCR24        EQU  (PORTC_BASE + PORTC_PCR24_OFFSET)
PORTC_PCR25        EQU  (PORTC_BASE + PORTC_PCR25_OFFSET)
PORTC_PCR26        EQU  (PORTC_BASE + PORTC_PCR26_OFFSET)
PORTC_PCR27        EQU  (PORTC_BASE + PORTC_PCR27_OFFSET)
PORTC_PCR28        EQU  (PORTC_BASE + PORTC_PCR28_OFFSET)
PORTC_PCR29        EQU  (PORTC_BASE + PORTC_PCR29_OFFSET)
PORTC_PCR30        EQU  (PORTC_BASE + PORTC_PCR30_OFFSET)
PORTC_PCR31        EQU  (PORTC_BASE + PORTC_PCR31_OFFSET)
PORTC_GPCLR        EQU  (PORTC_BASE + PORTC_GPCLR_OFFSET)
PORTC_GPCHR        EQU  (PORTC_BASE + PORTC_GPCHR_OFFSET)
PORTC_ISFR         EQU  (PORTC_BASE + PORTC_ISFR_OFFSET)
;---------------------------------------------------------------
;Port D
PORTD_BASE         EQU  0x4004C000
PORTD_PCR0_OFFSET  EQU  0x00
PORTD_PCR1_OFFSET  EQU  0x04
PORTD_PCR2_OFFSET  EQU  0x08
PORTD_PCR3_OFFSET  EQU  0x0C
PORTD_PCR4_OFFSET  EQU  0x10
PORTD_PCR5_OFFSET  EQU  0x14
PORTD_PCR6_OFFSET  EQU  0x18
PORTD_PCR7_OFFSET  EQU  0x1C
PORTD_PCR8_OFFSET  EQU  0x20
PORTD_PCR9_OFFSET  EQU  0x24
PORTD_PCR10_OFFSET EQU  0x28
PORTD_PCR11_OFFSET EQU  0x2C
PORTD_PCR12_OFFSET EQU  0x30
PORTD_PCR13_OFFSET EQU  0x34
PORTD_PCR14_OFFSET EQU  0x38
PORTD_PCR15_OFFSET EQU  0x3C
PORTD_PCR16_OFFSET EQU  0x40
PORTD_PCR17_OFFSET EQU  0x44
PORTD_PCR18_OFFSET EQU  0x48
PORTD_PCR19_OFFSET EQU  0x4C
PORTD_PCR20_OFFSET EQU  0x50
PORTD_PCR21_OFFSET EQU  0x54
PORTD_PCR22_OFFSET EQU  0x58
PORTD_PCR23_OFFSET EQU  0x5C
PORTD_PCR24_OFFSET EQU  0x60
PORTD_PCR25_OFFSET EQU  0x64
PORTD_PCR26_OFFSET EQU  0x68
PORTD_PCR27_OFFSET EQU  0x6C
PORTD_PCR28_OFFSET EQU  0x70
PORTD_PCR29_OFFSET EQU  0x74
PORTD_PCR30_OFFSET EQU  0x78
PORTD_PCR31_OFFSET EQU  0x7C
PORTD_GPCLR_OFFSET EQU  0x80
PORTD_GPCHR_OFFSET EQU  0x84
PORTD_ISFR_OFFSET  EQU  0xA0
PORTD_PCR0         EQU  (PORTD_BASE + PORTD_PCR0_OFFSET)
PORTD_PCR1         EQU  (PORTD_BASE + PORTD_PCR1_OFFSET)
PORTD_PCR2         EQU  (PORTD_BASE + PORTD_PCR2_OFFSET)
PORTD_PCR3         EQU  (PORTD_BASE + PORTD_PCR3_OFFSET)
PORTD_PCR4         EQU  (PORTD_BASE + PORTD_PCR4_OFFSET)
PORTD_PCR5         EQU  (PORTD_BASE + PORTD_PCR5_OFFSET)
PORTD_PCR6         EQU  (PORTD_BASE + PORTD_PCR6_OFFSET)
PORTD_PCR7         EQU  (PORTD_BASE + PORTD_PCR7_OFFSET)
PORTD_PCR8         EQU  (PORTD_BASE + PORTD_PCR8_OFFSET)
PORTD_PCR9         EQU  (PORTD_BASE + PORTD_PCR9_OFFSET)
PORTD_PCR10        EQU  (PORTD_BASE + PORTD_PCR10_OFFSET)
PORTD_PCR11        EQU  (PORTD_BASE + PORTD_PCR11_OFFSET)
PORTD_PCR12        EQU  (PORTD_BASE + PORTD_PCR12_OFFSET)
PORTD_PCR13        EQU  (PORTD_BASE + PORTD_PCR13_OFFSET)
PORTD_PCR14        EQU  (PORTD_BASE + PORTD_PCR14_OFFSET)
PORTD_PCR15        EQU  (PORTD_BASE + PORTD_PCR15_OFFSET)
PORTD_PCR16        EQU  (PORTD_BASE + PORTD_PCR16_OFFSET)
PORTD_PCR17        EQU  (PORTD_BASE + PORTD_PCR17_OFFSET)
PORTD_PCR18        EQU  (PORTD_BASE + PORTD_PCR18_OFFSET)
PORTD_PCR19        EQU  (PORTD_BASE + PORTD_PCR19_OFFSET)
PORTD_PCR20        EQU  (PORTD_BASE + PORTD_PCR20_OFFSET)
PORTD_PCR21        EQU  (PORTD_BASE + PORTD_PCR21_OFFSET)
PORTD_PCR22        EQU  (PORTD_BASE + PORTD_PCR22_OFFSET)
PORTD_PCR23        EQU  (PORTD_BASE + PORTD_PCR23_OFFSET)
PORTD_PCR24        EQU  (PORTD_BASE + PORTD_PCR24_OFFSET)
PORTD_PCR25        EQU  (PORTD_BASE + PORTD_PCR25_OFFSET)
PORTD_PCR26        EQU  (PORTD_BASE + PORTD_PCR26_OFFSET)
PORTD_PCR27        EQU  (PORTD_BASE + PORTD_PCR27_OFFSET)
PORTD_PCR28        EQU  (PORTD_BASE + PORTD_PCR28_OFFSET)
PORTD_PCR29        EQU  (PORTD_BASE + PORTD_PCR29_OFFSET)
PORTD_PCR30        EQU  (PORTD_BASE + PORTD_PCR30_OFFSET)
PORTD_PCR31        EQU  (PORTD_BASE + PORTD_PCR31_OFFSET)
PORTD_GPCLR        EQU  (PORTD_BASE + PORTD_GPCLR_OFFSET)
PORTD_GPCHR        EQU  (PORTD_BASE + PORTD_GPCHR_OFFSET)
PORTD_ISFR         EQU  (PORTD_BASE + PORTD_ISFR_OFFSET)
;---------------------------------------------------------------
;Port E
PORTE_BASE         EQU  0x4004D000
PORTE_PCR0_OFFSET  EQU  0x00
PORTE_PCR1_OFFSET  EQU  0x04
PORTE_PCR2_OFFSET  EQU  0x08
PORTE_PCR3_OFFSET  EQU  0x0C
PORTE_PCR4_OFFSET  EQU  0x10
PORTE_PCR5_OFFSET  EQU  0x14
PORTE_PCR6_OFFSET  EQU  0x18
PORTE_PCR7_OFFSET  EQU  0x1C
PORTE_PCR8_OFFSET  EQU  0x20
PORTE_PCR9_OFFSET  EQU  0x24
PORTE_PCR10_OFFSET EQU  0x28
PORTE_PCR11_OFFSET EQU  0x2C
PORTE_PCR12_OFFSET EQU  0x30
PORTE_PCR13_OFFSET EQU  0x34
PORTE_PCR14_OFFSET EQU  0x38
PORTE_PCR15_OFFSET EQU  0x3C
PORTE_PCR16_OFFSET EQU  0x40
PORTE_PCR17_OFFSET EQU  0x44
PORTE_PCR18_OFFSET EQU  0x48
PORTE_PCR19_OFFSET EQU  0x4C
PORTE_PCR20_OFFSET EQU  0x50
PORTE_PCR21_OFFSET EQU  0x54
PORTE_PCR22_OFFSET EQU  0x58
PORTE_PCR23_OFFSET EQU  0x5C
PORTE_PCR24_OFFSET EQU  0x60
PORTE_PCR25_OFFSET EQU  0x64
PORTE_PCR26_OFFSET EQU  0x68
PORTE_PCR27_OFFSET EQU  0x6C
PORTE_PCR28_OFFSET EQU  0x70
PORTE_PCR29_OFFSET EQU  0x74
PORTE_PCR30_OFFSET EQU  0x78
PORTE_PCR31_OFFSET EQU  0x7C
PORTE_GPCLR_OFFSET EQU  0x80
PORTE_GPCHR_OFFSET EQU  0x84
PORTE_ISFR_OFFSET  EQU  0xA0
PORTE_PCR0         EQU  (PORTE_BASE + PORTE_PCR0_OFFSET)
PORTE_PCR1         EQU  (PORTE_BASE + PORTE_PCR1_OFFSET)
PORTE_PCR2         EQU  (PORTE_BASE + PORTE_PCR2_OFFSET)
PORTE_PCR3         EQU  (PORTE_BASE + PORTE_PCR3_OFFSET)
PORTE_PCR4         EQU  (PORTE_BASE + PORTE_PCR4_OFFSET)
PORTE_PCR5         EQU  (PORTE_BASE + PORTE_PCR5_OFFSET)
PORTE_PCR6         EQU  (PORTE_BASE + PORTE_PCR6_OFFSET)
PORTE_PCR7         EQU  (PORTE_BASE + PORTE_PCR7_OFFSET)
PORTE_PCR8         EQU  (PORTE_BASE + PORTE_PCR8_OFFSET)
PORTE_PCR9         EQU  (PORTE_BASE + PORTE_PCR9_OFFSET)
PORTE_PCR10        EQU  (PORTE_BASE + PORTE_PCR10_OFFSET)
PORTE_PCR11        EQU  (PORTE_BASE + PORTE_PCR11_OFFSET)
PORTE_PCR12        EQU  (PORTE_BASE + PORTE_PCR12_OFFSET)
PORTE_PCR13        EQU  (PORTE_BASE + PORTE_PCR13_OFFSET)
PORTE_PCR14        EQU  (PORTE_BASE + PORTE_PCR14_OFFSET)
PORTE_PCR15        EQU  (PORTE_BASE + PORTE_PCR15_OFFSET)
PORTE_PCR16        EQU  (PORTE_BASE + PORTE_PCR16_OFFSET)
PORTE_PCR17        EQU  (PORTE_BASE + PORTE_PCR17_OFFSET)
PORTE_PCR18        EQU  (PORTE_BASE + PORTE_PCR18_OFFSET)
PORTE_PCR19        EQU  (PORTE_BASE + PORTE_PCR19_OFFSET)
PORTE_PCR20        EQU  (PORTE_BASE + PORTE_PCR20_OFFSET)
PORTE_PCR21        EQU  (PORTE_BASE + PORTE_PCR21_OFFSET)
PORTE_PCR22        EQU  (PORTE_BASE + PORTE_PCR22_OFFSET)
PORTE_PCR23        EQU  (PORTE_BASE + PORTE_PCR23_OFFSET)
PORTE_PCR24        EQU  (PORTE_BASE + PORTE_PCR24_OFFSET)
PORTE_PCR25        EQU  (PORTE_BASE + PORTE_PCR25_OFFSET)
PORTE_PCR26        EQU  (PORTE_BASE + PORTE_PCR26_OFFSET)
PORTE_PCR27        EQU  (PORTE_BASE + PORTE_PCR27_OFFSET)
PORTE_PCR28        EQU  (PORTE_BASE + PORTE_PCR28_OFFSET)
PORTE_PCR29        EQU  (PORTE_BASE + PORTE_PCR29_OFFSET)
PORTE_PCR30        EQU  (PORTE_BASE + PORTE_PCR30_OFFSET)
PORTE_PCR31        EQU  (PORTE_BASE + PORTE_PCR31_OFFSET)
PORTE_GPCLR        EQU  (PORTE_BASE + PORTE_GPCLR_OFFSET)
PORTE_GPCHR        EQU  (PORTE_BASE + PORTE_GPCHR_OFFSET)
PORTE_ISFR         EQU  (PORTE_BASE + PORTE_ISFR_OFFSET)
;---------------------------------------------------------------
;System integration module (SIM)
SIM_BASE             EQU  0x40047000
SIM_SOPT1CFG_OFFSET  EQU  0x04
SIM_SOPT2_OFFSET     EQU  0x1004
SIM_SOPT4_OFFSET     EQU  0x100C
SIM_SOPT5_OFFSET     EQU  0x1010
SIM_SOPT7_OFFSET     EQU  0x1018
SIM_SDID_OFFSET      EQU  0x1024
SIM_SCGC4_OFFSET     EQU  0x1034
SIM_SCGC5_OFFSET     EQU  0x1038
SIM_SCGC6_OFFSET     EQU  0x103C
SIM_SCGC7_OFFSET     EQU  0x1040
SIM_CLKDIV1_OFFSET   EQU  0x1044
SIM_FCFG1_OFFSET     EQU  0x104C
SIM_FCFG2_OFFSET     EQU  0x1050
SIM_UIDMH_OFFSET     EQU  0x1058
SIM_UIDML_OFFSET     EQU  0x105C
SIM_UIDL_OFFSET      EQU  0x1060
SIM_COPC_OFFSET      EQU  0x1100
SIM_SRVCOP_OFFSET    EQU  0x1104
SIM_CLKDIV1          EQU  (SIM_BASE + SIM_CLKDIV1_OFFSET)
SIM_COPC             EQU  (SIM_BASE + SIM_COPC_OFFSET)
SIM_FCFG1            EQU  (SIM_BASE + SIM_FCFG1_OFFSET)
SIM_FCFG2            EQU  (SIM_BASE + SIM_FCFG2_OFFSET)
SIM_SCGC4            EQU  (SIM_BASE + SIM_SCGC4_OFFSET) 
SIM_SCGC5            EQU  (SIM_BASE + SIM_SCGC5_OFFSET)
SIM_SCGC6            EQU  (SIM_BASE + SIM_SCGC6_OFFSET)
SIM_SCGC7            EQU  (SIM_BASE + SIM_SCGC7_OFFSET)
SIM_SDID             EQU  (SIM_BASE + SIM_SDID_OFFSET)
SIM_SOPT1CFG         EQU  (SIM_BASE + SIM_SOPT1CFG_OFFSET)
SIM_SOPT2            EQU  (SIM_BASE + SIM_SOPT2_OFFSET)
SIM_SOPT4            EQU  (SIM_BASE + SIM_SOPT4_OFFSET)
SIM_SOPT5            EQU  (SIM_BASE + SIM_SOPT5_OFFSET)
SIM_SOPT7            EQU  (SIM_BASE + SIM_SOPT7_OFFSET)
SIM_SRVCOP           EQU  (SIM_BASE + SIM_SRVCOP_OFFSET)
SIM_UIDL             EQU  (SIM_BASE + SIM_UIDL_OFFSET)
SIM_UIDMH            EQU  (SIM_BASE + SIM_UIDMH_OFFSET)
SIM_UIDML            EQU  (SIM_BASE + SIM_UIDML_OFFSET)
;---------------------------------------------------------------
;SIM_CLKDIV1
;31-28:OUTDIV1=clock 1 output divider value
;             :set divider for core/system clock,
;             :from which bus/flash clocks are derived
;             :divide by OUTDIV1 + 1
;27-19:Reserved; read-only; always 0
;18-16:OUTDIV4=clock 4 output divider value
;             :sets divider for bus and flash clocks,
;             :relative to core/system clock
;             :divide by OUTDIV4 + 1
;15-00:Reserved; read-only; always 0
SIM_CLKDIV1_OUTDIV1_MASK       EQU 0xF0000000
SIM_CLKDIV1_OUTDIV1_SHIFT      EQU 28
SIM_CLKDIV1_OUTDIV4_MASK       EQU 0x00070000
SIM_CLKDIV1_OUTDIV4_SHIFT      EQU 16
SIM_CLKDIV1_OUTDIV1_DIV2_MASK  EQU 0x10000000
SIM_CLKDIV1_OUTDIV4_DIV2_MASK  EQU 0x00010000
SIM_CORE_DIV2_BUS_DIV2         EQU \
  (SIM_CLKDIV1_OUTDIV1_DIV2_MASK :OR: SIM_CLKDIV1_OUTDIV4_DIV2_MASK)
;---------------------------------------------------------------
;SIM_COPC
;31-04:Reserved; read-only; always 0
;03-02:COPT=COP watchdog timeout
;          :00=disabled
;          :01=timeout after 2^5 LPO cycles or 2^13 bus cycles
;          :10=timeout after 2^8 LPO cycles or 2^16 bus cycles
;          :11=timeout after 2^10 LPO cycles or 2^18 bus cycles
;   01:COPCLKS=COP clock select
;             :0=internal 1 kHz
;             :1=bus clock
;   00:COPW=COP windowed mode
COP_COPT_MASK      EQU  0x0000000C
COP_COPT_SHIFT     EQU  2
COP_COPCLKS_MASK   EQU  0x00000002
COP_COPCLKS_SHIFT  EQU  1
COP_COPW_MASK      EQU  0x00000001
COP_COPW_SHIFT     EQU  1
COP_DISABLE        EQU  0x00000000
;---------------------------------------------------------------
;SIM_SCGC4
;1->31-28:Reserved; read-only; always 1
;0->27-24:Reserved; read-only; always 0
;0->   23:SPI1=SPI1 clock gate control (disabled)
;0->   22:SPI0=SPI0 clock gate control (disabled)
;0->21-20:Reserved; read-only; always 0
;0->   19:CMP=comparator clock gate control (disabled)
;0->   18:USBOTG=USB clock gate control (disabled)
;0->17-14:Reserved; read-only; always 0
;0->   13:Reserved; read-only; always 0
;0->   12:UART2=UART2 clock gate control (disabled)
;1->   11:UART1=UART1 clock gate control (disabled)
;0->   10:UART0=UART0 clock gate control (disabled)
;0->09-08:Reserved; read-only; always 0
;0->   07:I2C1=I2C1 clock gate control (disabled)
;0->   06:I2C0=I2C0 clock gate control (disabled)
;1->05-04:Reserved; read-only; always 1
;0->03-00:Reserved; read-only; always 0
SIM_SCGC4_SPI1_MASK     EQU  0x00800000
SIM_SCGC4_SPI1_SHIFT    EQU  23
SIM_SCGC4_SPI0_MASK     EQU  0x00400000
SIM_SCGC4_SPI0_SHIFT    EQU  22
SIM_SCGC4_CMP_MASK      EQU  0x00080000
SIM_SCGC4_CMP_SHIFT     EQU  19
SIM_SCGC4_USBOTG_MASK   EQU  0x00040000
SIM_SCGC4_USBOTG_SHIFT  EQU  18
SIM_SCGC4_UART2_MASK    EQU  0x00001000
SIM_SCGC4_UART2_SHIFT   EQU  12
SIM_SCGC4_UART1_MASK    EQU  0x00000800
SIM_SCGC4_UART1_SHIFT   EQU  11
SIM_SCGC4_UART0_MASK    EQU  0x00000400
SIM_SCGC4_UART0_SHIFT   EQU  10
SIM_SCGC4_I2C1_MASK     EQU  0x00000080
SIM_SCGC4_I2C1_SHIFT    EQU  7
SIM_SCGC4_I2C0_MASK     EQU  0x00000040
SIM_SCGC4_I2C0_SHIFT    EQU  6
;---------------------------------------------------------------
;SIM_SCGC5
;31-20:Reserved; read-only; always 0
;   19:Reserved; read-only; always 0
;18-14:Reserved; read-only; always 0
;   13:PORTE=Port E clock gate control
;   12:PORTD=Port D clock gate control
;   11:PORTC=Port C clock gate control
;   10:PORTB=Port B clock gate control
;    9:PORTA=Port A clock gate control
;08-07:Reserved; read-only; always 1
;    6:Reserved; read-only; always 0
;    5:TSI=TSI access control
;04-02:Reserved; read-only; always 0
;    1:Reserved; read-only; always 0
;    0:LPTMR=Low power timer access control
SIM_SCGC5_PORTE_MASK   EQU  0x00002000
SIM_SCGC5_PORTE_SHIFT  EQU  13
SIM_SCGC5_PORTD_MASK   EQU  0x00001000
SIM_SCGC5_PORTD_SHIFT  EQU  12
SIM_SCGC5_PORTC_MASK   EQU  0x00000800
SIM_SCGC5_PORTC_SHIFT  EQU  11
SIM_SCGC5_PORTB_MASK   EQU  0x00000400
SIM_SCGC5_PORTB_SHIFT  EQU  10
SIM_SCGC5_PORTA_MASK   EQU  0x00000200
SIM_SCGC5_PORTA_SHIFT  EQU  9
SIM_SCGC5_TSI_MASK     EQU  0x00000020
SIM_SCGC5_TSI_SHIFT    EQU  6
SIM_SCGC5_LPTMR_MASK   EQU  0x00000001
SIM_SCGC5_LPTMR_SHIFT  EQU  0
;---------------------------------------------------------------
;SIM_SCGC6
;   31:DAC0=DAC0 clock gate control
;   30:(reserved):read-only:0
;   29:RTC=RTC access controll
;   28:(reserved):read-only:0
;   27:ADC0=ADC0 clock gate control
;   26:TPM2=TPM2 clock gate control
;   25:TPM1=TMP1 clock gate control
;   24:TPM0=TMP0 clock gate control
;   23:PIT=PIT clock gate control
;22-16:(reserved)
;   15:(reserved)
;14-02:(reserved)
;    1:DMAMUX=DMA mux clock gate control
;    0:FTF=flash memory clock gate control
SIM_SCGC6_DAC0_MASK     EQU  0x80000000
SIM_SCGC6_DAC0_SHIFT    EQU  31
SIM_SCGC6_RTC_MASK      EQU  0x20000000
SIM_SCGC6_RTC_SHIFT     EQU  29
SIM_SCGC6_ADC0_MASK     EQU  0x08000000
SIM_SCGC6_ADC0_SHIFT    EQU  27
SIM_SCGC6_TPM2_MASK     EQU  0x04000000
SIM_SCGC6_TPM2_SHIFT    EQU  26
SIM_SCGC6_TPM1_MASK     EQU  0x02000000
SIM_SCGC6_TPM1_SHIFT    EQU  25
SIM_SCGC6_TPM0_MASK     EQU  0x01000000
SIM_SCGC6_TPM0_SHIFT    EQU  24
SIM_SCGC6_PIT_MASK      EQU  0x00800000
SIM_SCGC6_PIT_SHIFT     EQU  23
SIM_SCGC6_DMAMUX_MASK   EQU  0x00000002
SIM_SCGC6_DMAMUX_SHIFT  EQU  1
SIM_SCGC6_FTF_MASK      EQU  0x00000001
SIM_SCGC6_FTF_SHIFT     EQU  0
;---------------------------------------------------------------
;SIM_SOPT2
;31-28:(reserved):read-only:0
;27-26:UART0SRC=UART0 clock source select
;               00:clock disabled
;               01:MCGFLLCLK or MCGPLLCLK/2
;               10:OSCERCLK
;               11:MCGIRCLK
;25-24:TPMSRC=TPM clock source select
;             00:clock disabled
;             01:MCGFLLCLK or MCGPLLCLK/2
;             10:OSCERCLK
;             11:MCGIRCLK
;23-19:(reserved):read-only:0
;   18:USBSRC=USB clock source select
;             0:USB_CLKIN
;             1:MCGFLLCLK or MCGPLLCLK/2
;   17:(reserved):read-only:0
;   16:PLLFLLSEL=PLL/FLL clock select
;             0:MCGFLLCLK
;             1:MCGPLLCLK/2
;15- 8:(reserved):read-only:0
; 7- 5:CLKOUTSEL=CLKOUT select
;                000:(reserved)
;                001:(reserved)
;                010:bus clock
;                011:LPO clock (1 KHz)
;                100:MCGIRCLK
;                101:(reserved)
;                110:OSCERCLK
;                110:(reserved)
;    4:RTCCLKOUTSEL=RTC clock out select
;                   0:RTC (1 Hz)
;                   1:OSCERCLK
; 3- 0:(reserved):read-only:0
SIM_SOPT2_UART0SRC_MASK       EQU  0x0C000000
SIM_SOPT2_UART0SRC_SHIFT      EQU  26
SIM_SOPT2_TPMSRC_MASK         EQU  0x03000000
SIM_SOPT2_TPMSRC_SHIFT        EQU  24
SIM_SOPT2_USBSRC_MASK         EQU  0x00040000
SIM_SOPT2_USBSRC_SHIFT        EQU  18
SIM_SOPT2_PLLFLLSEL_MASK      EQU  0x00010000
SIM_SOPT2_PLLFLLSEL_SHIFT     EQU  16
SIM_SOPT2_CLKOUTSEL_MASK      EQU  0xE0
SIM_SOPT2_CLKOUTSEL_SHIFT     EQU  5
SIM_SOPT2_RTCCLKOUTSEL_MASK   EQU  0x10
SIM_SOPT2_RTCCLKOUTSEL_SHIFT  EQU  4
;---------------------------------------------------------------
;SIM_SOPT5
;31-20:Reserved; read-only; always 0
;   19:Reserved; read-only; always 0
;   18:UART2ODE=UART2 open drain enable
;   17:UART1ODE=UART1 open drain enable
;   16:UART0ODE=UART0 open drain enable
;15-07:Reserved; read-only; always 0
;   06:UART1TXSRC=UART1 receive data select
;                :0=UART1_RX pin
;                :1=CMP0 output
;05-04:UART1TXSRC=UART1 transmit data select source
;                :00=UART1_TX pin
;                :01=UART1_TX pin modulated with TPM1 channel 0 output
;                :10=UART1_TX pin modulated with TPM2 channel 0 output
;                :11=(reserved)
;   03:Reserved; read-only; always 0
;   02:UART0RXSRC=UART0 receive data select
;                :0=UART0_RX pin
;                :1=CMP0 output
;01-00:UART0TXSRC=UART0 transmit data select source
;                :00=UART0_TX pin
;                :01=UART0_TX pin modulated with TPM1 channel 0 output
;                :10=UART0_TX pin modulated with TPM2 channel 0 output
;                :11=(reserved)
SIM_SOPT5_UART2ODE_MASK     EQU  0x00040000
SIM_SOPT5_UART2ODE_SHIFT    EQU  18
SIM_SOPT5_UART1ODE_MASK     EQU  0x00020000
SIM_SOPT5_UART1ODE_SHIFT    EQU  17
SIM_SOPT5_UART0ODE_MASK     EQU  0x00010000
SIM_SOPT5_UART0ODE_SHIFT    EQU  16
SIM_SOPT5_UART1RXSRC_MASK   EQU  0x00000040
SIM_SOPT5_UART1RXSRC_SHIFT  EQU  6
SIM_SOPT5_UART1TXSRC_MASK   EQU  0x00000030
SIM_SOPT5_UART1TXSRC_SHIFT  EQU  4
SIM_SOPT5_UART0RXSRC_MASK   EQU  0x00000004
SIM_SOPT5_UART0RXSRC_SHIFT  EQU  2
SIM_SOPT5_UART0TXSRC_MASK   EQU  0x00000003
SIM_SOPT5_UART0TXSRC_SHIFT  EQU  0
;---------------------------------------------------------------
;Timer/PWM modules (TPMx)
TPM_SC_OFFSET      EQU  0x00
TPM_CNT_OFFSET     EQU  0x04
TPM_MOD_OFFSET     EQU  0x08
TPM_C0SC_OFFSET    EQU  0x0C
TPM_C0V_OFFSET     EQU  0x10
TPM_C1SC_OFFSET    EQU  0x14
TPM_C1V_OFFSET     EQU  0x18
TPM_C2SC_OFFSET    EQU  0x1C
TPM_C2V_OFFSET     EQU  0x20
TPM_C3SC_OFFSET    EQU  0x24
TPM_C3V_OFFSET     EQU  0x28
TPM_C4SC_OFFSET    EQU  0x2C
TPM_C4V_OFFSET     EQU  0x30
TPM_C5SC_OFFSET    EQU  0x34
TPM_C5V_OFFSET     EQU  0x38
TPM_STATUS_OFFSET  EQU  0x50
TPM_CONF_OFFSET    EQU  0x84
;---------------------------------------------------------------
;TPMx_CnSC:  Channel n Status and Control
;31-8:(reserved):read-only:0
;   7:CHF=channel flag
;         set on channel event
;         write 1 to clear
;   6:CHIE=channel interrupt enable
;   5:MSB=channel mode select B (see selection table below)
;   4:MSA=channel mode select A (see selection table below)
;   3:ELSB=edge or level select B (see selection table below)
;   2:ELSA=edge or level select A (see selection table below)
;   1:(reserved):read-only:0
;   0:DMA=DMA enable
;Mode, Edge, and Level Selection
;MSB:MSA | ELSB:ELSA | Mode           | Configuration
;  0 0   |    0 0    | (none)         | channel disabled
;  0 1   |    0 0    | SW compare     | pin not used
;  1 X   |    0 0    | SW compare     | pin not used
;  0 0   |    0 1    | input capture  | rising edge
;  0 0   |    1 0    | input capture  | falling edge
;  0 0   |    1 1    | input capture  | either edge
;  0 1   |    0 1    | output compare | toggle on match
;  0 1   |    1 0    | output compare | clear on match
;  0 1   |    1 1    | output compare | set on match
;  1 0   |    X 1    | PWM            | low pulse
;  1 0   |    1 0    | PWM            | high pulse
;  1 1   |    X 1    | output compare | pulse high on match
;  1 1   |    1 0    | output compare | pulse low on match
TPM_CnSC_CHF_MASK    EQU  0x80
TPM_CnSC_CHF_SHIFT   EQU  7
TPM_CnSC_CHIE_MASK   EQU  0x40
TPM_CnSC_CHIE_SHIFT  EQU  6
TPM_CnSC_MSB_MASK    EQU  0x20
TPM_CnSC_MSB_SHIFT   EQU  5
TPM_CnSC_MSA_MASK    EQU  0x10
TPM_CnSC_MSA_SHIFT   EQU  4
TPM_CnSC_ELSB_MASK   EQU  0x08
TPM_CnSC_ELSB_SHIFT  EQU  3
TPM_CnSC_ELSA_MASK   EQU  0x04
TPM_CnSC_ELSA_SHIFT  EQU  2
TPM_CnSC_CDMA_MASK   EQU  0x01
TPM_CnSC_CDMA_SHIFT  EQU  0
;---------------------------------------------------------------
;TPMx_CnV:  Channel n Value
;31-16:(reserved):read-only:0
;16- 0:MOD (all bytes must be written at the same time)
TPM_CnV_VAL_MASK   EQU 0xFFFF
TPM_CnV_VAL_SHIFT  EQU 0
;---------------------------------------------------------------
;TPMx_CONF:  Configuration
;31-28:(reserved):read-only:0
;27-24:TRGSEL=trigger select
;             should be changed only when counter disabled
;             0000:EXTRG_IN (external trigger pin input)
;             0001:CMP0 output
;             0010:(reserved)
;             0011:(reserved)
;             0100:PIT trigger 0
;             0101:PIT trigger 1
;             0110:(reserved)
;             0111:(reserved)
;             1000:TPM0 overflow
;             1001:TPM1 overflow
;             1010:TPM2 overflow
;             1011:(reserved)
;             1100:RTC alarm
;             1101:RTC seconds
;             1110:LPTMR trigger
;             1111:(reserved)
;23-19:(reserved):read-only:0
;   18:CROT=counter reload on trigger
;           should be changed only when counter disabled
;   17:CSOO=counter stop on overflow
;           should be changed only when counter disabled
;   16:CSOT=counter start on trigger
;           should be changed only when counter disabled
;15-10:(reserved):read-only:0
;    9:GTBEEN=global time base enable
;    8:(reserved):read-only:0
; 7- 6:DBGMODE=debug mode
;              00:paused during debug, and during debug
;                 trigger and input caputure events ignored
;              01:(reserved)
;              10:(reserved)
;              11:counter continues during debug
;    5:DOZEEN=doze enable
;             0:counter continues during debug
;             1:paused during debug, and during debug
;               trigger and input caputure events ignored
; 4- 0:(reserved):read-only:0
TPM_CONF_TRGSEL_MASK    EQU  0x0F000000
TPM_CONF_TRGSEL_SHIFT   EQU  24
TPM_CONF_CROT_MASK      EQU  0x00040000
TPM_CONF_CROT_SHIFT     EQU  18
TPM_CONF_CSOO_MASK      EQU  0x00020000
TPM_CONF_CSOO_SHIFT     EQU  17
TPM_CONF_CSOT_MASK      EQU  0x00010000
TPM_CONF_CSOT_SHIFT     EQU  16
TPM_CONF_GTBEEN_MASK    EQU  0x200
TPM_CONF_GTBEEN_SHIFT   EQU  9
TPM_CONF_DBGMODE_MASK   EQU  0xC0
TPM_CONF_DBGMODE_SHIFT  EQU  6
TPM_CONF_DOZEEN_MASK    EQU  0x20
TPM_CONF_DOZEEN_SHIFT   EQU  5
;---------------------------------------------------------------
;TPMx_MOD:  Modulo
;31-16:(reserved):read-only:0
;16- 0:MOD (all bytes must be written at the same time)
TPM_MOD_MOD_MASK   EQU 0xFFFF
TPM_MOD_MOD_SHIFT  EQU 0xFFFF
;---------------------------------------------------------------
;TPMx_SC:  Status and Control
;31-9:(reserved):read-only:0
;   8:DMA=DMA enable
;   7:TOF=timer overflow flag
;         set on count after TPMx_CNT = TPMx_MOD
;         write 1 to clear
;   6:TOIE=timer overflow interrupt enable
;   5:CPWMS=center-aligned PWM select
;           0:edge align (up count)
;           1:center align (up-down count)
; 4-3:CMOD=clock mode selection
;          00:counter disabled
;          01:TPMx_CNT increments on every TPMx clock
;          10:TPMx_CNT increments on rising edge of TPMx_EXTCLK
;          11:(reserved)
; 2-0:PS=prescale factor selection
;        can be written only when counter is disabled
;        count clock = CMOD selected clock / 2^PS
TPM_SC_DMA_MASK     EQU 0x100
TPM_SC_DMA_SHIFT    EQU 8
TPM_SC_TOF_MASK     EQU 0x80
TPM_SC_TOF_SHIFT    EQU 7
TPM_SC_TOIE_MASK    EQU 0x40
TPM_SC_TOIE_SHIFT   EQU 6
TPM_SC_CPWMS_MASK   EQU 0x20
TPM_SC_CPWMS_SHIFT  EQU 5
TPM_SC_CMOD_MASK    EQU 0x18
TPM_SC_CMOD_SHIFT   EQU 3
TPM_SC_PS_MASK      EQU 0x07
TPM_SC_PS_SHIFT     EQU 0
;---------------------------------------------------------------
;TPMx_STATUS:  Capture and Compare Status
;31-9:(reserved):read-only:0
;   8:TOF=timer overflow flag=TPMx_SC.TOF
; 7-6:(reserved):read-only:0
;   5:CH5F=channel 5 flag=TPMx_C5SC.CHF
;   4:CH4F=channel 4 flag=TPMx_C4SC.CHF
;   3:CH3F=channel 3 flag=TPMx_C3SC.CHF
;   2:CH2F=channel 2 flag=TPMx_C2SC.CHF
;   1:CH1F=channel 1 flag=TPMx_C1SC.CHF
;   0:CH0F=channel 0 flag=TPMx_C0SC.CHF
TPM_STATUS_TOF_MASK    EQU 0x100
TPM_STATUS_TOF_SHIFT   EQU 8
TPM_STATUS_CH5F_MASK   EQU 0x20
TPM_STATUS_CH5F_SHIFT  EQU 5
TPM_STATUS_CH4F_MASK   EQU 0x10
TPM_STATUS_CH4F_SHIFT  EQU 4
TPM_STATUS_CH3F_MASK   EQU 0x08
TPM_STATUS_CH3F_SHIFT  EQU 3
TPM_STATUS_CH2F_MASK   EQU 0x04
TPM_STATUS_CH2F_SHIFT  EQU 2
TPM_STATUS_CH1F_MASK   EQU 0x02
TPM_STATUS_CH1F_SHIFT  EQU 1
TPM_STATUS_CH0F_MASK   EQU 0x01
TPM_STATUS_CH0F_SHIFT  EQU 0
;---------------------------------------------------------------
;Timer/PWM module 2 (TPM2)
TPM2_BASE           EQU  0x4003A000
TPM2_SC      EQU (TPM2_BASE + TPM_SC_OFFSET    )
TPM2_CNT     EQU (TPM2_BASE + TPM_CNT_OFFSET   )
TPM2_MOD     EQU (TPM2_BASE + TPM_MOD_OFFSET   )
TPM2_C0SC    EQU (TPM2_BASE + TPM_C0SC_OFFSET  )
TPM2_C0V     EQU (TPM2_BASE + TPM_C0V_OFFSET   )
TPM2_C1SC    EQU (TPM2_BASE + TPM_C1SC_OFFSET  )
TPM2_C1V     EQU (TPM2_BASE + TPM_C1V_OFFSET   )
TPM2_C2SC    EQU (TPM2_BASE + TPM_C2SC_OFFSET  )
TPM2_C2V     EQU (TPM2_BASE + TPM_C2V_OFFSET   )
TPM2_C3SC    EQU (TPM2_BASE + TPM_C3SC_OFFSET  )
TPM2_C3V     EQU (TPM2_BASE + TPM_C3V_OFFSET   )
TPM2_C4SC    EQU (TPM2_BASE + TPM_C4SC_OFFSET  )
TPM2_C4V     EQU (TPM2_BASE + TPM_C4V_OFFSET   )
TPM2_C5SC    EQU (TPM2_BASE + TPM_C5SC_OFFSET  )
TPM2_C5V     EQU (TPM2_BASE + TPM_C5V_OFFSET   )
TPM2_STATUS  EQU (TPM2_BASE + TPM_STATUS_OFFSET)
TPM2_CONF    EQU (TPM2_BASE + TPM_CONF_OFFSET  )
	;---------------------------------------------------------------
	;UART 1
UART1_BASE  EQU  0x4006B000
UART_BDH_OFFSET  EQU  0x00
UART_BDL_OFFSET  EQU  0x01
UART_C1_OFFSET   EQU  0x02
UART_C2_OFFSET   EQU  0x03
UART_S1_OFFSET   EQU  0x04
UART_S2_OFFSET   EQU  0x05
UART_C3_OFFSET   EQU  0x06
UART_D_OFFSET    EQU  0x07
UART_C4_OFFSET   EQU  0x08
UART1_BDH        EQU  (UART1_BASE + UART_BDH_OFFSET)
UART1_BDL        EQU  (UART1_BASE + UART_BDL_OFFSET)
UART1_C1         EQU  (UART1_BASE + UART_C1_OFFSET)
UART1_C2         EQU  (UART1_BASE + UART_C2_OFFSET)
UART1_S1         EQU  (UART1_BASE + UART_S1_OFFSET)
UART1_S2         EQU  (UART1_BASE + UART_S2_OFFSET)
UART1_C3         EQU  (UART1_BASE + UART_C3_OFFSET)
UART1_D          EQU  (UART1_BASE + UART_D_OFFSET)
UART1_C4         EQU  (UART1_BASE + UART_C4_OFFSET)
;UART0
UART0_BASE  EQU  0x4006A000
UART0_BDH        EQU  (UART0_BASE + UART_BDH_OFFSET)
UART0_BDL        EQU  (UART0_BASE + UART_BDL_OFFSET)
UART0_C1         EQU  (UART0_BASE + UART_C1_OFFSET)
UART0_C2         EQU  (UART0_BASE + UART_C2_OFFSET)
UART0_S1         EQU  (UART0_BASE + UART_S1_OFFSET)
UART0_S2         EQU  (UART0_BASE + UART_S2_OFFSET)
UART0_C3         EQU  (UART0_BASE + UART_C3_OFFSET)
UART0_D          EQU  (UART0_BASE + UART_D_OFFSET)
UART0_C4         EQU  (UART0_BASE + UART_C4_OFFSET)
;---------------------------------------------------------------
;UARTx_BDH
;  7:LBKDIE=LIN break detect IE
;  6:RXEDGIE=RxD input active edge IE
;  5:SBNS=Stop bit number select
;4-0:SBR[12:0] (BUSCLK / (16 x 9600))
UART_BDH_LBKDIE_MASK    EQU  0x80
UART_BDH_LBKDIE_SHIFT   EQU  7
UART_BDH_RXEDGIE_MASK   EQU  0x40
UART_BDH_RXEDGIE_SHIFT  EQU  6
UART_BDH_SBNS_MASK      EQU  0x20
UART_BDH_SBNS_SHIFT     EQU  5
UART_BDH_SBR_MASK       EQU  0x1F
UART_BDH_SBR_SHIFT      EQU  0
;---------------------------------------------------------------
;UARTx_BDL
;7-0:SBR[7:0] (BUSCLK / 16 x 9600))
UART_BDL_SBR_MASK   EQU  0xFF
UART_BDL_SBR_SHIFT  EQU  0
;---------------------------------------------------------------
;UARTx_C1
;7:LOOPS=loops select (normal)
;6:UARTSWAI=UART stop in wait mode (disabled)
;5:RSRC=receiver source select (internal--no effect LOOPS=0)
;4:M=9- or 8-bit mode select (1 start, 8 data [lsb first], 1 stop)
;3:WAKE=receiver wakeup method select (idle)
;2:IDLE=idle line type select (idle begins after start bit)
;1:PE=parity enable (disabled)
;0:PT=parity type (even parity--no effect PE=0)
UART_C1_LOOPS_MASK      EQU  0x80
UART_C1_LOOPS_SHIFT     EQU  7
UART_C1_UARTSWAI_MASK   EQU  0x40
UART_C1_UARTSWAI_SHIFT  EQU  6
UART_C1_RSRC_MASK       EQU  0x20
UART_C1_RSRC_SHIFT      EQU  5
UART_C1_M_MASK          EQU  0x10
UART_C1_M_SHIFT         EQU  4
UART_C1_WAKE_MASK       EQU  0x08
UART_C1_WAKE_SHIFT      EQU  3
UART_C1_ILT_MASK        EQU  0x04
UART_C1_ILT_SHIFT       EQU  2
UART_C1_PE_MASK         EQU  0x02
UART_C1_PE_SHIFT        EQU  1
UART_C1_PT_MASK         EQU  0x01
UART_C1_PT_SHIFT        EQU  0
;---------------------------------------------------------------
;UARTx_C2
;7:TIE=transmit IE for TDRE (disabled)
;6:TCIE=trasmission complete IE for TC (disabled)
;5:RIE=receiver IE for RDRF (disabled)
;4:ILIE=idle line IE for IDLE (disabled)
;3:TE=transmitter enable (enabled)
;2:RE=receiver enable (enabled)
;1:RWU=receiver wakeup control (normal)
;0:SBK=send break (disabled, normal)
UART_C2_TIE_MASK    EQU  0x80
UART_C2_TIE_SHIFT   EQU  7
UART_C2_TCIE_MASK   EQU  0x40
UART_C2_TCIE_SHIFT  EQU  6
UART_C2_RIE_MASK    EQU  0x20
UART_C2_RIE_SHIFT   EQU  5
UART_C2_ILIE_MASK   EQU  0x10
UART_C2_ILIE_SHIFT  EQU  4
UART_C2_TE_MASK     EQU  0x08
UART_C2_TE_SHIFT    EQU  3
UART_C2_RE_MASK     EQU  0x04
UART_C2_RE_SHIFT    EQU  2
UART_C2_RWU_MASK    EQU  0x02
UART_C2_RWU_SHIFT   EQU  1
UART_C2_SBK_MASK    EQU  0x01
UART_C2_SBK_SHIFT   EQU  0
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
UART_C3_R8_MASK      EQU  0x80
UART_C3_R8_SHIFT     EQU  7
UART_C3_T8_MASK      EQU  0x40
UART_C3_T8_SHIFT     EQU  6
UART_C3_TXDIR_MASK   EQU  0x20
UART_C3_TXDIR_SHIFT  EQU  5
UART_C3_TXINV_MASK   EQU  0x10
UART_C3_TXINV_SHIFT  EQU  4
UART_C3_ORIE_MASK    EQU  0x08
UART_C3_ORIE_SHIFT   EQU  3
UART_C3_NEIE_MASK    EQU  0x04
UART_C3_NEIE_SHIFT   EQU  2
UART_C3_FEIE_MASK    EQU  0x02
UART_C3_FEIE_SHIFT   EQU  1
UART_C3_PEIE_MASK    EQU  0x01
UART_C3_PEIE_SHIFT   EQU  0
;---------------------------------------------------------------
;UARTx_C4
;  7:TDMAS=transmitter DMA select (disabled)
;  6:(reserved); read-only; always 0
;  5:RDMAS=receiver full DMA select (disabled)
;  4:(reserved); read-only; always 0
;  3:(reserved); read-only; always 0
;2-0:(reserved); read-only; always 0
UART_C4_TDMAS_MASK   EQU  0x80
UART_C4_TDMAS_SHIFT  EQU  7
UART_C4_RDMAS_MASK   EQU  0x20
UART_C4_RDMAS_SHIFT  EQU  5
;---------------------------------------------------------------
;UARTx_S1
;7:TDRE=transmit data register empty flag
;6:TC=transmission complete flag
;5:RDRF=receive data register full flag
;4:IDLE=idle line flag
;3:OR=receiver overrun flag
;2:NF=noise flag
;1:FE=framing error flag
;0:PF=parity error flag
UART_S1_TDRE_MASK   EQU 0x80
UART_S1_TDRE_SHIFT  EQU 7
UART_S1_TC_MASK     EQU 0x40
UART_S1_TC_SHIFT    EQU 6
UART_S1_RDRF_MASK   EQU 0x20
UART_S1_RDRF_SHIFT  EQU 5
UART_S1_IDLE_MASK   EQU 0x10
UART_S1_IDLE_SHIFT  EQU 4
UART_S1_OR_MASK     EQU 0x08
UART_S1_OR_SHIFT    EQU 3
UART_S1_NF_MASK     EQU 0x04
UART_S1_NF_SHIFT    EQU 2
UART_S1_FE_MASK     EQU 0x02
UART_S1_FE_SHIFT    EQU 1
UART_S1_PF_MASK     EQU 0x01
UART_S1_PF_SHIFT    EQU 0
;---------------------------------------------------------------
;UARTx_S2
;7:LBKDIF=LIN break detect interrupt flag
;6:RXEDGIF=RxD pin active edge interrupt flag
;5:(reserved);read-only; always 0
;4:RXINV=receive data inversion
;3:RWUID=receive wake-up idle detect
;2:BRK13=break character generation length
;1:LBKDE=LIN break detect enable
;0:RAF=receiver active flag
UART_S2_LBKDIF_MASK   EQU 0x80
UART_S2_LBKDIF_SHIFT  EQU 7
UART_S2_RXEDGIF_MASK  EQU 0x40
UART_S2_RXEDGIF_SHIF  EQU 6
UART_S2_RXINV_MASK    EQU 0x10
UART_S2_RXINV_SHIFT   EQU 4
UART_S2_RWUID_MASK    EQU 0x08
UART_S2_RWUID_SHIFT   EQU 3
UART_S2_BRK13_MASK    EQU 0x04
UART_S2_BRK13_SHIFT   EQU 2
UART_S2_LBKDE_MASK    EQU 0x02
UART_S2_LBKDE_SHIFT   EQU 1
UART_S2_RAF_MASK      EQU 0x01
UART_S2_RAF_SHIFT     EQU 0
            END
