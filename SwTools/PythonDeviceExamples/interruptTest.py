#!/usr/bin/env python2.7


import time
import RPi.GPIO as GPIO


# handle the button event
def buttonEventHandler (pin):
    print "GPIO DOIT"
    time.sleep(1)



# main function
def main():

    # tell the GPIO module that we want to use 
    # the chip's pin numbering scheme
    GPIO.setmode(GPIO.BCM)

    # setup pin 23 as an input
    # and set up pins 24 and 25 as outputs
    GPIO.setup(18,GPIO.IN)
   

    # tell the GPIO library to look out for an 
    # event on pin 23 and deal with it by calling 
    # the buttonEventHandler function
    GPIO.add_event_detect(18,GPIO.FALLING)
    GPIO.add_event_callback(18,buttonEventHandler,100)

  
    GPIO.output(24,True)

    # make the red LED flash
    while True:
        time.sleep(1)


    GPIO.cleanup()



if __name__=="__main__":
    main()

