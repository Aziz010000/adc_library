default: 
	avr-gcc -c -w -Os -DF_CPU=16000000UL -mmcu=atmega328p   main.c -o bare.o
	avr-gcc -c -w -Os -DF_CPU=16000000UL -mmcu=atmega328p   adc_lib.c -o push.o
	avr-ar rcs libper.a push.o bare.o
	avr-gcc -w -Os -DF_CPU=16000000UL -mmcu=atmega328p -o push.elf adc_lib.c -L. -lper
	avr-objcopy -O ihex -R .eeprom push.elf push.hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:push.hex
