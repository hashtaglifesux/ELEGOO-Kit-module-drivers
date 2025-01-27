# Still need to implement pushbutton detection
import RPi.GPIO as gpio
import pygame

pygame.init()
screen = pygame.display.set_mode((130, 80))
pygame.display.set_caption('number')
bigfont = pygame.font.Font(None, 70)
clock = pygame.time.Clock()

clk = 21
dt = 20
sw = 16


gpio.setmode(gpio.BCM)
gpio.setup(sw, gpio.IN)
gpio.setup(dt, gpio.IN)
gpio.setup(clk, gpio.IN)


number = 0
color = (255, 255, 255)
while True:
    if gpio.input(sw):
        color = (255, 64, 16)
    else:
        color = (255, 255, 255)
    while not gpio.input(dt):
        flag = False
        while not gpio.input(clk):
            if gpio.input(dt):
                flag = True
                break
        if flag:
            number += 1
            break
    while not gpio.input(clk):
        flag = False
        while not gpio.input(dt):
            if gpio.input(clk):
                flag = True
                break
        if flag:
            number -= 1
            break
    screen.fill((16, 16, 16))
    numtext = bigfont.render(str(number), False, (255, 255, 255))
    screen.blit(numtext, (10, 10))
    pygame.display.flip()
    clock.tick(80)
