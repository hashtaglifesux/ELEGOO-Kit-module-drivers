import RPi.GPIO as gpio
from time import time, sleep

# Device pinout - GPIO assignment 
trig = 22
echo = 27

mach = 343 # speed of sound in m/s


gpio.setmode(gpio.BCM)
gpio.setup(trig, gpio.OUT)
gpio.setup(echo, gpio.IN)

def measure():
    gpio.output(trig, True)
    start = time.time()
    sleep(0.00004) # minimum is 0.00001
    gpio.output(trig, False)
    while not gpio.input(echo):
         pass
    end = time.time()
    return (end-start) * mach / 2