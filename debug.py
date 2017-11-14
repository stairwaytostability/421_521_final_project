#!/usr/bin/python

import sys,os
import serial 
import time
import datetime

ser = serial.Serial('/dev/ttyACM1',9600)
alarmOn = 0

while True:
	if ser.inWaiting():
		match = ser.read() 
		if match =='y':
			alarmOn = 1
		if match =='n':
			alarmOn = 0
	print alarmOn	
	time.sleep(1)
