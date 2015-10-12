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
LIBS:powerRev2-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
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
L LT4415 U?
U 1 1 5618869F
P 6000 3550
F 0 "U?" H 6050 3100 60  0000 C CNN
F 1 "LT4415" H 6050 3200 60  0000 C CNN
F 2 "" H 6050 2600 60  0000 C CNN
F 3 "" H 6050 2600 60  0000 C CNN
	1    6000 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 3400 5350 3400
Wire Wire Line
	5150 2500 5150 3400
Connection ~ 5150 3300
Wire Wire Line
	5200 3900 5200 4000
Wire Wire Line
	5200 4000 5350 4000
Connection ~ 5200 3900
Wire Wire Line
	6750 3900 6950 3900
Wire Wire Line
	6950 3900 6950 4000
Connection ~ 6950 4000
Wire Wire Line
	6750 3300 7750 3300
Wire Wire Line
	6950 3300 6950 3400
Wire Wire Line
	6950 3400 6750 3400
Connection ~ 6950 3300
Text Notes 2650 4900 0    60   ~ 0
Secondary is enabled when the following occurs:\nR1 is closest to the primary\nVPri < 0.8V * (1+ (R1 + R2) / R3)\n
Text Notes 2650 5400 0    60   ~ 0
Primary is disabled when:\nVin1 < (0.8V - Venhyst (0.055) ) * (1+ R1 / (R2 + R3))\n
Wire Wire Line
	5150 3300 5350 3300
$Comp
L R R?
U 1 1 56188D34
P 3500 2900
F 0 "R?" V 3580 2900 40  0000 C CNN
F 1 "237K" V 3507 2901 40  0000 C CNN
F 2 "" V 3430 2900 30  0000 C CNN
F 3 "" H 3500 2900 30  0000 C CNN
	1    3500 2900
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 56188D65
P 3500 3500
F 0 "R?" V 3580 3500 40  0000 C CNN
F 1 "30.1K" V 3507 3501 40  0000 C CNN
F 2 "" V 3430 3500 30  0000 C CNN
F 3 "" H 3500 3500 30  0000 C CNN
	1    3500 3500
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 56188D8F
P 3500 4100
F 0 "R?" V 3580 4100 40  0000 C CNN
F 1 "95.3K" V 3507 4101 40  0000 C CNN
F 2 "" V 3430 4100 30  0000 C CNN
F 3 "" H 3500 4100 30  0000 C CNN
	1    3500 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 2500 5150 2500
Wire Wire Line
	3500 2500 3500 2650
Wire Wire Line
	3500 3150 3500 3250
Wire Wire Line
	5350 3500 5050 3500
Wire Wire Line
	5050 3500 5050 3200
Wire Wire Line
	5050 3200 3400 3200
Connection ~ 3500 3200
Wire Wire Line
	3400 3800 5350 3800
Wire Wire Line
	3500 3750 3500 3850
Connection ~ 3500 3800
$Comp
L R R?
U 1 1 56188FAE
P 4350 3700
F 0 "R?" V 4430 3700 40  0000 C CNN
F 1 "165" V 4357 3701 40  0000 C CNN
F 2 "" V 4280 3700 30  0000 C CNN
F 3 "" H 4350 3700 30  0000 C CNN
	1    4350 3700
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 56188FE0
P 4000 3600
F 0 "R?" V 4080 3600 40  0000 C CNN
F 1 "165" V 4007 3601 40  0000 C CNN
F 2 "" V 3930 3600 30  0000 C CNN
F 3 "" H 4000 3600 30  0000 C CNN
	1    4000 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	5350 3900 5100 3900
Wire Wire Line
	3750 3600 3750 4400
Wire Wire Line
	3500 4400 3500 4350
Wire Wire Line
	4100 4400 4100 3700
Wire Wire Line
	4250 3600 5350 3600
Wire Wire Line
	4600 3700 5350 3700
Wire Wire Line
	3500 4400 4100 4400
