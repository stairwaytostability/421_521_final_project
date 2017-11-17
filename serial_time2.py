#!/usr/bin/python

import sys,os
import serial 
import time
import datetime

ser = serial.Serial('/dev/ttyACM0',9600)
alarmOn = 0
print 'about to enter loop'

t = datetime.datetime.now().time()
print t
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
print 'I wrote'
#print time_now
ser.flushInput() 
time.sleep(2)
while True:
	if ser.inWaiting():
		match = ser.read()
		print 'I read ' + str(match)		 
		if match =='y':
			alarmOn = 1
	#		execfile("youtube.py")	
		if match =='k':
			alarmOn = 0
	#		os.system("killall omxplayer")
		print alarmOn	

