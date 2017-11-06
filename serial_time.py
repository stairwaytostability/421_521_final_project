#!/usr/bin/python

import sys,os
import serial 
import time
import datetime

ser = serial.Serial('/dev/ttyACM0',9600)


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
	print time_now
	time.sleep(2)
