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
LIBS:conn_11x2
LIBS:tps63020
LIBS:ncp508
LIBS:smtJmpOpen
LIBS:SparkFun
LIBS:attiny24a-m
LIBS:power-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L CONN_11X2 P2
U 1 1 55490368
P 1750 1400
F 0 "P2" H 1750 1950 60  0000 C CNN
F 1 "CONN_11X2" V 1750 1300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x11" H 1750 1400 60  0001 C CNN
F 3 "" H 1750 1400 60  0000 C CNN
	1    1750 1400
	1    0    0    -1  
$EndComp
Text Label 950  950  0    60   ~ 0
Vin
Text Label 950  1050 0    60   ~ 0
VOut2
Text Label 950  1150 0    60   ~ 0
3v3Out
Text Label 950  1350 0    60   ~ 0
SDA
Text Label 950  1450 0    60   ~ 0
CLK
Text Label 950  1550 0    60   ~ 0
SDA
Text Label 950  1650 0    60   ~ 0
Gnd
Text Label 950  1250 0    60   ~ 0
Gnd
Text Label 950  1750 0    60   ~ 0
3v3Out
Text Label 950  1850 0    60   ~ 0
VOut2
Text Label 950  1950 0    60   ~ 0
Vin
Text Label 2300 950  0    60   ~ 0
Vin
Text Label 2300 1050 0    60   ~ 0
VOut2
Text Label 2300 1150 0    60   ~ 0
3v3Out
Text Label 2300 1350 0    60   ~ 0
SDA
Text Label 2300 1450 0    60   ~ 0
CLK
Text Label 2300 1550 0    60   ~ 0
SDA
Text Label 2300 1650 0    60   ~ 0
Gnd
Text Label 2300 1250 0    60   ~ 0
Gnd
Text Label 2300 1750 0    60   ~ 0
3v3Out
Text Label 2300 1850 0    60   ~ 0
VOut2
Text Label 2300 1950 0    60   ~ 0
Vin
$Comp
L TPS63020 U1
U 1 1 55491A9D
P 3900 4250
F 0 "U1" H 3950 4650 60  0000 C CNN
F 1 "TPS63020" H 3950 4500 60  0000 C CNN
F 2 "TPS63020:TPS63020" H 3900 4250 60  0001 C CNN
F 3 "" H 3900 4250 60  0000 C CNN
	1    3900 4250
	1    0    0    -1  
$EndComp
$Comp
L INDUCTOR_SMALL L1
U 1 1 55491AF6
P 3850 3100
F 0 "L1" H 3850 3200 50  0000 C CNN
F 1 "1uh" H 3850 3050 50  0000 C CNN
F 2 "Inductors:SELF-WE-TPC_M" H 3850 3100 60  0001 C CNN
F 3 "" H 3850 3100 60  0000 C CNN
	1    3850 3100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 55491B4C
P 3700 5600
F 0 "#PWR01" H 3700 5600 30  0001 C CNN
F 1 "GND" H 3700 5530 30  0001 C CNN
F 2 "" H 3700 5600 60  0000 C CNN
F 3 "" H 3700 5600 60  0000 C CNN
	1    3700 5600
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 55491B63
P 5200 4150
F 0 "R3" V 5280 4150 40  0000 C CNN
F 1 "768J" V 5207 4151 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 5130 4150 30  0001 C CNN
F 3 "" H 5200 4150 30  0000 C CNN
	1    5200 4150
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 55491B9A
P 5200 4850
F 0 "R4" V 5280 4850 40  0000 C CNN
F 1 "137J" V 5207 4851 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 5130 4850 30  0001 C CNN
F 3 "" H 5200 4850 30  0000 C CNN
	1    5200 4850
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 55491BE2
P 1800 4400
F 0 "C1" H 1800 4500 40  0000 L CNN
F 1 "10u" H 1806 4315 40  0000 L CNN
F 2 "Capacitors_SMD:C_0201" H 1838 4250 30  0001 C CNN
F 3 "" H 1800 4400 60  0000 C CNN
	1    1800 4400
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 55491C2D
P 2000 4400
F 0 "C2" H 2000 4500 40  0000 L CNN
F 1 "10u" H 2006 4315 40  0000 L CNN
F 2 "Capacitors_SMD:c_elec_5x5.8" H 2038 4250 30  0001 C CNN
F 3 "" H 2000 4400 60  0000 C CNN
	1    2000 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 950  900  950 
