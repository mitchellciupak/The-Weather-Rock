EESchema Schematic File Version 4
EELAYER 30 0
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
L Connector:Conn_01x08_Male J?
U 1 1 5FE50245
P 4350 4400
F 0 "J?" H 4322 4282 50  0000 R CNN
F 1 "E-Paper Display" H 4600 4800 50  0000 R CNN
F 2 "" H 4350 4400 50  0001 C CNN
F 3 "~" H 4350 4400 50  0001 C CNN
	1    4350 4400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J?
U 1 1 5FE53085
P 4250 3350
F 0 "J?" H 4222 3232 50  0000 R CNN
F 1 "IMU_BNO055" H 4500 3550 50  0000 R CNN
F 2 "" H 4250 3350 50  0001 C CNN
F 3 "~" H 4250 3350 50  0001 C CNN
	1    4250 3350
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J?
U 1 1 5FE55999
P 7100 4200
F 0 "J?" H 7208 4481 50  0000 C CNN
F 1 "MoistureSensor" H 7350 3900 50  0000 C CNN
F 2 "" H 7100 4200 50  0001 C CNN
F 3 "~" H 7100 4200 50  0001 C CNN
	1    7100 4200
	-1   0    0    1   
$EndComp
Text GLabel 8100 3700 0    50   Input ~ 0
SDA
Text GLabel 8100 3800 0    50   Input ~ 0
SCL
Text GLabel 6300 4400 2    50   Input ~ 0
SDA
Text GLabel 6300 4500 2    50   Input ~ 0
SCL
Text GLabel 4550 4800 2    50   Input ~ 0
3V3
Text GLabel 4550 4700 2    50   Input ~ 0
GND
$Comp
L Battery_Management:BQ27441-G1 U?
U 1 1 5FE4EEB2
P 8700 3900
F 0 "U?" H 8700 4567 50  0000 C CNN
F 1 "BQ27441-G1" H 8700 4476 50  0000 C CNN
F 2 "Package_SON:Texas_S-PDSO-N12" H 8950 3350 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/bq27441-g1.pdf" H 8900 4100 50  0001 C CNN
	1    8700 3900
	1    0    0    -1  
$EndComp
$Comp
L MCU_Module:Arduino_UNO_R3 A?
U 1 1 5FE4DDBF
P 5800 4000
F 0 "A?" H 5800 5181 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 5800 5090 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 5800 4000 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 5800 4000 50  0001 C CNN
	1    5800 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 4100 4550 4100
Wire Wire Line
	4550 4200 5300 4200
Wire Wire Line
	4550 4300 5300 4300
Wire Wire Line
	4550 4400 5300 4400
Text GLabel 4550 4500 2    50   Input ~ 0
CLK_DISP
Text GLabel 5300 4700 0    50   Input ~ 0
CLK_DISP
Wire Wire Line
	4550 4600 5150 4600
Wire Wire Line
	5150 4600 5150 4500
Wire Wire Line
	5150 4500 5300 4500
Text GLabel 5700 5100 3    50   Input ~ 0
GND
Text GLabel 5900 3000 1    50   Input ~ 0
3V3
Text GLabel 4450 3250 2    50   Input ~ 0
SDA
Text GLabel 4450 3350 2    50   Input ~ 0
SCL
Text GLabel 4450 3450 2    50   Input ~ 0
3V3
Text GLabel 4450 3550 2    50   Input ~ 0
GND
Text GLabel 6900 4300 0    50   Input ~ 0
5V
Text GLabel 6000 3000 1    50   Input ~ 0
5V
Text GLabel 6900 4200 0    50   Input ~ 0
GND2
Text GLabel 5800 5100 3    50   Input ~ 0
GND2
Wire Wire Line
	6900 4000 6300 4000
$Comp
L power:+3.3V #PWR?
U 1 1 5FE773F4
P 8100 3500
F 0 "#PWR?" H 8100 3350 50  0001 C CNN
F 1 "+3.3V" V 8115 3628 50  0000 L CNN
F 2 "" H 8100 3500 50  0001 C CNN
F 3 "" H 8100 3500 50  0001 C CNN
	1    8100 3500
	0    -1   -1   0   
$EndComp
Text GLabel 9300 3600 2    50   Input ~ 0
VIN
Text GLabel 9300 3900 2    50   Input ~ 0
GND
$EndSCHEMATC
