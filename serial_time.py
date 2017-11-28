
 #!/usr/bin/python

#importing all of the necessary libraries for functionality
import sys,os
import serial 
import time
import datetime

#instantiate a counter for the loop
counter = 0

#call a youtube fn that will play a black screen video - we tried using fbi
# to display a black screen but were met with several errors
execfile("youtubeBlack.py")
# os.system("omxplayer -b") - attempt at using omx to display black

#create serial connection to arduino at given port, 9600 baud rate
ser = serial.Serial('/dev/ttyACM0',9600)

while True:
	t = datetime.datetime.now().time() #get time from pi

#SENDING TO ARDUINO
	
	#we needed to do some handling to make sure the number outputted
	#correctly for the string we send to the arduino lcd
	if t.hour < 10:
		thour = '0' + str(t.hour)	
	else:
		thour = str(t.hour)
	if t.minute < 10:
		tminute = '0' + str(t.minute)
	else:
		tminute = str(t.minute)

	time_now = 'Clock - ' + thour + ':' + tminute
	ser.write(time_now) #send to arduino

#RECEIVING FROM ARDUINO

	#we found that the pi was reading the entire serial buffer instead of
	# just the alarm value currently being sent, so we flush the input when 
	# reading text from arduino to pi
	ser.flushInput() 
	time.sleep(2)
	
	if ser.inWaiting(): #when there is data in the buffer...
		counter = counter + 1
		match = ser.read() 
		if match =='y':
			if counter == 1:
				os.system("sudo killall omxplayer")
			execfile("youtube.py") #script that streams a youtube video using omxplayer
	
#this was our attempt at getting the system to be self sufficient - ie you don't
#need to restart the program after the alarm is set. What we found is that the arduino serial
#port was sending a 'k' over to the pi, but the pi wasn't able to read it - perhaps due to timing 
#issues. We tried to work around via removing the sleep but then the 'y' wasn't coming through either.
#This would be a "next step" that would help us send new commands when the alarm is turned off.	

	#	if match =='k':
	#		os.system("killall omxplayer")
	#		execfile("youtubeBlack.py")