Wire Wire Line
	1350 1050 900  1050
Wire Wire Line
	800  1150 1350 1150
Wire Wire Line
	600  1250 1350 1250
Wire Wire Line
	1350 1350 900  1350
Wire Wire Line
	1350 1450 900  1450
Wire Wire Line
	1350 1550 900  1550
Wire Wire Line
	600  1650 1350 1650
Wire Wire Line
	800  1750 1350 1750
Wire Wire Line
	1350 1850 900  1850
Wire Wire Line
	1350 1950 900  1950
Wire Wire Line
	2150 950  2600 950 
Wire Wire Line
	2150 1050 2600 1050
Wire Wire Line
	2150 1150 2750 1150
Wire Wire Line
	2150 1250 2800 1250
Wire Wire Line
	2150 1350 2600 1350
Wire Wire Line
	2150 1450 2600 1450
Wire Wire Line
	2150 1550 2600 1550
Wire Wire Line
	2150 1650 2850 1650
Wire Wire Line
	2150 1750 2700 1750
Wire Wire Line
	2150 1850 2600 1850
Wire Wire Line
	2150 1950 2600 1950
Wire Wire Line
	4750 3800 4750 3900
Wire Wire Line
	4750 3850 5400 3850
Wire Wire Line
	5200 3700 5200 3900
Connection ~ 4750 3850
Wire Wire Line
	5200 4400 5200 4600
Wire Wire Line
	4750 4300 5000 4300
Wire Wire Line
	5000 4300 5000 4500
Wire Wire Line
	5000 4500 5200 4500
Connection ~ 5200 4500
Wire Wire Line
	5200 5500 5200 5100
Wire Wire Line
	2000 5500 6200 5500
Wire Wire Line
	3800 5500 3800 5450
Wire Wire Line
	3700 5450 3700 5600
Connection ~ 3800 5500
Connection ~ 3700 5500
Wire Wire Line
	1200 4150 3250 4150
Wire Wire Line
	2000 4150 2000 4200
Wire Wire Line
	3250 4050 3200 4050
Wire Wire Line
	3200 4050 3200 4150
Connection ~ 3200 4150
Wire Wire Line
	1800 4150 1800 4200
Connection ~ 2000 4150
Wire Wire Line
	1800 4600 1800 4650
Wire Wire Line
	1800 4650 2000 4650
Wire Wire Line
	2000 4600 2000 5500
Connection ~ 2000 4650
Wire Wire Line
	3550 3500 3550 3100
Wire Wire Line
	3550 3100 3600 3100
Wire Wire Line
	3650 3500 3650 3400
Wire Wire Line
	3650 3400 3550 3400
Connection ~ 3550 3400
Wire Wire Line
	4000 3500 4000 3400
Wire Wire Line
	4000 3400 4150 3400
Wire Wire Line
	4150 3400 4150 3100
Wire Wire Line
	4150 3100 4100 3100
Wire Wire Line
	4100 3500 4100 3400
Connection ~ 4100 3400
$Comp
L NCP508 U2
U 1 1 55492823
P 5300 1350
F 0 "U2" H 5300 1600 40  0000 C CNN
F 1 "NCP508" H 5300 1550 40  0000 C CNN
F 2 "SMD:SOT-23-5" H 5300 1350 60  0001 C CNN
F 3 "" H 5300 1350 60  0000 C CNN
	1    5300 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 1250 4150 1250
$Comp
L GND #PWR02
U 1 1 554929C2
P 4750 1500
F 0 "#PWR02" H 4750 1500 30  0001 C CNN
F 1 "GND" H 4750 1430 30  0001 C CNN
F 2 "" H 4750 1500 60  0000 C CNN
F 3 "" H 4750 1500 60  0000 C CNN
	1    4750 1500
	1    0    0    -1  
