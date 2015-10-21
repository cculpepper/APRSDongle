EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:lt6105
LIBS:tps563200
LIBS:lt3652
LIBS:lt4415
LIBS:msp430
LIBS:KL03-QFN24
LIBS:ncp508
LIBS:hardwareRev1-cache
LIBS:powerRev2-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LT3652 U5
U 1 1 56114C94
P 5850 3100
F 0 "U5" H 5850 3400 60  0000 C CNN
F 1 "LT3652" H 5900 2850 60  0000 C CNN
F 2 "" H 5850 2400 60  0000 C CNN
F 3 "" H 5850 2400 60  0000 C CNN
	1    5850 3100
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 56114CEB
P 3450 3150
F 0 "C13" H 3450 3250 40  0000 L CNN
F 1 "C" H 3456 3065 40  0000 L CNN
F 2 "" H 3488 3000 30  0000 C CNN
F 3 "" H 3450 3150 60  0000 C CNN
	1    3450 3150
	1    0    0    -1  
$EndComp
$Comp
L R R27
U 1 1 56114D05
P 3850 2900
F 0 "R27" V 3930 2900 40  0000 C CNN
F 1 "13.7k" V 3857 2901 40  0000 C CNN
F 2 "" V 3780 2900 30  0000 C CNN
F 3 "" H 3850 2900 30  0000 C CNN
	1    3850 2900
	0    1    1    0   
$EndComp
$Comp
L R R28
U 1 1 56114DC8
P 4150 3200
F 0 "R28" V 4230 3200 40  0000 C CNN
F 1 "10k" V 4157 3201 40  0000 C CNN
F 2 "" V 4080 3200 30  0000 C CNN
F 3 "" H 4150 3200 30  0000 C CNN
	1    4150 3200
	1    0    0    -1  
$EndComp
Text HLabel 3200 2800 0    60   Input ~ 0
Vin
$Comp
L C C15
U 1 1 56114F88
P 6700 2650
F 0 "C15" H 6700 2750 40  0000 L CNN
F 1 "1uf" H 6706 2565 40  0000 L CNN
F 2 "" H 6738 2500 30  0000 C CNN
F 3 "" H 6700 2650 60  0000 C CNN
	1    6700 2650
	1    0    0    -1  
$EndComp
$Comp
L INDUCTOR L2
U 1 1 56114FE2
P 8300 2900
F 0 "L2" V 8250 2900 40  0000 C CNN
F 1 "5.6uh" V 8400 2900 40  0000 C CNN
F 2 "" H 8300 2900 60  0000 C CNN
F 3 "" H 8300 2900 60  0000 C CNN
	1    8300 2900
	1    0    0    -1  
$EndComp
$Comp
L DIODESCH D7
U 1 1 56115039
P 8850 2550
F 0 "D7" H 8850 2650 40  0000 C CNN
F 1 "CMSH3-40MA" H 8850 2450 40  0000 C CNN
F 2 "" H 8850 2550 60  0000 C CNN
F 3 "" H 8850 2550 60  0000 C CNN
	1    8850 2550
	-1   0    0    1   
$EndComp
Text HLabel 9050 2550 2    60   Input ~ 0
GND
$Comp
L C C16
U 1 1 561153DF
P 7900 3750
F 0 "C16" H 7900 3850 40  0000 L CNN
F 1 "10uf" H 7906 3665 40  0000 L CNN
F 2 "" H 7938 3600 30  0000 C CNN
F 3 "" H 7900 3750 60  0000 C CNN
	1    7900 3750
	1    0    0    -1  
$EndComp
$Comp
L BATTERY BT1
U 1 1 5611543C
P 9050 3850
F 0 "BT1" H 9050 4050 50  0000 C CNN
F 1 "BATTERY" H 9050 3660 50  0000 C CNN
F 2 "" H 9050 3850 60  0000 C CNN
F 3 "" H 9050 3850 60  0000 C CNN
	1    9050 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	6450 2800 6450 2400
Wire Wire Line
	6450 2400 8300 2400
Wire Wire Line
	6700 2450 6700 2400
Connection ~ 6700 2400
Wire Wire Line
	8300 2400 8300 2600
Wire Wire Line
	8300 2550 8650 2550
Connection ~ 8300 2550
Wire Wire Line
	6450 2900 7000 2900
Wire Wire Line
	6700 2850 6700 2900
Connection ~ 6700 2900
Wire Wire Line
	7900 2900 7900 3550
$Comp
L R R34
U 1 1 56115725
P 8600 3250
F 0 "R34" V 8680 3250 40  0000 C CNN
F 1 ".1" V 8607 3251 40  0000 C CNN
F 2 "" V 8530 3250 30  0000 C CNN
F 3 "" H 8600 3250 30  0000 C CNN
	1    8600 3250
	0    1    1    0   
$EndComp
Wire Wire Line
	6450 3000 7000 3000
Wire Wire Line
	7000 3000 7000 3250
Wire Wire Line
	7000 3250 8350 3250
Wire Wire Line
	8300 3200 8300 3250
Connection ~ 8300 3250
Wire Wire Line
	8850 3250 9650 3250
Wire Wire Line
	9050 3250 9050 3550
Wire Wire Line
	6450 3100 6900 3100
Wire Wire Line
	6900 3100 6900 3350
Wire Wire Line
	6900 3350 8400 3350
Connection ~ 7900 3350
Wire Wire Line
	8400 3350 8400 3400
Wire Wire Line
	8400 3400 9050 3400
Connection ~ 9050 3400
$Comp
L THERMISTOR TH2
U 1 1 56115896
P 6500 3800
F 0 "TH2" V 6600 3850 50  0000 C CNN
F 1 "THERMISTOR" V 6400 3800 50  0000 C CNN
F 2 "" H 6500 3800 60  0000 C CNN
F 3 "" H 6500 3800 60  0000 C CNN
	1    6500 3800
	1    0    0    -1  
