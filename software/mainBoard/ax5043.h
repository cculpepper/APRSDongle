#include <stdint.h>
#define AX_REG_SILICONREVISION 		0x000 	/* Silicon Revision */        
#define AX_REG_SCRATCH 			0x001 	/* Scratch */         
#define AX_REG_PWRMODE 			0x002 	/* Power Mode */        
#define AX_REG_POWSTAT 			0x003 	/* Power Management Status */       
#define AX_REG_POWSTICKYSTAT 		0x004 	/* Power Management Sticky Status */      
#define AX_REG_POWIRQMASK 		0x005 	/* Power Management Interrupt Mask */      
#define AX_REG_IRQMASK1 		0x006 	/* IRQ Mask 1 */       
#define AX_REG_IRQMASK0 		0x007 	/* IRQ Mask 0 */       
#define AX_REG_RADIOEVENTMASK1 		0x008 	/* Radio Event Mask 1 */      
#define AX_REG_RADIOEVENTMASK0 		0x009 	/* Radio Event Mask 0 */      
#define AX_REG_IRQINVERSION1 		0x00A 	/* IRQ Inversion 1 */       
#define AX_REG_IRQINVERSION0 		0x00B 	/* IRQ Inversion 0 */       
#define AX_REG_IRQREQUEST1 		0x00C 	/* IRQ Request 1 */       
#define AX_REG_IRQREQUEST0 		0x00D 	/* IRQ Request 0 */       
#define AX_REG_RADIOEVENTREQ1 		0x00E 	/* Radio Event Request 1 */      
#define AX_REG_RADIOEVENTREQ0 		0x00F 	/* Radio Event Request 0 */      
#define AX_REG_MODULATION 		0x010 	/* Modulation */         
#define AX_REG_ENCODING 		0x011 	/* Encoding */         
#define AX_REG_FRAMING 			0x012 	/* Framing Mode */        
#define AX_REG_CRCINIT3 		0x014 	/* CRC Initial Value 3 */      
#define AX_REG_CRCINIT2 		0x015 	/* CRC Initial Value 2 */      
#define AX_REG_CRCINIT1 		0x016 	/* CRC Initial Value 1 */      
#define AX_REG_CRCINIT0 		0x017 	/* CRC Initial Value 0 */      
#define AX_REG_FEC 			0x018 	/* Forward Error Correction */       
#define AX_REG_FECSYNC 			0x019 	/* Forward Error Correction Sync Threshold */     
#define AX_REG_FECSTATUS 		0x01A 	/* Forward Error Correction Status */      
#define AX_REG_RADIOSTATE 		0x01C 	/* Radio Controller State */       
#define AX_REG_XTALSTATUS 		0x01D 	/* Crystal Oscillator Status */       
#define AX_REG_PINSTATE 		0x020 	/* Pin State */        
#define AX_REG_PINFUNCSYSCLK 		0x021 	/* Pin Function SYSCLK */       
#define AX_REG_PINFUNCDCLK 		0x022 	/* Pin Function DCLK */       
#define AX_REG_PINFUNCDATA 		0x023 	/* Pin Function DATA */       
#define AX_REG_PINFUNCIRQ 		0x024 	/* Pin Function IRQ */       
#define AX_REG_PINFUNCANTSEL 		0x025 	/* Pin Function ANTSEL */       
#define AX_REG_PINFUNCPWRAMP 		0x026 	/* Pin Function PWRAMP */       
#define AX_REG_PWRAMP 			0x027 	/* PWRAMP Control */        
#define AX_REG_FIFOSTAT 		0x028 	/* FIFO Control */        
#define AX_REG_FIFODATA 		0x029 	/* FIFO Data */        
#define AX_REG_FIFOCOUNT1 		0x02A 	/* Number of Words currently in FIFO 1 */   
#define AX_REG_FIFOCOUNT0 		0x02B 	/* Number of Words currently in FIFO 0 */   
#define AX_REG_FIFOFREE1 		0x02C 	/* Number of Words that can be written to FIFO 1 */
#define AX_REG_FIFOFREE0 		0x02D 	/* Number of Words that can be written to FIFO 0 */
#define AX_REG_FIFOTHRESH1 		0x02E 	/* FIFO Threshold 1 */       
#define AX_REG_FIFOTHRESH0 		0x02F 	/* FIFO Threshold 0 */       
#define AX_REG_PLLLOOP 			0x030 	/* PLL Loop Filter Settings */      
#define AX_REG_PLLCPI 			0x031 	/* PL Charge Pump Current */      
#define AX_REG_PLLVCODIV 		0x032 	/* PLL Divider Settings */       
#define AX_REG_PLLRANGINGA 		0x033 	/* PLL Autoranging A */       
#define AX_REG_FREQA3 			0x034 	/* Frequency A 3 */       
#define AX_REG_FREQA2 			0x035 	/* Frequency A 2 */       
#define AX_REG_FREQA1 			0x036 	/* Frequency A 1 */       
#define AX_REG_FREQA0 			0x037 	/* Frequency A 0 */       
#define AX_REG_PLLLOOPBOOST 		0x038 	/* PLL Loop Filter Settings (Boosted) */     
#define AX_REG_PLLCPIBOOST 		0x039 	/* PLL Charge Pump Current (Boosted) */     
#define AX_REG_PLLRANGINGB 		0x03B 	/* PLL Autoranging B */       
#define AX_REG_FREQB3 			0x03C 	/* Frequency B 3 */       
#define AX_REG_PINFUNCDATA 		0x023 	/* Pin Function DATA */       
#define AX_REG_PINFUNCIRQ 		0x024 	/* Pin Function IRQ */       
#define AX_REG_PINFUNCANTSEL 		0x025 	/* Pin Function ANTSEL */       
#define AX_REG_PINFUNCPWRAMP 		0x026 	/* Pin Function PWRAMP */       
#define AX_REG_PWRAMP 			0x027 	/* PWRAMP Control */        
#define AX_REG_FIFOSTAT 		0x028 	/* FIFO Control */        
#define AX_REG_FIFODATA 		0x029 	/* FIFO Data */        
#define AX_REG_FIFOCOUNT1 		0x02A 	/* Number of Words currently in FIFO 1 */   
#define AX_REG_FIFOCOUNT0 		0x02B 	/* Number of Words currently in FIFO 0 */   
#define AX_REG_FIFOFREE1 		0x02C 	/* Number of Words that can be written to FIFO 1 */
#define AX_REG_FIFOFREE0 		0x02D 	/* Number of Words that can be written to FIFO 0 */
#define AX_REG_FIFOTHRESH1 		0x02E 	/* FIFO Threshold 1 */       
#define AX_REG_FIFOTHRESH0 		0x02F 	/* FIFO Threshold 0 */       
#define AX_REG_PLLLOOP 			0x030 	/* PLL Loop Filter Settings */      
#define AX_REG_PLLCPI 			0x031 	/* PL Charge Pump Current */      
#define AX_REG_PLLVCODIV 		0x032 	/* PLL Divider Settings */       
#define AX_REG_PLLRANGINGA 		0x033 	/* PLL Autoranging A */       
#define AX_REG_FREQA3 			0x034 	/* Frequency A 3 */       
#define AX_REG_FREQA2 			0x035 	/* Frequency A 2 */       
#define AX_REG_FREQA1 			0x036 	/* Frequency A 1 */       
#define AX_REG_FREQA0 			0x037 	/* Frequency A 0 */       
#define AX_REG_PLLLOOPBOOST 		0x038 	/* PLL Loop Filter Settings (Boosted) */     
#define AX_REG_PLLCPIBOOST 		0x039 	/* PLL Charge Pump Current (Boosted) */     
#define AX_REG_PLLRANGINGB 		0x03B 	/* PLL Autoranging B */       
#define AX_REG_FREQB3 			0x03C 	/* Frequency B 3 */       
#define AX_REG_FREQB2 			0x03D 	/* Frequency B 2 */       
#define AX_REG_FREQB1 			0x03E 	/* Frequency B 1 */       
#define AX_REG_FREQB0 			0x03F 	/* Frequency B 0 */       
#define AX_REG_RSSI 			0x040 	/* Received Signal Strength Indicator */      
#define AX_REG_BGNDRSSI 		0x041 	/* Background RSSI */        
#define AX_REG_DIVERSITY 		0x042 	/* Antenna Diversity Configuration */       
#define AX_REG_AGCCOUNTER 		0x043 	/* AGC Counter */        
#define AX_REG_TRKDATARATE2 		0x045 	/* Datarate Tracking 2 */       
#define AX_REG_TRKDATARATE1 		0x046 	/* Datarate Tracking 1 */       
#define AX_REG_TRKDATARATE0 		0x047 	/* Datarate Tracking 0 */       
#define AX_REG_TRKAMPLITUDE1 		0x048 	/* Amplitude Tracking 1 */       
#define AX_REG_TRKAMPLITUDE0 		0x049 	/* Amplitude Tracking 0 */       
#define AX_REG_TRKPHASE1 		0x04A 	/* Phase Tracking 1 */       
#define AX_REG_TRKPHASE0 		0x04B 	/* Phase Tracking 0 */       
#define AX_REG_TRKRFFREQ2 		0x04D 	/* RF Frequency Tracking 2 */      
#define AX_REG_TRKRFFREQ1 		0x04E 	/* RF Frequency Tracking 1 */      
#define AX_REG_TRKRFFREQ0 		0x04F 	/* RF Frequency Tracking 0 */      
#define AX_REG_TRKFREQ1 		0x050 	/* Frequency Tracking 1 */       
#define AX_REG_TRKFREQ0 		0x051 	/* Frequency Tracking 0 */       
#define AX_REG_TRKFSKDEMOD1 		0x052 	/* FSK Demodulator Tracking 1 */      
#define AX_REG_TRKFSKDEMOD0 		0x053 	/* FSK Demodulator Tracking 0 */      
#define AX_REG_TRKAFSKDEMOD1 		0x054 	/* AFSK Demodulator Tracking 1 */      
#define AX_REG_TRKAFSKDEMOD0 		0x055 	/* AFSK Demodulator Tracking 0 */      
#define AX_REG_TIMER2 			0x059 	/* 1MHz Timer 2 */       
#define AX_REG_TIMER1 			0x05A 	/* 1Mz Timer 1 */       
#define AX_REG_TIMER0 			0x05B 	/* 1MHz Timer 0 */       
#define AX_REG_WAKEUPTIMER1 		0x068 	/* Wakeup Timer 1 */       
#define AX_REG_WAKEUPTIMER0 		0x069 	/* Wakeup Timer 0 */       
#define AX_REG_WAKEUP1 			0x06A 	/* Wakeup Time 1 */       
#define AX_REG_WAKEUP0 			0x06B 	/* Wakeup Time 0 */       
#define AX_REG_WAKEUPFREQ1 		0x06C 	/* Wakeup Frequency 1 */       
#define AX_REG_WAKEUPFREQ0 		0x06D 	/* Wakeup Frequency 0 */       
#define AX_REG_WAKEUPXOEARLY 		0x06E 	/* Wakeup Crystal Oscillator Early */      
#define AX_REG_IFFREQ1 			0x100 	/* 2nd LO / IF Frequency 1 */    
#define AX_REG_IFFREQ0 			0x101 	/* 2nd LO / IF Frequency 0 */    
#define AX_REG_DECIMATION 		0x102 	/* Decimation Factor */        
#define AX_REG_RXDATARATE2 		0x103 	/* Receiver Datarate 2 */       
#define AX_REG_RXDATARATE1 		0x104 	/* Receiver Datarate 1 */       
#define AX_REG_RXDATARATE0 		0x105 	/* Receiver Datarate 0 */       
#define AX_REG_MAXDROFFSET2 		0x106 	/* Maximum Receiver Datarate Offset 2 */     
#define AX_REG_MAXDROFFSET1 		0x107 	/* Maximum Receiver Datarate Offset 1 */     
#define AX_REG_MAXDROFFSET0 		0x108 	/* Maximum Receiver Datarate Offset 0 */     
#define AX_REG_MAXRFOFFSET2 		0x109 	/* Maximum Receiver RF Offset 2 */     
#define AX_REG_MAXRFOFFSET1 		0x10A 	/* Maximum Receiver RF Offset 1 */     
#define AX_REG_MAXRFOFFSET0 		0x10B 	/* Maximum Receiver RF Offset 0 */     
#define AX_REG_FSKDMAX1 		0x10C 	/* Four FSK Rx Maximum Deviation 1 */    
#define AX_REG_FSKDMAX0 		0x10D 	/* Four FSK Rx Maximum Deviation 0 */    
#define AX_REG_FSKDMIN1 		0x10E 	/* Four FSK Rx Minimum Deviation 1 */    
#define AX_REG_FSKDMIN0 		0x10F 	/* Four FSK Rx Minimum Deviation 0 */    
#define AX_REG_AFSKSPACE1 		0x110 	/* AFSK Space (0) Frequency 1 */     
#define AX_REG_AFSKSPACE0 		0x111 	/* AFSK Space (0) Frequency 0 */     
#define AX_REG_AFSKMARK1 		0x112 	/* AFSK Mark (1) Frequency 1 */     
#define AX_REG_AFSKMARK0 		0x113 	/* AFSK Mark (1) Frequency 0 */     
#define AX_REG_AFSKCTRL 		0x114 	/* AFSK Control */        
#define AX_REG_AMPLFILTER 		0x115 	/* Amplitude Filter */        
#define AX_REG_RXPARAMSETS 		0x116 	/* Receiver Parameter Set Indirection */      
#define AX_REG_FREQUENCYLEAK 		0x116 	/* Baseband Frequency Recovery Loop Leakiness */     
#define AX_REG_RXPARAMCURSET 		0x117 	/* Receiver Parameter Current Set */      
#define AX_REG_AGCGAIN0 		0x120 	/* AGC Speed */        
#define AX_REG_AGCTARGET0 		0x121 	/* AGC Target */        
#define AX_REG_TIMEGAIN0 		0x122 	/* Time Estimator Bandwidth */       
#define AX_REG_AGCAHYST0 		0x122 	/* AGC Analog Hysteresis */       
#define AX_REG_DRGAIN0 			0x123 	/* Data Rate Estimator Bandwidth */      
#define AX_REG_AGCMINMAX0 		0x123 	/* AGC Analog Update Behaviour */      
#define AX_REG_PHASEGAIN0 		0x124 	/* Phase Estimator Bandwidth */       
#define AX_REG_FREQUENCYGAINA0 		0x125 	/* Frequency Estimator Bandwidth A */      
#define AX_REG_FREQUENCYGAINB0 		0x126 	/* Frequency Estimator Bandwidth B */      
#define AX_REG_FREQUENCYGAINC0 		0x127 	/* Frequency Estimator Bandwidth C */      
#define AX_REG_FREQUENCYGAIND0 		0x128 	/* Frequency Estimator Bandwidth D */      
#define AX_REG_AMPLITUDEGAIN0 		0x129 	/* Amplitude Estimator Bandwidth */       
#define AX_REG_FREQDEV10 		0x12A 	/* Receiver Frequency Deviation 1 */      
#define AX_REG_FREQDEV00 		0x12B 	/* Receiver Frequency Deviation 0 */      
#define AX_REG_FOURFSK0 		0x12C 	/* Four FSK Control */       
#define AX_REG_BBOFFSRES0 		0x12D 	/* Baseband Offset Compensation Resistors */      
#define AX_REG_AGCGAIN1 		0x12E 	/* AGC Speed */        
#define AX_REG_AGCTARGET1 		0x12F 	/* AGC Target */        
#define AX_REG_TIMEGAIN1 		0x130 	/* Time Estimator Bandwidth */       
#define AX_REG_DRGAIN1 			0x131 	/* Data Rate Estimator Bandwidth */      
#define AX_REG_PHASEGAIN1 		0x132 	/* Phase Estimator Bandwidth */       
#define AX_REG_AGCAHYST1 		0x132 	/* AGC Analog Hysteresis */       
#define AX_REG_FREQUENCYGAINA1 		0x133 	/* Frequency Estimator Bandwidth A */      
#define AX_REG_AGCMINMAX1 		0x133 	/* AGC Analog Update Behaviour */      
#define AX_REG_FREQUENCYGAINB1 		0x134 	/* Frequency Estimator Bandwidth B */      
#define AX_REG_FREQUENCYGAINC1 		0x135 	/* Frequency Estimator Bandwidth C */      
#define AX_REG_FREQUENCYGAIND1 		0x136 	/* Frequency Estimator Bandwidth D */      
#define AX_REG_AMPLITUDEGAIN1 		0x137 	/* Amplitude Estimator Bandwidth */       
#define AX_REG_FREQDEV11 		0x138 	/* Receiver Frequency Deviation 1 */      
#define AX_REG_FREQDEV01 		0x139 	/* Receiver Frequency Deviation 0 */      
#define AX_REG_FOURFSK1 		0x13A 	/* Four FSK Control */       
#define AX_REG_BBOFFSRES1 		0x13B 	/* Baseband Offset Compensation Resistors */      
#define AX_REG_AGCGAIN2 		0x13C 	/* AGC Speed */        
#define AX_REG_AGCTARGET2 		0x13D 	/* AGC Target */        
#define AX_REG_TIMEGAIN2 		0x13E 	/* Time Estimator Bandwidth */       
#define AX_REG_DRGAIN2 			0x13F 	/* Data Rate Estimator Bandwidth */      
#define AX_REG_PHASEGAIN2 		0x140 	/* Phase Estimator Bandwidth */       
#define AX_REG_FREQUENCYGAINA2 		0x141 	/* Frequency Estimator Bandwidth A */      
#define AX_REG_FREQUENCYGAINB2 		0x142 	/* Frequency Estimator Bandwidth B */      
#define AX_REG_AGCAHYST2 		0x142 	/* AGC Analog Hysteresis */       
#define AX_REG_FREQUENCYGAINC2 		0x143 	/* Frequency Estimator Bandwidth C */      
#define AX_REG_AGCMINMAX2 		0x143 	/* AGC Analog Update Behaviour */      
#define AX_REG_FREQUENCYGAIND2 		0x144 	/* Frequency Estimator Bandwidth D */      
#define AX_REG_AMPLITUDEGAIN2 		0x145 	/* Amplitude Estimator Bandwidth */       
#define AX_REG_FREQDEV12 		0x146 	/* Receiver Frequency Deviation 1 */      
#define AX_REG_FREQDEV02 		0x147 	/* Receiver Frequency Deviation 0 */      
#define AX_REG_FOURFSK2 		0x148 	/* Four FSK Control */       
#define AX_REG_BBOFFSRES2 		0x149 	/* Baseband Offset Compensation Resistors */      
#define AX_REG_AGCGAIN3 		0x14A 	/* AGC Speed */        
#define AX_REG_AGCTARGET3 		0x14B 	/* AGC Target */        
#define AX_REG_TIMEGAIN3 		0x14C 	/* Time Estimator Bandwidth */       
#define AX_REG_DRGAIN3 			0x14D 	/* Data Rate Estimator Bandwidth */      
#define AX_REG_PHASEGAIN3 		0x14E 	/* Phase Estimator Bandwidth */       
#define AX_REG_FREQUENCYGAINA3 		0x14F 	/* Frequency Estimator Bandwidth A */      
#define AX_REG_FREQUENCYGAINB3 		0x150 	/* Frequency Estimator Bandwidth B */      
#define AX_REG_FREQUENCYGAINC3 		0x151 	/* Frequency Estimator Bandwidth C */      
#define AX_REG_FREQUENCYGAIND3 		0x152 	/* Frequency Estimator Bandwidth D */      
#define AX_REG_AGCAHYST3 		0x152 	/* AGC Analog Hysteresis */       
#define AX_REG_AMPLITUDEGAIN3 		0x153 	/* Amplitude Estimator Bandwidth */       
#define AX_REG_AGCMINMAX3 		0x153 	/* AGC Analog Update Behaviour */      
#define AX_REG_FREQDEV13 		0x154 	/* Receiver Frequency Deviation 1 */      
#define AX_REG_FREQDEV03 		0x155 	/* Receiver Frequency Deviation 0 */      
#define AX_REG_FOURFSK3 		0x156 	/* Four FSK Control */       
#define AX_REG_BBOFFSRES3 		0x157 	/* Baseband Offset Compensation Resistors */      
#define AX_REG_MODCFGF 			0x160 	/* Modulator Configuration F */       
#define AX_REG_FSKDEV2 			0x161 	/* FSK Deviation 2 */       
#define AX_REG_FSKDEV1 			0x162 	/* FSK Deviation 1 */       
#define AX_REG_FSKDEV0 			0x163 	/* FSK Deviation 0 */       
#define AX_REG_MODCFGA 			0x164 	/* Modulator Configuration A */       
#define AX_REG_TXRATE2 			0x165 	/* Transmitter Bitrate 2 */       
#define AX_REG_TXRATE1 			0x166 	/* Transmitter Bitrate 1 */       
#define AX_REG_TXRATE0 			0x167 	/* Transmitter Bitrate 0 */       
#define AX_REG_TXPWRCOEFFA1 		0x168 	/* Transmitter Predistortion Coefficient A 1 */     
#define AX_REG_TXPWRCOEFFA0 		0x169 	/* Transmitter Predistortion Coefficient A 0 */     
#define AX_REG_TXPWRCOEFFB1 		0x16A 	/* Transmitter Predistortion Coefficient B 1 */     
#define AX_REG_TXPWRCOEFFB0 		0x16B 	/* Transmitter Predistortion Coefficient B 0 */     
#define AX_REG_TXPWRCOEFFC1 		0x16C 	/* Transmitter Predistortion Coefficient C 1 */     
#define AX_REG_TXPWRCOEFFC0 		0x16D 	/* Transmitter Predistortion Coefficient C 0 */     
#define AX_REG_TXPWRCOEFFD1 		0x16E 	/* Transmitter Predistortion Coefficient D 1 */     
#define AX_REG_TXPWRCOEFFD0 		0x16F 	/* Transmitter Predistortion Coefficient D 0 */     
#define AX_REG_TXPWRCOEFFE1 		0x170 	/* Transmitter Predistortion Coefficient E 1 */     
#define AX_REG_TXPWRCOEFFE0 		0x171 	/* Transmitter Predistortion Coefficient E 0 */     
#define AX_REG_PLLVCOI 			0x180 	/* PLL VCO Current */       
#define AX_REG_PLLVCOIR 		0x181 	/* PLL VCO Current Readback */      
#define AX_REG_PLLLOCKDET 		0x182 	/* PLL Lock Detect Delay */      
#define AX_REG_PLLRNGCLK 		0x183 	/* PLL Autoranging Clock */       
#define AX_REG_XTALCAP 			0x184 	/* Crystal Oscillator Load Capacitance */      
#define AX_REG_BBTUNE 			0x188 	/* Baseband Tuning */        
#define AX_REG_BBOFFSCAP 		0x189 	/* Baseband Offset Compensation Capacitors */      
#define AX_REG_PKTADDRCFG 		0x201 	/* Packet Address Config */       
#define AX_REG_PKTADDR1 		0x202 	/* Packet Address 1 */       
#define AX_REG_PKTADDR0 		0x203 	/* Packet Address 0 */       
#define AX_REG_PKTADDRMASK1 		0x204 	/* Packet Address Mask 1 */      
#define AX_REG_PKTADDR3 		0x204 	/* Packet Address 3 */       
#define AX_REG_PKTADDRMASK0 		0x205 	/* Packet Address Mask 0 */      
#define AX_REG_PKTADDR2 		0x205 	/* Packet Address 2 */       
#define AX_REG_PKTLENCFG 		0x206 	/* Packet Length Configuration */       
#define AX_REG_PKTLENOFFSET 		0x207 	/* Packet Length Offset */       
#define AX_REG_PKTMAXLEN 		0x208 	/* Packet Maximum Length */       
#define AX_REG_PKTADDRMASK3 		0x208 	/* Packet Address Mask 3 */      
#define AX_REG_PKTADDRMASK2 		0x209 	/* Packet Address Mask 2 */      
#define AX_REG_MATCH0PAT3 		0x210 	/* Pattern Match Unit 0 Pattern 3 */    
#define AX_REG_MATCH0PAT2 		0x211 	/* Pattern Match Unit 0 Pattern 2 */    
#define AX_REG_MATCH0PAT1 		0x212 	/* Pattern Match Unit 0 Pattern 1 */    
#define AX_REG_MATCH0PAT0 		0x213 	/* Pattern Match Unit 0 Pattern 0 */    
#define AX_REG_MATCH0LEN 		0x214 	/* Pattern Match Unit 0 Pattern Length */    
#define AX_REG_MATCH0MIN 		0x215 	/* Pattern Match Unit 0 Minimum Match */    
#define AX_REG_MATCH0MAX 		0x216 	/* Pattern Match Unit 0 Maximum Match */    
#define AX_REG_MATCH1PAT1 		0x218 	/* Pattern Match Unit 1 Pattern 1 */    
#define AX_REG_MATCH1PAT0 		0x219 	/* Pattern Match Unit 1 Pattern 0 */    
#define AX_REG_MATCH1LEN 		0x21C 	/* Pattern Match Unit 1 Pattern Length */    
#define AX_REG_MATCH1MIN 		0x21D 	/* Pattern Match Unit 1 Minimum Match */    
#define AX_REG_MATCH1MAX 		0x21E 	/* Pattern Match Unit 1 Maximum Match */    
#define AX_REG_TMGTXBOOST 		0x220 	/* Transmit PLL Boost Time */      
#define AX_REG_TMGTXSETTLE 		0x221 	/* Transmit PLL (post Boost) Settling Time */    
#define AX_REG_TMGRXBOOST 		0x223 	/* Receive PLL Boost Time */      
#define AX_REG_TMGRXSETTLE 		0x224 	/* Receive PLL (post Boost) Settling Time */    
#define AX_REG_TMGRXOFFSACQ 		0x225 	/* Receive Baseband DC Offset Acquisition Time */    
#define AX_REG_TMGRXCOARSEAGC 		0x226 	/* Receive Coarse AGC Time */      
#define AX_REG_TMGRXAGC 		0x227 	/* Receiver AGC Settling Time */      
#define AX_REG_TMGRXRSSI 		0x228 	/* Receiver RSSI Settling Time */      
#define AX_REG_TMGRXPREAMBLE1 		0x229 	/* Receiver Preamble 1 Timeout */      
#define AX_REG_TMGRXPREAMBLE2 		0x22A 	/* Receiver Preamble 2 Timeout */      
#define AX_REG_TMGRXPREAMBLE3 		0x22B 	/* Receiver Preamble 3 Timeout */      
#define AX_REG_RSSIREFERENCE 		0x22C 	/* RSSI Offset */        
#define AX_REG_RSSIABSTHR 		0x22D 	/* RSSI Absolute Threshold */       
#define AX_REG_BGNDRSSIGAIN 		0x22E 	/* Background RSSI Averaging Time Constant */     
#define AX_REG_BGNDRSSITHR 		0x22F 	/* Background RSSI Relative Threshold */      
#define AX_REG_PKTCHUNKSIZE 		0x230 	/* Packet Chunk Size */       
#define AX_REG_PKTMISCFLAGS 		0x231 	/* Packet Controller Miscellaneous Flags */      
#define AX_REG_PKTSTOREFLAGS 		0x232 	/* Packet Controller Store Flags */      
#define AX_REG_PKTACCEPTFLAGS 		0x233 	/* Packet Controller Accept Flags */      
#define AX_REG_GPADCCTRL 		0x300 	/* General Purpose ADC Control */      
#define AX_REG_GPADCPERIOD 		0x301 	/* GPADC Sampling Period */       
#define AX_REG_GPADC13VALUE1 		0x308 	/* GPADC13 Value 1 */       
#define AX_REG_GPADC13VALUE0 		0x309 	/* GPADC13 Value 0 */       
#define AX_REG_LPOSCCONFIG 		0x310 	/* Low Power Oscillator Calibration Configuration */     
#define AX_REG_LPOSCSTATUS 		0x311 	/* Low Power Oscillator Calibration Status */     
#define AX_REG_LPOSCKFILT1 		0x312 	/* Low Power Oscillator Calibration Filter Constant High Byte */  
#define AX_REG_LPOSCKFILT0 		0x313 	/* Low Power Oscillator Calibration Filter Constant Low Byte */  
#define AX_REG_LPOSCREF1 		0x314 	/* Low Power Oscillator Reference Frequency High Byte */   
#define AX_REG_LPOSCREF0 		0x315 	/* Low Power Oscillator Reference Frequency Low Byte */   
#define AX_REG_LPOSCFREQ1 		0x316 	/* Low Power Oscillator Frequency Tuning High Byte */   
#define AX_REG_LPOSCFREQ0 		0x317 	/* Low Power Oscillator Frequency Tuning Low Byte */   
#define AX_REG_LPOSCPER1 		0x318 	/* Low Power Oscillator Period High Byte */    
#define AX_REG_LPOSCPER0 		0x319 	/* Low Power Oscillator Period Low Byte */    
#define AX_REG_DACVALUE1 		0x330 	/* DAC Value 1 */       
#define AX_REG_DACVALUE0 		0x331 	/* DAC Value 0 */       
#define AX_REG_DACCONFIG 		0x332 	/* DAC Configuration */        
#define AX_REG_POWCTRL1 		0xF08 	/* Power Control 1 */       
#define AX_REG_REF 			0xF0D 	/* Reference */         
#define AX_REG_XTALOSC 			0xF10 	/* Crystal Oscillator Control */       
#define AX_REG_XTALAMPL 		0xF11 	/* Crystal Oscillator Amplitude Control */      


