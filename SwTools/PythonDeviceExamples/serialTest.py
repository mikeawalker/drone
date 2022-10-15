import serial
from serial import Serial
import time


fp2 = open("gpsOut.txt","w")
serialPort = Serial(port="/dev/ttyAMA0",
			baudrate=57600,
			parity=serial.PARITY_NONE,
			stopbits=serial.STOPBITS_ONE,
			bytesize=serial.EIGHTBITS,
			timeout=2)
if( serialPort.isOpen()==False):
	serialPort.open()

outStr=''
inStr=''

serialPort.flushInput()
serialPort.flushOutput()
x=0
serialPort.write("$PMTK220,1000*1F\r\n")
serialPort.write("$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n")
firstTime = True
while True:
	x  = (x+1)%10
	outStr = "LOL%d" % x
	#serialPort.write(outStr)
#	print "GOGO"
	time.sleep(0.01)
	#inStr = serialPort.read(100)
	inStr = serialPort.readline()
	fp2.write(inStr)
	fp2.write("\n")
	
	#print "sent: " + outStr
	#if( inStr == outStr):
	#	print "WORKED"
	#
	#else:
	#	print "Fail whale"
	print "Read: "  + inStr
	if( firstTime ):
#		serialPort.write("$PMTK314,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,*29")
		firstTime = False
serialPort.close()
fp2.close()