$EndComp
$Comp
L R R31
U 1 1 561158DE
P 7150 3950
F 0 "R31" V 7230 3950 40  0000 C CNN
F 1 "237k" V 7157 3951 40  0000 C CNN
F 2 "" V 7080 3950 30  0000 C CNN
F 3 "" H 7150 3950 30  0000 C CNN
	1    7150 3950
	0    1    1    0   
$EndComp
$Comp
L R R32
U 1 1 56115929
P 7450 3650
F 0 "R32" V 7530 3650 40  0000 C CNN
F 1 "14.3k" V 7457 3651 40  0000 C CNN
F 2 "" V 7380 3650 30  0000 C CNN
F 3 "" H 7450 3650 30  0000 C CNN
	1    7450 3650
	1    0    0    -1  
$EndComp
$Comp
L R R33
U 1 1 561159A8
P 7450 4250
F 0 "R33" V 7530 4250 40  0000 C CNN
F 1 "330k" V 7457 4251 40  0000 C CNN
F 2 "" V 7380 4250 30  0000 C CNN
F 3 "" H 7450 4250 30  0000 C CNN
	1    7450 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 3300 6800 3300
Wire Wire Line
	6800 3300 6800 3950
Wire Wire Line
	6800 3950 6900 3950
Wire Wire Line
	7400 3950 7450 3950
Wire Wire Line
	7450 3900 7450 4000
Connection ~ 7450 3950
Wire Wire Line
	7450 3400 7450 3350
Connection ~ 7450 3350
Wire Wire Line
	6450 3200 6500 3200
Wire Wire Line
	6500 3200 6500 3550
Text HLabel 6200 4850 0    60   Input ~ 0
GND
Wire Wire Line
	6200 4850 9050 4850
Wire Wire Line
	9050 4850 9050 4150
Wire Wire Line
	7900 3950 7900 4850
Wire Wire Line
	7900 4850 7850 4850
Connection ~ 7850 4850
Wire Wire Line
	7450 4500 7450 4850
Connection ~ 7450 4850
Wire Wire Line
	6500 4050 6500 4850
Connection ~ 6500 4850
Connection ~ 9050 3250
Text HLabel 9650 3250 2    60   Input ~ 0
Vout
Wire Wire Line
	3200 2800 5250 2800
Wire Wire Line
	3450 2950 3450 2800
Connection ~ 3450 2800
Wire Wire Line
	3600 2900 3550 2900
Wire Wire Line
	3550 2900 3550 2800
Connection ~ 3550 2800
Wire Wire Line
	4100 2900 5250 2900
Wire Wire Line
	4150 2900 4150 2950
Connection ~ 4150 2900
$Comp
L R R29
U 1 1 561165A5
P 4550 3000
F 0 "R29" V 4630 3000 40  0000 C CNN
F 1 "50k" V 4557 3001 40  0000 C CNN
F 2 "" V 4480 3000 30  0000 C CNN
F 3 "" H 4550 3000 30  0000 C CNN
	1    4550 3000
	0    1    1    0   
$EndComp
$Comp
L R R30
U 1 1 561165FC
P 4850 3300
F 0 "R30" V 4930 3300 40  0000 C CNN
F 1 "10k" V 4857 3301 40  0000 C CNN
F 2 "" V 4780 3300 30  0000 C CNN
F 3 "" H 4850 3300 30  0000 C CNN
	1    4850 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 3000 4250 3000
Wire Wire Line
	4250 3000 4250 2800
Connection ~ 4250 2800
Wire Wire Line
	4800 3000 5250 3000
Wire Wire Line
	4850 2400 4850 3050
Connection ~ 4850 3000
Wire Wire Line
	4850 2400 5000 2400
Text HLabel 5000 2400 2    60   Input ~ 0
SHDN
Wire Wire Line
	5250 3100 4950 3100
Wire Wire Line
	4950 3100 4950 2500
Wire Wire Line
	4950 2500 5100 2500
Wire Wire Line
	5250 3200 5050 3200
Wire Wire Line
	5050 3200 5050 2600
Wire Wire Line
	5050 2600 5100 2600
Text HLabel 5100 2500 2    60   Input ~ 0
CHRG
Text HLabel 5100 2600 2    60   Input ~ 0
FAULT
$Comp
L C C14
U 1 1 56116AAD
P 5200 3550
F 0 "C14" H 5200 3650 40  0000 L CNN
F 1 ".68uf" H 5206 3465 40  0000 L CNN
F 2 "" H 5238 3400 30  0000 C CNN
F 3 "" H 5200 3550 60  0000 C CNN
	1    5200 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3350 5200 3300
Wire Wire Line
	5200 3300 5250 3300
$Comp
L DIODESCH D6
U 1 1 56116E89
P 7200 2900
F 0 "D6" H 7200 3000 40  0000 C CNN
F 1 "CMDSH2-4L" H 7200 2800 40  0000 C CNN
F 2 "" H 7200 2900 60  0000 C CNN
F 3 "" H 7200 2900 60  0000 C CNN
	1    7200 2900
	-1   0    0    1   
$EndComp
Wire Wire Line
	7400 2900 7900 2900
Text HLabel 3300 4100 0    60   Input ~ 0
GND
Wire Wire Line
	3300 4100 5200 4100
Wire Wire Line
	5200 4100 5200 3750
Wire Wire Line
	4850 3550 4850 4100
Connection ~ 4850 4100
Wire Wire Line
	4150 3450 4150 4100
Connection ~ 4150 4100
Wire Wire Line
	3450 3350 3450 4100
Connection ~ 3450 4100
$EndSCHEMATC
