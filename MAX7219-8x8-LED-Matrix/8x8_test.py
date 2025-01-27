import max7219 as led


amogus = ['00111100',
			'01111110',
			'11110001',
			'11110001',
			'11111110',
			'01111110',
			'01100110',
			'01100110']
led.init(0, 7, False, False)
led.image_out(led.test_image, 0)

led.sleep(2)
led.init(2, 4, False, False)
led.image_out(led.test_image, 0)

led.sleep(2)
led.init(0, 7, False, False)
led.image_out(led.rotate(amogus, 3), 0)
led.sleep(2)
led.image_out(led.rotate(amogus, 3), 1)
