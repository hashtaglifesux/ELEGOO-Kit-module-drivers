# Still need to implement pushbutton detection
import RPi.GPIO as gpio
import pygame # only for testing

# only for testing
pygame.init()
screen = pygame.display.set_mode((130, 80))
pygame.display.set_caption('number')
bigfont = pygame.font.Font(None, 70)
clock = pygame.time.Clock()

# Device pinout - GPIO assignment 
clk = 21
dt = 20
sw = 16


gpio.setmode(gpio.BCM)
gpio.setup(sw, gpio.IN)
gpio.setup(dt, gpio.IN)
gpio.setup(clk, gpio.IN)


number = 0 # only used for testing
while True:
    while not gpio.input(dt):
        flag = False
        while not gpio.input(clk):
            if gpio.input(dt):
                flag = True
                break
        if flag:
            number += 1 # only for testing
            # dosomethinguseful()
            break
    while not gpio.input(clk):
        flag = False
        while not gpio.input(dt):
            if gpio.input(clk):
                flag = True
                break
        if flag:
            number -= 1 # only for testing
            # dosomethingelseuseful()
            break
    
    # only for testing
    screen.fill((16, 16, 16))
    numtext = bigfont.render(str(number), False, (255, 255, 255))
    screen.blit(numtext, (10, 10))
    pygame.display.flip()
    clock.tick(80)
