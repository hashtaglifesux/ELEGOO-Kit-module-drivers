import pygame
import HCSR04

pygame.init()
screen = pygame.display.set_mode((330, 80))
pygame.display.set_caption('number')
bigfont = pygame.font.Font(None, 70)
clock = pygame.time.Clock()

while True:
    screen.fill((16, 16, 16))
    numtext = bigfont.render(str(HCSR04.measure())[0:6], False, (255, 255, 255))
    screen.blit(numtext, (10, 10))
    pygame.display.flip()
    clock.tick(5)