$EndComp
Text Label 4550 1250 0    60   ~ 0
Vin
Wire Wire Line
	6550 1250 5750 1250
Wire Wire Line
	6550 900  6550 1250
Wire Wire Line
	6550 1150 6750 1150
Wire Wire Line
	4750 1500 4750 1450
Wire Wire Line
	4750 1450 4850 1450
Wire Wire Line
	4800 1450 4800 1700
Wire Wire Line
	4800 1600 5750 1600
Connection ~ 4800 1450
$Comp
L C C5
U 1 1 55492B2E
P 6050 1500
F 0 "C5" H 6050 1600 40  0000 L CNN
F 1 "1u" H 6056 1415 40  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 6088 1350 30  0001 C CNN
F 3 "" H 6050 1500 60  0000 C CNN
	1    6050 1500
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 55492B5F
P 4400 1500
F 0 "C4" H 4400 1600 40  0000 L CNN
F 1 "1u" H 4406 1415 40  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 4438 1350 30  0001 C CNN
F 3 "" H 4400 1500 60  0000 C CNN
	1    4400 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 1300 4400 1250
Connection ~ 4400 1250
Wire Wire Line
	4800 1700 4400 1700
Connection ~ 4800 1600
Wire Wire Line
	5750 1700 6050 1700
Wire Wire Line
	6050 1300 6050 1250
Connection ~ 6050 1250
Wire Wire Line
	5900 1700 6550 1700
Wire Wire Line
	6550 1700 6550 2350
Wire Wire Line
	6550 2350 6750 2350
Connection ~ 5900 1700
Wire Wire Line
	8850 1150 9700 1150
Wire Wire Line
	8850 1250 9700 1250
Wire Wire Line
	8850 1350 9850 1350
Wire Wire Line
	8850 1450 9700 1450
Wire Wire Line
	8850 1750 10100 1750
Wire Wire Line
	8850 1850 9700 1850
Wire Wire Line
	8850 2050 9700 2050
Wire Wire Line
	8850 2150 9700 2150
Wire Wire Line
	8850 2250 9700 2250
Wire Wire Line
	8850 2350 10200 2350
Wire Wire Line
	3250 4700 2850 4700
Wire Wire Line
	3250 4400 2850 4400
Text Label 2850 4400 0    60   ~ 0
PSave
Text Label 2850 4700 0    60   ~ 0
Enable
$Comp
L +3.3V #PWR03
U 1 1 554933F2
P 2750 1150
F 0 "#PWR03" H 2750 1110 30  0001 C CNN
F 1 "+3.3V" H 2750 1260 30  0000 C CNN
F 2 "" H 2750 1150 60  0000 C CNN
F 3 "" H 2750 1150 60  0000 C CNN
	1    2750 1150
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR04
U 1 1 55493427
P 2700 1750
F 0 "#PWR04" H 2700 1710 30  0001 C CNN
F 1 "+3.3V" H 2700 1860 30  0000 C CNN
F 2 "" H 2700 1750 60  0000 C CNN
F 3 "" H 2700 1750 60  0000 C CNN
	1    2700 1750
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR05
U 1 1 55493446
P 800 1150
F 0 "#PWR05" H 800 1110 30  0001 C CNN
F 1 "+3.3V" H 800 1260 30  0000 C CNN
F 2 "" H 800 1150 60  0000 C CNN
F 3 "" H 800 1150 60  0000 C CNN
	1    800  1150
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR06
U 1 1 55493465
P 800 1750
F 0 "#PWR06" H 800 1710 30  0001 C CNN
F 1 "+3.3V" H 800 1860 30  0000 C CNN
F 2 "" H 800 1750 60  0000 C CNN
F 3 "" H 800 1750 60  0000 C CNN
	1    800  1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 55493484