#define AX_REG_POWSTAT_SVIO_MASK 	(1<<0)  /* IOVoltage good*/ 
#define AX_REG_POWSTAT_SBEVMODEM_MASK 	(1<<1)  /* Modem Voltage Good*/ 
#define AX_REG_POWSTAT_SBEVANA_MASK 	(1<<2)  /* Analog voltage okay*/ 
#define AX_REG_POWSTAT_SVMODEM_MASK 	(1<<3)  /* Modem Vreg ready*/ 
#define AX_REG_POWSTAT_SVANA_MASK 	(1<<4)  /* Analog vreg ready*/ 
#define AX_REG_POWSTAT_SVREF_MASK 	(1<<5)  /* Ref Vreg ready*/ 
#define AX_REG_POWSTAT_SREF_MASK 	(1<<6)  /* Reference ready*/ 
#define AX_REG_POWSTAT_SSUM_MASK 	(1<<7)  /* Indicates all power sources are ready, Just check this guy. */ 

#define AX_REG_POWIRQMASK_MSVIO_MASK 	(1<<0)  /* IOVoltage good*/ 
#define AX_REG_POWIRQMASK_MSBEVMODEM_MASK (1<<1)  /* Modem Voltage Good*/ 
#define AX_REG_POWIRQMASK_MSBEVANA_MASK (1<<2)  /* Analog voltage okay*/ 
#define AX_REG_POWIRQMASK_MSVMODEM_MASK (1<<3)  /* Modem Vreg ready*/ 
#define AX_REG_POWIRQMASK_MSVANA_MASK 	(1<<4)  /* Analog vreg ready*/ 
#define AX_REG_POWIRQMASK_MSVREF_MASK 	(1<<5)  /* Ref Vreg ready*/ 
#define AX_REG_POWIRQMASK_MSREF_MASK 	(1<<6)  /* Reference ready*/ 
#define AX_REG_POWIRQMASK_MSSUM_MASK 	(1<<7)  /* Indicates all power sources are ready, Just check this bit */

