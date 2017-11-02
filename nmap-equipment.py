#!/usr/bin/python

import sys,os
import time
import datetime
import math
import collections

from bs4 import BeautifulSoup
# HOW TO INSTALL BEAUTIFULSOUP4
# $ sudo pip install beautifulsoup4




BedroomLights = []



AnotherNow = datetime.datetime.now()
print AnotherNow

# thetime = now.time()
# print thetime

formattedDatetime = AnotherNow.strftime("%A, %B %d, %Y @ %I:%M:%S %p")
print formattedDatetime


# FILENAME
resultsFilename = "/home/pi/lights/nmap-results.txt"


# theCommand = "/bin/echo '" + formattedDatetime + "' > " + resultsFilename
# print theCommand
# os.system(theCommand)



# theCommand = "/usr/bin/sudo /usr/bin/nmap -sn 192.168.1.0/24 >> " + resultsFilename
# OUTPUT IN XML FORMAT FOR PROCESSING WITH BEAUTIFULSOUP FTW
theCommand = "/usr/bin/sudo /usr/bin/nmap -sn 192.168.1.0/24 -oX " + resultsFilename
print theCommand
os.system(theCommand)


# Now we need to generate the master array of current IP ADDRESSES WITH DEVICES AND DESCRIPTIONS AND COMPARE AGAINST KNOWN MAC ADDRESSES
# https://pymotw.com/2/collections/ordereddict.html
# print '\nOrderedDictionary:'
nmappings = collections.OrderedDict()


# Read the nmap-results.txt file and parse it line by line for CURRENT IP ADDRESSES FOR EACH MAC ADDRESS
source = open(resultsFilename, "r")
# for line in nmapResults:
#     print line
source.seek(0)

soup = BeautifulSoup(source, "html.parser")
# divTags = soup.find_all("div", {"id": "content"})
hostTags = soup.find_all("host")

for index,tag in enumerate(hostTags):
    # print len(tag)
    # print index
    # print "\n"
    # print repr(tag)
    
    addresses = tag.findAll('address')
    # print addresses
    theMac = ""
    theIP = ""
    theVendor = "none"
    for anAddress in addresses:
        # print "\n"
        # print anAddress
        # print type(anAddress)
        # print dir(anAddress)
        # print anAddress['addr'], anAddress["addrtype"]
        if anAddress.has_attr('addrtype') and anAddress["addrtype"] == "ipv4":
            theIP = anAddress['addr']
        if anAddress.has_attr('addrtype') and anAddress["addrtype"] == "mac":
            theMac = anAddress['addr']
            if anAddress.has_attr('vendor'):
                theVendor = anAddress['vendor']
    if theMac:
        print theMac + " --> " + theIP + ", vendor: " + theVendor
        nmappings[theMac] = theIP


# for k, v in nmappings.items():
#     print k, v


# MASTER LIST OF WHICH DEVICE IS WHERE

bedroomLightsMAC = ["MAC ADDRESS HERE"]
bedroomLightsMAC += ["MAC ADDRESS HERE"]
bedroomLightsMAC += ["MAC ADDRESS HERE"]
bedroomLightsMAC += ["MAC ADDRESS HERE"]



# Lookup by MAC ADDRESS AND POPULATE THE ACTUAL IP ADDRESSES NOW

for bigMac in bedroomLightsMAC:
    #IF LIGHTS ARE OFF, THEY WILL NOT BE ON THE NETWORK, SO nmappings.get(bigMac) will return None. So test if it exists first before populating the final array with IP addresses
    if nmappings.get(bigMac):
        BedroomLights += [nmappings.get(bigMac)]


if BedroomLights:
    BedroomLightsString = " ".join(BedroomLights)