P 600 1700
F 0 "#PWR07" H 600 1700 30  0001 C CNN
F 1 "GND" H 600 1630 30  0001 C CNN
F 2 "" H 600 1700 60  0000 C CNN
F 3 "" H 600 1700 60  0000 C CNN
	1    600  1700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 554934A3
P 600 1300
F 0 "#PWR08" H 600 1300 30  0001 C CNN
F 1 "GND" H 600 1230 30  0001 C CNN
F 2 "" H 600 1300 60  0000 C CNN
F 3 "" H 600 1300 60  0000 C CNN
	1    600  1300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 554934C2
P 2800 1300
F 0 "#PWR09" H 2800 1300 30  0001 C CNN
F 1 "GND" H 2800 1230 30  0001 C CNN
F 2 "" H 2800 1300 60  0000 C CNN
F 3 "" H 2800 1300 60  0000 C CNN
	1    2800 1300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 554934E1
P 2850 1700
F 0 "#PWR010" H 2850 1700 30  0001 C CNN
F 1 "GND" H 2850 1630 30  0001 C CNN
F 2 "" H 2850 1700 60  0000 C CNN
F 3 "" H 2850 1700 60  0000 C CNN
	1    2850 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	600  1300 600  1250
Wire Wire Line
	600  1650 600  1700
Wire Wire Line
	2850 1650 2850 1700
Wire Wire Line
	2800 1250 2800 1300
$Comp
L R R5
U 1 1 55493909
P 5650 3850
F 0 "R5" V 5730 3850 40  0000 C CNN
F 1 "R" V 5657 3851 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 5580 3850 30  0001 C CNN
F 3 "" H 5650 3850 30  0000 C CNN
	1    5650 3850
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 554939CC
P 1200 4450
F 0 "R1" V 1280 4450 40  0000 C CNN
F 1 "R" V 1207 4451 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1130 4450 30  0001 C CNN
F 3 "" H 1200 4450 30  0000 C CNN
	1    1200 4450
	-1   0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 55493A3A
P 1200 5150
F 0 "R2" V 1280 5150 40  0000 C CNN
F 1 "R" V 1207 5151 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1130 5150 30  0001 C CNN
F 3 "" H 1200 5150 30  0000 C CNN
	1    1200 5150
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 55493A6B
P 1200 5700
F 0 "#PWR011" H 1200 5700 30  0001 C CNN
F 1 "GND" H 1200 5630 30  0001 C CNN
F 2 "" H 1200 5700 60  0000 C CNN
F 3 "" H 1200 5700 60  0000 C CNN
	1    1200 5700
	-1   0    0    -1  
$EndComp
$Comp
L +3.3V #PWR012
U 1 1 55493A8D
P 6650 3750
F 0 "#PWR012" H 6650 3710 30  0001 C CNN
F 1 "+3.3V" H 6650 3860 30  0000 C CNN
F 2 "" H 6650 3750 60  0000 C CNN
F 3 "" H 6650 3750 60  0000 C CNN
	1    6650 3750
	1    0    0    -1  
$EndComp
Connection ~ 5200 3850
Wire Wire Line
	5900 3850 6650 3850
Wire Wire Line
	1200 4700 1200 4900
Wire Wire Line
	1200 5400 1200 5700
Wire Wire Line
	1200 4800 450  4800
Connection ~ 1200 4800
Wire Wire Line
	6650 3850 6650 3750
Wire Wire Line
	5200 3700 6000 3700
Text Label 5300 3700 0    60   ~ 0
ISense
Text Label 1050 4800 2    60   ~ 0
VSense
Text Label 8900 1550 0    60   ~ 0
CLK
Text Label 8900 1750 0    60   ~ 0
SDA
Wire Wire Line
	1200 4150 1200 4200
Connection ~ 1800 4150
Text Label 1350 4150 0    60   ~ 0
Vin
Text Label 8900 1150 0    60   ~ 0
VSense
Text Label 8900 1250 0    60   ~ 0
ISense
$Comp
L +3.3V #PWR013
U 1 1 55494ACE
P 9850 1300
F 0 "#PWR013" H 9850 1260 30  0001 C CNN
F 1 "+3.3V" H 9850 1410 30  0000 C CNN
F 2 "" H 9850 1300 60  0000 C CNN
F 3 "" H 9850 1300 60  0000 C CNN
	1    9850 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 1350 9850 1300
