#debug code used for our serial communication from arduino to raspberry pi

#!/usr/bin/python

import sys,os
import serial 
import time
import datetime

ser = serial.Serial('/dev/ttyACM0',9600)
alarmOn = 2
ycount=0
ncount = 0
ser.flushInput()
while True:
	#if ser.inWaiting():
		#match = ser.read()
	match = ser.read()
	print match 
	if match =='y':
		alarmOn = 1
		ycount = ycount+1
		print 'yes, '+ str(alarmOn) + ', ' + str(ycount)
	#	print alarmOn
	elif match =='n':
		alarmOn = 0
		ncount = ncount+1
	#	print ncount
		print 'no '+ str(alarmOn) + ', ' + str(ncount)
	else:
		ncount = 0
		ycount =0
		alarmOn = 2
		print alarmOn
	

		
#time.sleep(1)
