#!/usr/bin/python

import sys,os
import time
import datetime


# https://wiki.python.org/moin/ForLoop
def my_range(start, end, step):
    while start <= end:
        yield start
        start += step

# for x in my_range(1, 10, 0.5):
#     print x


execfile("/home/pi/lights/nmap-equipment.py")


# CHOOSE WHICH LIGHTS TO USE HERE - this comes from the nmap file execution
theLights = BedroomLights
#theLights = FrontRoomLights
theLightsString = " ".join(theLights)


# Wake-up over XXX cycles

startAt = 0
stopAt = 100
stepSize = 1
totalMin = 5
numSteps = int(stopAt/stepSize)
print "there are '" + str(numSteps) + "' steps over " + str(totalMin*60) + " seconds."
delay = int(totalMin*60/numSteps)
print "So the delay should be " + str(delay)
print "Which gives us a " + str(delay*numSteps) + " second wakeup" #how long the whole process takes

if delay == 0: #because int is a floor function and could be 0
    delay = 0.5

theCommand = "/usr/local/bin/flux_led " + theLightsString + " --off" #all the ip addresses, turn the lights off?
print theCommand
os.system(theCommand) #is this what runs the command? the OS? is it running on command line?
time.sleep(5)




#put some code for color etc once we get the bulb we can look up the command set for it 



















for currentBrightness in my_range(startAt, stopAt, stepSize):
    #Don't use brightness value of 0, but 0 is better for counting. So use this workaround
    thisBrightness = currentBrightness
    if currentBrightness == 0:
        thisBrightness = 1
        
    print "\nBRIGHTNESS IS : " + str(thisBrightness) + "\n"
    # for ip in PorchLights:
        # print ip
    theCommand = "/usr/local/bin/flux_led " + theLightsString + " -w " + str(thisBrightness) + " --on"
    print theCommand
    os.system(theCommand)
    # os.system("/usr/local/bin/flux_led " + allPorchLights + " --on")
    time.sleep(delay)

# time.sleep(60)
# os.system("./porchLightsOff.py")




for cycle in my_range(0, 10, 1):
    theCommand = "/usr/local/bin/flux_led " + theLightsString + " --off"
    print theCommand
    os.system(theCommand)
    time.sleep(0.5)
    theCommand = "/usr/local/bin/flux_led " + theLightsString + " --on"
    print theCommand
    os.system(theCommand)
    time.sleep(2)