#define AX_REG_PWRMODE_POWERDOWN_MASK 	(0x00) /* All circuits powered down*/ 
#define AX_REG_PWRMODE_DEEP_SLEEP_MASK 	(0x01) /* Deep sleep, all registers dead, lost contents*/ 
#define AX_REG_PWRMODE_XTALEN_MASK 	(0x05) /* Xtal osc is en*/ 
#define AX_REG_PWRMODE_FIFOEN_MASK 	(0x07)
#define AX_REG_PWRMODE_SYNTH_RUN_RX_MASK (0x08) /* Synth is running , its in receive mode*/ 
#define AX_REG_PWRMODE_RX_RUN_MASK 	(0x09)
#define AX_REG_IRQINVERSION0_FIFO_NOTFULL_MASK 	(1<<1) /* FIFO not full inturruyt inversion*/ 
#define AX_REG_IRQINVERSION0_FIFO_THRCNT_MASK 	(1<<2) /* FIFO count > threshold interrupt inversion*/ 
#define AX_REG_IRQINVERSION0_FIFO_THRFREE_MASK 	(1<<3) /* FIFO free > threshold interrupt inversion*/ 
#define AX_REG_IRQINVERSION0_FIFO_ERROR_MASK 	(1<<4) /* FIFO error interrupt inversion*/ 
#define AX_REG_IRQINVERSION0_PLL_UNLOCK_MASK 	(1<<5) /* PLL lock lost inturrupt inversion*/ 
#define AX_REG_IRQINVERSION0_RADIO_CTRL_MASK 	(1<<6) /* Radio controller inturrupt inversion*/ 
#define AX_REG_IRQINVERSION0_POWER_MASK 	 	(1<<7) /* Power interrupt inversion*/ 
#define AX_REG_IRQINVERSION1_XTAL_READY_MASK 	(1<<0) /* Crystal oscillator ready interrupt inversion*/ 
#define AX_REG_IRQINVERSION1_WAKEUP_TIMER_MASK 	(1<<1) /* Wakeup timer interrupt inversion*/ 
#define AX_REG_IRQINVERSION1_LP_OSC_MASK 		(1<<2) /* Low power oscillator inturrupt inversion*/ 
#define AX_REG_IRQINVERSION1_GPADC_MASK 		(1<<3) /* GPADC interrupt inversion*/ 
#define AX_REG_IRQINVERSION1_PLL_RNG_DONE_MASK 	(1<<4) /* PLL autoranging done interrupt inversion*/ 


