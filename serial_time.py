#!/usr/bin/python

import sys,os
import serial 
import time
import datetime

ser = serial.Serial('/dev/ttyACM0',9600)
alarmOn = 0

while True:
	t = datetime.datetime.now().time()

	if t.hour < 10:
		thour = '0' + str(t.hour)	
	else:
		thour = str(t.hour)

	if t.minute < 10:
		tminute = '0' + str(t.minute)
	else:
		tminute = str(t.minute)

	time_now = 'Clock - ' + thour + ':' + tminute
	ser.write(time_now)
	#print time_now
	time.sleep(2)
	
	if ser.inWaiting():
		match = ser.read() 
		if match =='y':
			alarmOn = 1
		if match =='n':
			alarmOn = 0
	print alarmOn	
	