$Comp
L CONN_3X2 P3
U 1 1 55494EEA
P 7800 750
F 0 "P3" H 7800 1000 50  0000 C CNN
F 1 "AVRProg" V 7800 800 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03" H 7800 750 60  0001 C CNN
F 3 "" H 7800 750 60  0000 C CNN
	1    7800 750 
	-1   0    0    1   
$EndComp
Wire Wire Line
	7400 700  6350 700 
Wire Wire Line
	6350 700  6350 1700
Connection ~ 6350 1700
Wire Wire Line
	7400 900  6550 900 
Connection ~ 6550 1150
Wire Wire Line
	7400 800  7300 800 
Wire Wire Line
	7300 800  7300 550 
Wire Wire Line
	7300 550  10100 550 
Wire Wire Line
	10100 550  10100 1750
Wire Wire Line
	8200 800  10000 800 
Wire Wire Line
	10000 800  10000 1550
Wire Wire Line
	10000 1550 8850 1550
Wire Wire Line
	8200 900  9950 900 
Wire Wire Line
	9950 900  9950 1650
Wire Wire Line
	9950 1650 8850 1650
Wire Wire Line
	8200 700  10200 700 
Wire Wire Line
	10200 700  10200 2350
Text Label 8950 2050 0    60   ~ 0
PSave
Text Label 8950 2150 0    60   ~ 0
Enable
$Comp
L TEST-POINT2 TP1
U 1 1 55495A00
P 3050 4800
F 0 "TP1" H 3100 4900 50  0000 C CNN
F 1 "TEST-POINT2" H 3100 4700 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Big" H 3100 4600 50  0001 C CNN
F 3 "" H 3050 4800 60  0000 C CNN
	1    3050 4800
	0    1    1    0   
$EndComp
Wire Wire Line
	3050 4800 3050 4700
Connection ~ 3050 4700
$Comp
L C C6
U 1 1 55495C91
P 6200 4100
F 0 "C6" H 6200 4200 40  0000 L CNN
F 1 "120u" H 6206 4015 40  0000 L CNN
F 2 "Capacitors_SMD:c_elec_6.3x7.7" H 6238 3950 30  0001 C CNN
F 3 "" H 6200 4100 60  0000 C CNN
	1    6200 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 3900 6200 3850
Connection ~ 6200 3850
Wire Wire Line
	6200 5500 6200 4300
Connection ~ 5200 5500
$Comp
L C C3
U 1 1 5549617A
P 2250 4700
F 0 "C3" H 2250 4800 40  0000 L CNN
F 1 "100n" H 2256 4615 40  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 2288 4550 30  0001 C CNN
F 3 "" H 2250 4700 60  0000 C CNN
	1    2250 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 4900 2000 4900
Connection ~ 2000 4900
Wire Wire Line
	3250 4500 2250 4500
$Comp
L LED D2
U 1 1 55496818
P 9900 1850
F 0 "D2" H 9900 1950 50  0000 C CNN
F 1 "STAT1G" H 9900 1750 50  0000 C CNN
F 2 "LEDs:LED-0805" H 9900 1850 60  0001 C CNN
F 3 "" H 9900 1850 60  0000 C CNN
	1    9900 1850
	1    0    0    -1  
$EndComp
$Comp
L LED D3
U 1 1 554968A8
P 9900 2250
F 0 "D3" H 9900 2350 50  0000 C CNN
F 1 "STAT2R" H 9900 2150 50  0000 C CNN
F 2 "LEDs:LED-0805" H 9900 2250 60  0001 C CNN
F 3 "" H 9900 2250 60  0000 C CNN
	1    9900 2250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 554968EB
