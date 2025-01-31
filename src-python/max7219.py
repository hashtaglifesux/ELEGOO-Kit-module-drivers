import RPi.GPIO as gpio
from time import sleep

# Device pinout - GPIO assignment 
cs = 22
clk = 23
din = 24

# make shift-out slower
delay = 0

gpio.setmode(gpio.BCM)
gpio.setup(cs, gpio.OUT)
gpio.setup(clk, gpio.OUT)
gpio.setup(din, gpio.OUT)


# shift out 16 bits
# address is a string with 4 binary digits eg. '1011'
# data is a string or array with 8 binary digits
# can also be an int array, or a str array
# if positive is 0, all data bits will be inverted
def shout(addr: str, data, positive: int):
    head = '0000' + addr  # unused leading zeroes + register address
    for bit in range(8):
        if int(head[bit]) == 1:
            gpio.output(din, True)
        else:
            gpio.output(din, False)
        gpio.output(clk, True)
        sleep(delay)
        gpio.output(clk, False)
    for bit in range(8):
        if int(data[bit]) == positive:
            gpio.output(din, True)
        else:
            gpio.output(din, False)
        gpio.output(clk, True)
        sleep(delay)
        gpio.output(clk, False)
    gpio.output(cs, True)
    sleep(delay)
    gpio.output(cs, False)
    gpio.output(clk, False)
    gpio.output(din, False)


# img can be an 8x8 2d array or array of strings
def image_out(img, mode):  # mode = 0 to invert the image
    shout('0001', img[0], mode)
    shout('0010', img[1], mode)
    shout('0011', img[2], mode)
    shout('0100', img[3], mode)
    shout('0101', img[4], mode)
    shout('0110', img[5], mode)
    shout('0111', img[6], mode)
    shout('1000', img[7], mode)


# initialize/configure the display (clears the display)
# intensity is display brightness, 0 is lowest
# scanlimit is the highest data register scanned
# shutdown_mode = True to enter the IC's shutdown mode
# display_test = True to enter the IC's display test mode
def init(intensity: int = 0, 
        scanlimit: int = 7, 
        shutdown_mode: bool = False, 
        display_test: bool = False):
    image_out(['00000000' for ln in range(8)], 1)
    shout('1100', '00000000', 1)
    sleep(delay)
    if display_test:
        shout('1111', '00000001', 1)
    else:
        shout('1111', '00000000', 1)
    if not shutdown_mode:
        shout('1100', '00000001', 1)
    shout('1001', '00000000', 1) 
    shout('1010', '{:08b}'.format(intensity), 1)
    shout('1011', '{:08b}'.format(scanlimit), 1)
    
    

# rotate an image 90 degrees ccw
# a is the image
# halfpi is the number of times to rotate 
def rotate(a, halfpi):
    for turn in range(halfpi%4):
        b = [[0, 0, 0, 0, 0, 0, 0, 0] for j in range(8)]
        for y in range(8):
            for x in range(8):
                b[7-x][y] = a[y][x]
        a = b
    return a


test_image = ['00000000',
          '01111110',
          '01000010',
          '01011010',
          '01011010',
          '01000010',
          '01111110',
          '00000000']

gpio.output(cs, False)
gpio.output(clk, False)
gpio.output(din, False)
