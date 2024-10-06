#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BUTTON_PIN PD2
#define BUTTON_PIN2 PD3
#define BUTTON_PIN3 PD4
#define sw1 PC0
#define sw2 PC1
#define sw3 PC2
#define sw4 PC3
#define decimalPoint PB4
#define Led_Light PC4



float count =0;
float resetvalue=0;
char num[]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
char c =0b00111001;
char F =0b01110001;
float b =32;

void setup()
{
	DDRC=0xff;
	DDRB = 0xff;
	DDRD =0x00;
	DDRD &= ~(1 << BUTTON_PIN)&(1<<BUTTON_PIN2)&(1<<BUTTON_PIN3);
	PORTD |=(1<<BUTTON_PIN)|(1<<BUTTON_PIN2)|(1<<BUTTON_PIN3);
	

	
	
	
	// Enable external interrupt INT0
	EIMSK |= (1 << INT0)|(1<<INT1);
	
	// Trigger on falling edge for INT0
	EICRA |= (1 << ISC01)|(1<<ISC11);
	
	// Enable global interrupts
	sei();
	
	
}

ISR(INT0_vect)
{
	// Toggle the LED state
	count++;
	resetvalue++;
	
	

}
ISR(INT1_vect){

	if (count>0)
	{
		count--;
		
		
	}

}
void displayCellsius(float count){
for(int i; i<20;i++){
	if (!(PIND & (1<<BUTTON_PIN3))){
		resetvalue =0;
	}
	
	if (count<10)
	{
		int givenNumber =count*1000;
		int decimalPart = givenNumber % 1000;
		
		
		PORTC =(1<<sw1);
		PORTB = num[givenNumber/1000 %10];
		_delay_ms(160);
		PORTB |=(1<<decimalPoint);
		_delay_ms(80);
		PORTB &=~(1<<decimalPoint);
		_delay_ms(80);
		
		
		
		PORTC = (1<<sw2);
		PORTB = num[decimalPart/100 %10];
		_delay_ms(200);
		PORTC = (1<<sw3);
		PORTB = num[decimalPart/10 %10];
		_delay_ms(200);
		PORTC = (1<<sw4);
		PORTB = num[decimalPart/1 %10];
		_delay_ms(200);
		
		
		
		
		
	}
	else if (count<100 )
	{
		int givenNumber =count*100;
		int decimalPart = givenNumber % 100;
		if (resetvalue>40)
		{
			PORTC ^=(1<<Led_Light);
			_delay_ms(100);
			
		}
		
		
		PORTC =(1<<sw1);
		PORTB = num[givenNumber/1000 %10];
		_delay_ms(200);
		
		PORTC=(1<<sw2);
		PORTB = num[givenNumber/100 %10];
		_delay_ms(180);
		PORTB |=(1<<decimalPoint);
		_delay_ms(40);
		PORTB &=~(1<<decimalPoint);
		//_delay_ms(80);
		
		PORTC=(1<<sw3);
		PORTB = num[decimalPart/10 %10];
		_delay_ms(200);
		PORTC =(1<<sw4);
		PORTB = num[decimalPart/1 %10];
		_delay_ms(200);
		
	}
	else if (count<1000)
	{
		int givenNumber =count*10;
		int decimalPart = givenNumber % 10;
		
		PORTC = (1<<sw1);
		PORTB = num[givenNumber/1000 %10];
		_delay_ms(200);
		
		PORTC =(1<<sw2);
		PORTB = num[givenNumber/100 %10];
		_delay_ms(200);
		
		PORTC = (1<<sw3);
		PORTB = num[givenNumber/10 %10];
		_delay_ms(66.67);
		PORTB |=(1<<decimalPoint);
		_delay_ms(66.67);
		PORTB &=~(1<<decimalPoint);
		_delay_ms(66.67);
		
		PORTC =(1<<sw4);
		PORTB = num[decimalPart/1 %10];
		_delay_ms(200);
		
		
	}
}

}



void displayFaran(float b){
		
for(int j;j<20;j++){
	if (!(PIND & (1<<BUTTON_PIN3))){
		resetvalue=0;
	}


	if (b<100 )
	{
		int givenNumber =b*100;
		int decimalPart = givenNumber % 100;
		
			
		PORTC =(1<<sw1);
		PORTB = num[givenNumber/1000 %10];
		_delay_ms(200);
		
		PORTC =(1<<sw2);
		PORTB = num[givenNumber/100 %10];
		_delay_ms(160);
		PORTB |=(1<<decimalPoint);
		_delay_ms(70.67);
		PORTB &=~(1<<decimalPoint);
		//_delay_ms(66.67);
		
		PORTC = (1<<sw3);
		PORTB = num[decimalPart/10 %10];
		_delay_ms(200);
		PORTC = (1<<sw4);
		PORTB = num[decimalPart/1 %10];
		_delay_ms(200);
		
	
		
		
	}
	else if (b<1000)
	{
		int givenNumber =b*10;
		int decimalPart = givenNumber % 10;
		if (resetvalue>40)
		{
			PORTC ^=(1<<Led_Light);
			_delay_ms(100);
			
		}
	
		
		PORTC = (1<<sw1);
		PORTB = num[givenNumber/1000 %10];
		_delay_ms(200);
		
		PORTC =(1<<sw2);
		PORTB = num[givenNumber/100 %10];
		_delay_ms(200);
		
		PORTC = (1<<sw3);
		PORTB = num[givenNumber/10 %10];
		_delay_ms(66.67);
		PORTB |=(1<<decimalPoint);
		_delay_ms(66.67);
		PORTB &=~(1<<decimalPoint);
		_delay_ms(66.67);
		
		PORTC =(1<<sw4);
		PORTB = num[decimalPart/1 %10];
		_delay_ms(200);
		
		
		
		
	}
}
}


void run(){
		

		b = count * 9.0 / 5.0 + 32.0;
		
		
		displayCellsius(count);
		
		displayFaran(b);
		
		
		
			
		
	
}


int main(void)
{
	setup();
	PORTD |=(1<<BUTTON_PIN3);
	while(1){
	run();
	
	}
	
	


	
	

}