#define AX_REG_MODULATION_ASK_MASK 		(0x00)
#define AX_REG_MODULATION_ASK_COHERENT_MASK 	(0x01)
#define AX_REG_MODULATION_PSK_MASK 		(0x04)
#define AX_REG_MODULATION_OQSK_MASK 		(0x06)
#define AX_REG_MODULATION_MSK_MASK 		(0x07)
#define AX_REG_MODULATION_FSK_MASK 		(0x08)
#define AX_REG_MODULATION_4FSK_MASK 		(0x09)
#define AX_REG_MODULATION_AFSK_MASK 		(0x0A)
#define AX_REG_MODULATION_FM_MASK 		(0x0B)
#define AX_REG_MODULATION_RX_HALFSPEED_MASK 	(1<<4) /* Sets the receiver to half speed bitrate*/ 


#define AX_REG_ENCODING_INV_MASK 		(1<<0)  /* Invert data if set to 1*/ 
#define AX_REG_ENCODING_DIFF_MASK 		(1<<1)  /* Enable differential encode/decode*/ 
#define AX_REG_ENCODING_SCRAM_MASK 		(1<<2)  /* Enable the scrambler*/ 
#define AX_REG_ENCODING_MANCH_MASK 		(1<<3)  /* Enable manchester encoding*/ 
#define AX_REG_ENCODING_NOSYNC_MASK 		(1<<4)  /* Disable dibit sync in 4fsk mode*/ 
/* To use NRZI, set inv to high, and set diff to 1*/ 


