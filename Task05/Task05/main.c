/*
 * task03.c
 *
 * Created: 6/3/2024 4:15:07 PM
 * Author : acer
 */ 

#include <avr/io.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//Define pins**********************

#define BUTTON_PIN PD2
#define BUTTON_PIN2 PD3
#define BUTTON_PIN3 PD4
#define BUTTON_PIN4 PD0
#define BUTTON_PIN5 PD1
#define sw1 PB0					
#define sw2 PB3
#define sw3 PB4
#define sw4 PB5
#define decimalPoint PC5
#define Led_Light PC4
#define LedCold PD5
#define LedNormal PD6
#define LedWarmth PB1
#define LedHot PB2


//define variables************

float count =0;
float resetvalue=0;
char num[]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09}; 
char c =0b00111001;
char F =0b01110001;
float b =32;
int faranCels=0;
int modeShift =0;

//interupts setups ********

void setup()
{
	DDRC=0xff;
	DDRB = 0xff;
	DDRD =0x00;
	DDRD &= ~(1 << BUTTON_PIN)&(1<<BUTTON_PIN2)&(1<<BUTTON_PIN3)&(1<<BUTTON_PIN4)|(1<<BUTTON_PIN5);
	PORTD |=(1<<BUTTON_PIN)|(1<<BUTTON_PIN2)|(1<<BUTTON_PIN3)|(1<<BUTTON_PIN4)|(1<<BUTTON_PIN5);
	

	
	
	
	// Enable external interrupt INT0
	EIMSK |= (1 << INT0)|(1<<INT1);
	
	// Trigger on falling edge for INT0
	EICRA |= (1 << ISC01)|(1<<ISC11);
	
	// Enable global interrupts
	sei();

	
	
}

//first interrupts(ButtonPin 1)***********************


ISR(INT0_vect)
{
	// Toggle the LED state
	count++;
	resetvalue++;
	
	

}

//second interrupt (Buttonpin 2)***********************
ISR(INT1_vect){

	if (count>0)
	{
		count--;
		
		
	}

}

//celsius section****************

void displayCellsius(float count){
	for(int i; i<20;i++){
		if (!(PIND & (1<<BUTTON_PIN3))){
			resetvalue =0;
		}
		else if (!(PIND & (1<<BUTTON_PIN4))){
				if (faranCels==0)
				{
					faranCels=1;
				}
				else {
					faranCels=0;
				}
		}
		else if (!(PIND & (1<<BUTTON_PIN5))){
			if (modeShift==0)
			{
				modeShift=1;
			}
			else {
				modeShift=0;
			}
		}
	
		
		
		if (count<10)
		{
			int givenNumber =count*1000;
			int decimalPart = givenNumber % 1000;
			
			
			PORTB =(1<<sw1);
			PORTC = num[givenNumber/1000 %10];
			_delay_ms(160);
			PORTC |=(1<<decimalPoint);
			_delay_ms(80);
			PORTC &=~(1<<decimalPoint);
			_delay_ms(80);
			
			
			
			PORTB = (1<<sw2);
			PORTC = num[decimalPart/100 %10];
			_delay_ms(200);
			PORTB = (1<<sw3);
			PORTC = num[decimalPart/10 %10];
			_delay_ms(200);
			PORTB = (1<<sw4);
			PORTC = num[decimalPart/1 %10];
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
			
			
			PORTB =(1<<sw1);
			PORTC = num[givenNumber/1000 %10];
			_delay_ms(200);
			
			PORTB=(1<<sw2);
			PORTC = num[givenNumber/100 %10];
			_delay_ms(180);
			PORTC |=(1<<decimalPoint);
			_delay_ms(40);
			PORTC &=~(1<<decimalPoint);
			//_delay_ms(80);
			
			PORTB=(1<<sw3);
			PORTC = num[decimalPart/10 %10];
			_delay_ms(200);
			PORTB =(1<<sw4);
			PORTC = num[decimalPart/1 %10];
			_delay_ms(200);
			
		}
		else if (count<1000)
		{
			int givenNumber =count*10;
			int decimalPart = givenNumber % 10;
			
			PORTB = (1<<sw1);
			PORTC = num[givenNumber/1000 %10];
			_delay_ms(200);
			
			PORTB =(1<<sw2);
			PORTC = num[givenNumber/100 %10];
			_delay_ms(200);
			
			PORTB = (1<<sw3);
			PORTC = num[givenNumber/10 %10];
			_delay_ms(66.67);
			PORTC |=(1<<decimalPoint);
			_delay_ms(66.67);
			PORTC &=~(1<<decimalPoint);
			_delay_ms(66.67);
			
			PORTB =(1<<sw4);
			PORTC = num[decimalPart/1 %10];
			_delay_ms(200);
			
			
		}
		
	}

}