Connection ~ 3750 4400
Text HLabel 3500 2500 0    60   Input ~ 0
VIN1
Text HLabel 3400 3200 0    60   Input ~ 0
EN1
Text HLabel 3400 3800 0    60   Input ~ 0
EN2
Text HLabel 4350 3500 0    60   Input ~ 0
Curren1
Text HLabel 4900 3500 0    60   Input ~ 0
Current2
Wire Wire Line
	4350 3500 4350 3600
Connection ~ 4350 3600
Wire Wire Line
	4900 3500 4900 3600
Connection ~ 4900 3600
Text HLabel 5100 3900 0    60   Input ~ 0
VIN2
Text HLabel 7750 3300 2    60   Input ~ 0
OUT1
Text HLabel 6950 4000 3    60   Input ~ 0
OUT2
$Comp
L R R?
U 1 1 56189415
P 7350 3500
F 0 "R?" V 7430 3500 40  0000 C CNN
F 1 "470K" V 7357 3501 40  0000 C CNN
F 2 "" V 7280 3500 30  0000 C CNN
F 3 "" H 7350 3500 30  0000 C CNN
	1    7350 3500
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 5618945D
P 7750 3600
F 0 "R?" V 7830 3600 40  0000 C CNN
F 1 "470K" V 7757 3601 40  0000 C CNN
F 2 "" V 7680 3600 30  0000 C CNN
F 3 "" H 7750 3600 30  0000 C CNN
	1    7750 3600
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 56189482
P 8150 3700
F 0 "R?" V 8230 3700 40  0000 C CNN
F 1 "470K" V 8157 3701 40  0000 C CNN
F 2 "" V 8080 3700 30  0000 C CNN
F 3 "" H 8150 3700 30  0000 C CNN
	1    8150 3700
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 561894A8
P 8600 3800
F 0 "R?" V 8680 3800 40  0000 C CNN
F 1 "470K" V 8607 3801 40  0000 C CNN
F 2 "" V 8530 3800 30  0000 C CNN
F 3 "" H 8600 3800 30  0000 C CNN
	1    8600 3800
	0    1    1    0   
$EndComp
Text HLabel 8300 3950 3    60   Input ~ 0
STAT2
Wire Wire Line
	6950 4000 6750 4000
Wire Wire Line
	6750 3500 7100 3500
Wire Wire Line
	6750 3600 7500 3600
Wire Wire Line
	6750 3700 7900 3700
Wire Wire Line
	6750 3800 8350 3800
Text HLabel 7850 3950 3    60   Input ~ 0
WARN2
Text HLabel 7450 3950 3    60   Input ~ 0
WARN1
Text HLabel 7050 3950 3    60   Input ~ 0
STAT1
Wire Wire Line
	7050 3950 7050 3500
Connection ~ 7050 3500
Wire Wire Line
	7450 3950 7450 3600
Connection ~ 7450 3600
Wire Wire Line
	7850 3700 7850 3950
Connection ~ 7850 3700
Wire Wire Line
	8300 3950 8300 3800
Connection ~ 8300 3800
Text HLabel 6050 2900 2    60   Input ~ 0
GND
Text HLabel 4100 4400 2    60   Input ~ 0
GND
Text HLabel 9250 3800 2    60   Input ~ 0
VPull
Wire Wire Line
	9250 3800 8850 3800
Wire Wire Line
	7600 3500 9050 3500
Wire Wire Line
	9050 3500 9050 3800
Connection ~ 9050 3800
Wire Wire Line
	8000 3600 9050 3600
Connection ~ 9050 3600
Wire Wire Line
	8400 3700 9050 3700
Connection ~ 9050 3700
Text Notes 2800 4200 2    60   ~ 0
For the current limiting/ current sensing resistors\nRCLIM = 1000 * 0.5V / ILIM\n\nAlso, this \nIout = 1000 * VCLIM / RCLIM
Text Notes 2600 3250 2    60   ~ 0
For 3 amps limit, use 165 ohm resistors. \n3.0303 Amps limit\n\n
Text Notes 4600 6050 2    60   ~ 0
R1: 237K\nR2: 30.1K\nR3: 95.3K\n\nThis will cause secondary to turn on when primary reaches 3.04V.\nWhen primary gets to 2.15, it will turn off completly. \n\nNote that if these are driven, both must be driven.\n
$EndSCHEMATC