#define AX_REG_FRAMING_FABORT_MASK 		(1<<0)
#define AX_REG_FRAMING_FRMMODE_RAW_MASK		(0x00 << 1)
#define AX_REG_FRAMING_FRMMODE_RAW_SOFT_MASK	(0x01 << 1)
#define AX_REG_FRAMING_FRMMODE_HDLC_MASK	(0x02 << 1)
#define AX_REG_FRAMING_FRMMODE_RAW_PAT_MATCH_MASK (0x03 << 1)
#define AX_REG_FRAMING_FRMMODE_MBUS_MASK	(0x04 << 1)
#define AX_REG_FRAMING_FRMMODE_MBUS_4TO6_MASK	(0x05 << 1)

#define AX_REG_FRAMING_CRC_OFF_MASK 		(0x00 << 4)
#define AX_REG_FRAMING_CRC_CCITT_MASK 		(0x01 << 4)
#define AX_REG_FRAMING_CRC_CRC16_MASK 		(0x02 << 4)
#define AX_REG_FRAMING_CRC_DNP_MASK 		(0x03 << 4)
#define AX_REG_FRAMING_CRC_CRC32_MASK 		(0x04 << 4)

#define AX_REG_FRAMING_FRMRX_MASK 		(0x01 << 7) /* Flag set when flag is detected in HDLC mode or when preamble matches in raw pattern mode. Cleared by writting 1 to FABORT*/ 



