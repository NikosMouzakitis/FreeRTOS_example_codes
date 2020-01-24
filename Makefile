ARDUINO_LIBS = FreeRTOS 
MONITOR_PORT = /dev/ttyACM0

## when working with Arduino Mega
#####
BOARD_TAG	= mega 
BOARD_SUB	= atmega2560 
AVRDUDE_MCU	= atmega2560
######



include /home/nicko/Downloads/arduino-1.8.5/Arduino-Makefile-master/Arduino.mk

