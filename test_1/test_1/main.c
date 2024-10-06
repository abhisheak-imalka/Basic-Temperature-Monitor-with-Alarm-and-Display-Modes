#include <avr/io.h>

#include <util/delay.h>
#define led PB2

int main(void)
{
	TCCR1A |= (1<<WGM11) | (1<<COM1B1); // Use COM1B1 instead of COM1A1
	TCCR1B |= (1<<WGM12) | (1<<CS11);
	DDRB |= (1<<led); // Use PB2 instead of PB1
	ICR1 = 1023;
	
	while (1)
	{
		// Gradually increase the brightness
		for (int i = 0; i < 1023; i++) {
			OCR1B = i; // Use OCR1B instead of OCR1A
			_delay_ms(20); // Delay to slow down the brightness change
		}

		// Gradually decrease the brightness
		
	}
}