#define AX_REG_FEC_FECEN_MASK 			(1<<0) /* Enable FEC*/ 

#define AX_REG_RADIOSTATE_IDLE_MASK 		(0x00)
#define AX_REG_RADIOSTATE_POWER_DOWN_MASK 	(0x01)
#define AX_REG_RADIOSTATE_TX_PLL_MASK 		(0x04)
#define AX_REG_RADIOSTATE_TX_MASK 		(0x06)
#define AX_REG_RADIOSTATE_TX_TAIL_MASK 		(0x07)
#define AX_REG_RADIOSTATE_RX_PLL_MASK 		(0x08)
#define AX_REG_RADIOSTATE_RX_ANT_MASK 		(0x09)
#define AX_REG_RADIOSTATE_RX_PREAMBLE_1_MASK 	(0x0C)
#define AX_REG_RADIOSTATE_RX_PREAMBLE_1_MASK 	(0x0D)
#define AX_REG_RADIOSTATE_RX_PREAMBLE_1_MASK 	(0x0E)
#define AX_REG_RADIOSTATE_RX_MASK 	 	(0x0F)


#define AX_REG_XTALSTATUS_MASK 			(0x01) /* A 1 indicates that the crystal oscilator is up and running. */ 


#define AX_REG_PINSTATE_SYSCLK_MASK 		(1<<0)
#define AX_REG_PINSTATE_DCLK_MASK 		(1<<1)
#define AX_REG_PINSTATE_DATA_MASK 		(1<<2)
#define AX_REG_PINSTATE_IRQ_MASK 		(1<<3)
#define AX_REG_PINSTATE_ANTSEL_MASK 		(1<<4)
#define AX_REG_PINSTATE_PWRAMP_MASK 		(1<<5)