P 10850 2400
F 0 "#PWR014" H 10850 2400 30  0001 C CNN
F 1 "GND" H 10850 2330 30  0001 C CNN
F 2 "" H 10850 2400 60  0000 C CNN
F 3 "" H 10850 2400 60  0000 C CNN
	1    10850 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 1850 10350 1850
Wire Wire Line
	10100 2250 10350 2250
NoConn ~ 3250 4800
$Comp
L CONN_2 P1
U 1 1 554972F7
P 600 2800
F 0 "P1" V 550 2800 40  0000 C CNN
F 1 "VIN" V 650 2800 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 600 2800 60  0001 C CNN
F 3 "" H 600 2800 60  0000 C CNN
	1    600  2800
	-1   0    0    1   
$EndComp
$Comp
L DIODE D1
U 1 1 5549747C
P 1850 2800
F 0 "D1" H 1850 2900 40  0000 C CNN
F 1 "DIODE" H 1850 2700 40  0000 C CNN
F 2 "Diodes_SMD:SOD-323" H 1850 2800 60  0001 C CNN
F 3 "" H 1850 2800 60  0000 C CNN
	1    1850 2800
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR015
U 1 1 554974F9
P 1850 3150
F 0 "#PWR015" H 1850 3150 30  0001 C CNN
F 1 "GND" H 1850 3080 30  0001 C CNN
F 2 "" H 1850 3150 60  0000 C CNN
F 3 "" H 1850 3150 60  0000 C CNN
	1    1850 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2700 1600 2500
Wire Wire Line
	1600 2500 2300 2500
Wire Wire Line
	1850 2500 1850 2600
Wire Wire Line
	950  2900 1650 2900
Wire Wire Line
	1650 2900 1650 3050
Wire Wire Line
	1650 3050 1850 3050
Wire Wire Line
	1850 3000 1850 3150
Connection ~ 1850 3050
Connection ~ 1850 2500
Text Label 1900 2500 0    60   ~ 0
Vin
$Comp
L FUSE F1
U 1 1 5549793A
P 1300 2700
F 0 "F1" H 1400 2750 40  0000 C CNN
F 1 "FUSE" H 1200 2650 40  0000 C CNN
F 2 "SMD_Packages:SMD-2112_Pol" H 1300 2700 60  0001 C CNN
F 3 "" H 1300 2700 60  0000 C CNN
	1    1300 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  2700 1050 2700
Wire Wire Line
	1550 2700 1600 2700
NoConn ~ 9700 1450
NoConn ~ 2600 1850
NoConn ~ 2600 1050
NoConn ~ 900  1850
NoConn ~ 900  1050
Wire Wire Line
	5750 1600 5750 1700
Wire Wire Line
	5750 1450 5850 1450
Wire Wire Line
	5850 1450 5850 1000
Wire Wire Line
	5850 1000 4750 1000
Wire Wire Line
	4750 1000 4750 1250
Connection ~ 4750 1250
$Comp
L R R6
U 1 1 55499110
P 10600 1850
F 0 "R6" V 10680 1850 40  0000 C CNN
F 1 "R" V 10607 1851 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 10530 1850 30  0001 C CNN
F 3 "" H 10600 1850 30  0000 C CNN
	1    10600 1850
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 554991E1
P 10600 2250
F 0 "R7" V 10680 2250 40  0000 C CNN
F 1 "75" V 10607 2251 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 10530 2250 30  0001 C CNN
F 3 "" H 10600 2250 30  0000 C CNN
	1    10600 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	10850 1850 10850 2400
$Comp
L ATTINY24A-M-FIXED IC1
U 1 1 5549A687
P 7800 1750
F 0 "IC1" H 6950 2500 40  0000 C CNN
F 1 "ATTINY24A-M-FIXED" H 8500 1000 40  0000 C CNN
F 2 "Housings_DFN_QFN:QFN-20-1EP_4x4mm_Pitch0.5mm" H 7800 1550 35  0000 C CIN
F 3 "" H 7800 1750 60  0000 C CNN
	1    7800 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 2250 6650 2250
Wire Wire Line
	6650 2250 6650 2350
Connection ~ 6650 2350
$EndSCHEMATC