//farenhite section **********************

void displayFaran(float b){
	
	for(int j;j<20;j++){
		if (!(PIND & (1<<BUTTON_PIN3))){
			resetvalue=0;
		}
		else if (!(PIND & (1<<BUTTON_PIN4))){
			if (faranCels==0)
			{
				faranCels=1;
			}
			else {
				faranCels=0;
			}
		}
		else if (!(PIND & (1<<BUTTON_PIN5))){
			if (modeShift==0)
			{
				modeShift=1;
			}
			else {
				modeShift=0;
			}
		}


		if (b<100 )
		{
			int givenNumber =b*100;
			int decimalPart = givenNumber % 100;
			
			
			PORTB =(1<<sw1);
			PORTC = num[givenNumber/1000 %10];
			_delay_ms(200);
			
			PORTB =(1<<sw2);
			PORTC = num[givenNumber/100 %10];
			_delay_ms(160);
			PORTC |=(1<<decimalPoint);
			_delay_ms(70.67);
			PORTC &=~(1<<decimalPoint);
			//_delay_ms(66.67);
			
			PORTB = (1<<sw3);
			PORTC = num[decimalPart/10 %10];
			_delay_ms(200);
			PORTB = (1<<sw4);
			PORTC = num[decimalPart/1 %10];
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
			
			
			PORTB = (1<<sw1);
			PORTC = num[givenNumber/1000 %10];
			_delay_ms(200);
			
			PORTB =(1<<sw2);
			PORTC = num[givenNumber/100 %10];
			_delay_ms(200);
			
			PORTB = (1<<sw3);
			PORTC = num[givenNumber/10 %10];
			_delay_ms(66.67);
			PORTC |=(1<<decimalPoint);
			_delay_ms(66.67);
			PORTC &=~(1<<decimalPoint);
			_delay_ms(66.67);
			
			PORTB =(1<<sw4);
			PORTC = num[decimalPart/1 %10];
			_delay_ms(200);
			
			
			
			
		}
	}
}
// mode (only display celsius value) *****************

void run1(){
	

	b = count * 9.0 / 5.0 + 32.0;
	
		displayCellsius(count);
			if (!(PIND & (1<<BUTTON_PIN4))){
				if (faranCels==0)
				{
					faranCels=1;
					
				}
				else {
					faranCels=0;
					
				}
			}
			
			if (!(PIND & (1<<BUTTON_PIN5))){
				if (modeShift==0)
				{
					modeShift=1;
					
				}
				else {
					modeShift=0;
					
				}
			}
		

		
	
}

//mode (Display faranhite )********************

void run2(){
	
	b = count * 9.0 / 5.0 + 32.0;
	
		displayFaran(b);
		
		
		if (!(PIND & (1<<BUTTON_PIN4))){
			if (faranCels==0)
			{
				faranCels=1;
				
			}
			else {
				faranCels=0;
				
			}
		}
		
		if (!(PIND & (1<<BUTTON_PIN5))){
			if (modeShift==0)
			{
				modeShift=1;
			
			}
			else {
				modeShift=0;
				
			}
		}
	
}


// mode display LIght only

void run3(int vlaue){
	
	ledLight(count);
	ledLightSecond(count);
	ledLightThird(count);
	
	PORTB &=~(1<<sw4);
	
		if (!(PIND & (1<<BUTTON_PIN4))){
			if (faranCels==0)
			{
				faranCels=1;
				
			}
			else {
				faranCels=0;
				
			}
		}
		
		if (!(PIND & (1<<BUTTON_PIN5))){
			if (modeShift==0)
			{
				modeShift=1;
			}
			else {
				modeShift=0;
			}
		}
		
		if (resetvalue>40)
		{
			PORTC |=(1<<Led_Light);
			_delay_ms(50);
			PORTC &=~(1<<Led_Light);
			
			
			
		}
		
		
		
	
}

// run final 

void finalRun(){
	
	if(modeShift==0){
		if (faranCels ==0)
		{
			run2();
		
		}
		else
		{
			run1();
		}
	}
	else if(modeShift==1)
		{
			run3(resetvalue);
		}
	
}
	
	//PWM signal for PD pins