#define AX_REG_PINFUNSYSCLK_OUT_ZERO_MASK 	(0x00)
#define AX_REG_PINFUNSYSCLK_OUT_ONE_MASK 	(0x01)
#define AX_REG_PINFUNSYSCLK_OUT_HIGHZ_MASK 	(0x02)
#define AX_REG_PINFUNSYSCLK_OUT_INV_XTAL_MASK 	(0x03)
#define AX_REG_PINFUNSYSCLK_OUT_XTAL_MASK 	(0x04)
#define AX_REG_PINFUNSYSCLK_OUT_XTAL_DIV2_MASK 	(0x05)
#define AX_REG_PINFUNSYSCLK_OUT_XTAL_DIV4_MASK 	(0x06)
#define AX_REG_PINFUNSYSCLK_OUT_XTAL_DIV8_MASK 	(0x07)
#define AX_REG_PINFUNSYSCLK_OUT_XTAL_DIV16_MASK (0x08)
#define AX_REG_PINFUNSYSCLK_OUT_XTAL_DIV32_MASK (0x09)
#define AX_REG_PINFUNSYSCLK_OUT_XTAL_DIV64_MASK (0x0A)
#define AX_REG_PINFUNSYSCLK_OUT_XTAL_DIV128_MASK 	(0x0B)
#define AX_REG_PINFUNSYSCLK_OUT_XTAL_DIV256_MASK 	(0x0C)
#define AX_REG_PINFUNSYSCLK_OUT_XTAL_DIV512_MASK 	(0x0D)
#define AX_REG_PINFUNSYSCLK_OUT_XTAL_DIV1024_MASK 	(0x0E)
#define AX_REG_PINFUNSYSCLK_OUT_LP_OSC_MASK 		(0x0F)
#define AX_REG_PINFUNSYSCLK_OUT_TEST_OBS_OSC_MASK 	(0x1F)

#define AX_REG_PINFUNSYSCLK_PUSYCLK_MASK 	(1<<7) /* Enables the weak pullup*/ 


#define AX_REG_PINFUNCIRQ_ZERO_MASK 		(0x00)
#define AX_REG_PINFUNCIRQ_ONE_MASK 		(0x01)
#define AX_REG_PINFUNCIRQ_HIGH_Z_MASK 		(0x02)
#define AX_REG_PINFUNCIRQ_IRQ_MASK 		(0x03) /* Enables the IRQ output*/ 
#define AX_REG_PINFUNCIRQ_TEST_OBS_MASK 	(0x07)
#define AX_REG_PINFUNCIRQ_PIIRQ_MASK 		(1 << 6) /* Inverts the data on the IRQ line*/ 
#define AX_REG_PINFUNCIRQ_PUIRQ_MASK 		(1 << 7) /* Enables the weak pullup on the IRQ line*/ 


#define AX_REG_PINFUNCANTSEL_ZERO_MASK 		(0x00) /* Outputs zero on the antenna select pin*/ 
#define AX_REG_PINFUNCANTSEL_ONE_MASK 		(0x01)
#define AX_REG_PINFUNCANTSEL_HIGH_Z_MASK 	(0x02)
#define AX_REG_PINFUNCANTSEL_BASEBAND_CLK_MASK 	(0x03)
#define AX_REG_PINFUNCANTSEL_EXTERNAL_TCXO_MASK (0x04)
#define AX_REG_PINFUNCANTSEL_DAC_MASK 		(0x05)
#define AX_REG_PINFUNCANTSEL_DIVERSITY_ANT_SEL_MASK (0x06)
#define AX_REG_PINFUNCANTSEL_TEST_OBS_MASK 	(0x07)
#define AX_REG_PINFUNCANTSEL_INV_MASK 	 	(1<<6)
#define AX_REG_PINFUNCANTSEL_PULLUP_MASK 	(1<<7)

