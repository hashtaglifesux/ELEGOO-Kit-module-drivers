import RPi.GPIO as gpio
from time import time, sleep

# Device pinout - GPIO assignment 
trig = 27
echo = 22

gpio.setmode(gpio.BCM)
gpio.setup(trig, gpio.OUT)
gpio.setup(echo, gpio.IN)

# returns the distance in meters
# mach = speed of sound in m/s
def measure(mach: int = 343):
    gpio.output(trig, True)
    sleep(0.00001) # minimum is 0.00001
    gpio.output(trig, False)
    while not gpio.input(echo):
         pass
    start = time()
    while gpio.input(echo):
         pass
    end = time()
    return (end-start)*mach/2


# vt = d