void ledLight(float num){
		TCCR0A |=(1<<WGM00)|(1<<WGM01)|(1<<COM0A1) | (1<<COM0B1);//FAST PULSE WIDTH WGM01,WGM02
		//SELCT NONINVERTING OUTPUT PD6 =COMOA1
		
		
		TCCR0B |=(1<<CS02);//FIND PRESCALER WITH FORMULA AND COME 256 AS A VALUE SET THIS VALUE TCROB REGISTER
		
		DDRD|=(1<<LedCold) | (1<<LedNormal); //DEFINE OUTPUT
		
		if (num <= 15)
		{
				num =num*16;
				OCR0A=num;
				_delay_ms(10);
				OCR0A=0;
				
				
		}else if (num<=25)
		
		{
			OCR0A =0;
			int temp = num;
			
			temp =temp%15;
			OCR0B =temp*16;
			_delay_ms(10);
			OCR0B=0;
		}
		else if(num>25){
			OCR0B =0;
			OCR0A =0;
			
			
			
		}
		
		
		if (!(PIND & (1<<BUTTON_PIN3))){
			resetvalue=0;
		}
		
		
		
		
	
}


//PWM signal for PC pins


void ledLightSecond(float num){
		TCCR1A |=(1<<WGM11)|(1<<COM1A1) |(1<COM1B1);
		TCCR1B |=(1<<WGM12)|(1<<CS11);
		
		DDRB |=(1<<LedWarmth) | (1<<LedHot);
		ICR1=1023;
		
		
		if (num<25){
			OCR1A =0;
			OCR1B =0;
		}
		
		else if(num>25)
		{
			if (num>35)
			{
				OCR1A=0;
				_delay_ms(10);
			}
			else
			{
			
			int temp = num;
			temp = temp%25;
			temp =temp*16;
			
			OCR1A =temp;
			_delay_ms(10);
			OCR1A=0;
			}
			
			
		
		}
		
		if (!(PIND & (1<<BUTTON_PIN4))){
				if (faranCels==0)
				{
					faranCels=1;
				}
				else {
					faranCels=0;
				}
			}
			
		if (!(PIND & (1<<BUTTON_PIN5))){
				if (modeShift==0)
				{
					modeShift=1;
				}
				else {
					modeShift=0;
				}
			}
		if (!(PIND & (1<<BUTTON_PIN3))){
			resetvalue=0;
		}
		
		
}

// pWM signgal for PC1 pin

void ledLightThird(float count){
	TCCR1A |= (1<<WGM11) | (1<<COM1B1); // Use COM1B1 instead of COM1A1
	TCCR1B |= (1<<WGM12) | (1<<CS11);
	DDRB |= (1<<LedHot); // Use PB2 instead of PB1
	ICR1 = 1023;
		if (count<=35)
		{
			OCR1B=0;
			_delay_ms(10);
			
		}
		else if (count>35)
		{
			if (count>40)
			{
				OCR1B=0;
				_delay_ms(10);
			}
			else{
			int temp =count;
			temp=temp%35;
			temp=temp*100;
			
			OCR1B = temp; // Use OCR1B instead of OCR1A
			_delay_ms(10); // Delay to slow down the brightness change
			OCR1B=0;
			}
		}
	
		
	if (!(PIND & (1<<BUTTON_PIN4))){
		if (faranCels==0)
		{
			faranCels=1;
		}
		else {
			faranCels=0;
		}
	}
	
	if (!(PIND & (1<<BUTTON_PIN5))){
			if (modeShift==0)
			{
				modeShift=1;
			}
			else {
				modeShift=0;
			}
		}
		
	if (!(PIND & (1<<BUTTON_PIN3))){
		resetvalue=0;
	}
	
	

	

}

		
	


	



int main(void)
{
	setup();
	PORTD |=(1<<BUTTON_PIN3)|(1<<BUTTON_PIN4)|(1<<BUTTON_PIN5);
	while(1){
		
	if (!(PIND & (1<<BUTTON_PIN4))){
		if (faranCels==0)
		{
			faranCels=1;
		}
		else {
			faranCels=0;
		}
	}
	
	if (!(PIND & (1<<BUTTON_PIN5))){
			if (modeShift==0)
			{
				modeShift=1;
			}
			else {
				modeShift=0;
			}
		}
		
	
	finalRun();
	
	}
}

		

	
	


	
	