struct reg_pair{
	uint16_t address;
	uint8_t  data;
} ;
typedef struct reg_pair reg_pair;
struct ax_settings{ /* Register setting struct */ 
	reg_pair MODULATION;
	reg_pair ENCODING;
	reg_pair FRAMING; 
	reg_pair PINFUNCSYSCLK;
	reg_pair PINFUNCANTSEL;
	reg_pair PINFUNCPWRAMP;
	reg_pair WAKEUPXOEARLY;
	reg_pair IFFREQ1;
	reg_pair IFFREQ0;
	reg_pair DECIMATION;
	reg_pair RXDATARATE2;
	reg_pair RXDATARATE1;
	reg_pair RXDATARATE0;
	reg_pair MAXDROFFSET2;
	reg_pair MAXDROFFSET1;
	reg_pair MAXDROFFSET0;
	reg_pair MAXRFOFFSET2;
	reg_pair MAXRFOFFSET1;
	reg_pair MAXRFOFFSET0;
	reg_pair FSKDMAX1;
	reg_pair FSKDMAX0;
	reg_pair FSKDMIN1;
	reg_pair FSKDMIN0;
	reg_pair AMPLFILTER;
	reg_pair RXPARAMSETS;
	reg_pair AGCGAIN0;
	reg_pair AGCTARGET0;
	reg_pair TIMEGAIN0;
	reg_pair DRGAIN0;
	reg_pair PHASEGAIN0;
	reg_pair FREQUENCYGAINA0;
	reg_pair FREQUENCYGAINB0;
	reg_pair FREQUENCYGAINC0;
	reg_pair FREQUENCYGAIND0;
	reg_pair AMPLITUDEGAIN0;
	reg_pair FREQDEV10;
	reg_pair FREQDEV00;
	reg_pair BBOFFSRES0;
	reg_pair AGCGAIN1;
	reg_pair AGCTARGET1;
	reg_pair AGCAHYST1;
	reg_pair AGCMINMAX1;
	reg_pair TIMEGAIN1;
	reg_pair DRGAIN1;
	reg_pair PHASEGAIN1;
	reg_pair FREQUENCYGAINA1;
	reg_pair FREQUENCYGAINB1;
	reg_pair FREQUENCYGAINC1; 
}; 
struct ax_settings ax_reg_settings = {
.MODULATION  =  { .address = AX_REG_MODULATION, 		.data = 0x08},
.ENCODING ={ .address = AX_REG_ENCODING,			.data=0x00},
.FRAMING = { .address=AX_REG_FRAMING,			  .data=0x14},
.PINFUNCANTSEL  = { .address=AX_REG_PINFUNCANTSEL,	  .data=0x05},
.PINFUNCPWRAMP  = { .address=AX_REG_PINFUNCPWRAMP,	  .data=0x00},
.WAKEUPXOEARLY  = { .address=AX_REG_WAKEUPXOEARLY,	  .data=0x01},
.IFFREQ1  = { .address=AX_REG_IFFREQ1,			  .data=0x00},
.IFFREQ0  = { .address=AX_REG_IFFREQ0,			  .data=0x89},
.DECIMATION  = { .address=AX_REG_DECIMATION,	       	  .data=0x7F},
.RXDATARATE2  = { .address=AX_REG_RXDATARATE2,		  .data=0x00},
.RXDATARATE1  = { .address=AX_REG_RXDATARATE1,		  .data=0x4E},
.RXDATARATE0  = { .address=AX_REG_RXDATARATE0,		  .data=0xBD},
.MAXDROFFSET2  = { .address=AX_REG_MAXDROFFSET2,	  .data=0x00},
.MAXDROFFSET1  = { .address=AX_REG_MAXDROFFSET1,	  .data=0x00},
.MAXDROFFSET0  = { .address=AX_REG_MAXDROFFSET0,	  .data=0x00},
.MAXRFOFFSET2  = { .address=AX_REG_MAXRFOFFSET2,	  .data=0x80},
.MAXRFOFFSET1  = { .address=AX_REG_MAXRFOFFSET1,	  .data=0x00},
.MAXRFOFFSET0  = { .address=AX_REG_MAXRFOFFSET0,	  .data=0x66},
.FSKDMAX1  = { .address=AX_REG_FSKDMAX1,		  .data=0x00},
.FSKDMAX0  = { .address=AX_REG_FSKDMAX0,		  .data=0xA6},
.FSKDMIN1  = { .address=AX_REG_FSKDMIN1,		  .data=0xFF},
.FSKDMIN0  = { .address=AX_REG_FSKDMIN0,		  .data=0x5A},
.AMPLFILTER  = { .address=AX_REG_AMPLFILTER,		  .data=0x00},
.RXPARAMSETS  = { .address=AX_REG_RXPARAMSETS,		  .data=0xF4},
.AGCGAIN0  = { .address=AX_REG_AGCGAIN0,		  .data=0xE8},
.AGCTARGET0  = { .address=AX_REG_AGCTARGET0,		  .data=0x84},
.TIMEGAIN0  = { .address=AX_REG_TIMEGAIN0,		  .data=0x99},
.DRGAIN0  = { .address=AX_REG_DRGAIN0,			  .data=0x93},
.PHASEGAIN0  = { .address=AX_REG_PHASEGAIN0,		  .data=0x83},
.FREQUENCYGAINA0  = { .address=AX_REG_FREQUENCYGAINA0,	  .data=0x0F},
.FREQUENCYGAINB0  = { .address=AX_REG_FREQUENCYGAINB0,	  .data=0x1F},
.FREQUENCYGAINC0  = { .address=AX_REG_FREQUENCYGAINC0,	  .data=0x0B},
.FREQUENCYGAIND0  = { .address=AX_REG_FREQUENCYGAIND0,	  .data=0x0B},
.AMPLITUDEGAIN0  = { .address=AX_REG_AMPLITUDEGAIN0,	  .data=0x06},
.FREQDEV10  = { .address=AX_REG_FREQDEV10,		  .data=0x00},
.FREQDEV00  = { .address=AX_REG_FREQDEV00,		  .data=0x00},
.BBOFFSRES0  = { .address=AX_REG_BBOFFSRES0,		  .data=0x00},
.AGCGAIN1  = { .address=AX_REG_AGCGAIN1,		  .data=0xE8},
.AGCTARGET1  = { .address=AX_REG_AGCTARGET1,		  .data=0x84},
.AGCAHYST1  = { .address=AX_REG_AGCAHYST1,		  .data=0x00},
.AGCMINMAX1  = { .address=AX_REG_AGCMINMAX1,		  .data=0x00},
.TIMEGAIN1  = { .address=AX_REG_TIMEGAIN1,		  .data=0x97},
.DRGAIN1  = { .address=AX_REG_DRGAIN1,			  .data=0x92},
.PHASEGAIN1  = { .address=AX_REG_PHASEGAIN1,		  .data=0x83},
.FREQUENCYGAINA1  = { .address=AX_REG_FREQUENCYGAINA1,	  .data=0x0F},
.FREQUENCYGAINB1  = { .address=AX_REG_FREQUENCYGAINB1,	  .data=0x1F},
.FREQUENCYGAINC1  = { .address=AX_REG_FREQUENCYGAINC1,	  .data=0x0B},
};
