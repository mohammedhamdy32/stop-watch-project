#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char num1=0,num2=0,num3=0,num4=0,num5=0,num6=0;
unsigned char  tick1=0,tick2=0,tick3=0,tick4=0,tick5=0,tick6=0;

/* Mohammed hamdy halim */

void inti_timer1A()
{
	TCCR1B = (1<<WGM12) | (1<<CS12) | (1<<CS10);

	TCNT1 =0;

	OCR1A =976;

	TIMSK |=  (1<<OCIE1A);

	sei(); //enable global interrupt

}

void inti_INT0(void)
{
	MCUCR |= (1<<ISC01);//falling edge
	MCUCR &= ~(1<<ISC00);

	GICR |= (1<<INT0);//open INT0 enable

}

void inti_INT1(void)
{
	MCUCR |= (1<<ISC11) | (1<<ISC10);//raising edge

	GICR |= (1<<INT1);//open INT1 enable

}

void inti_INT2()
{
	MCUCSR &= ~(1<<ISC2);//falling edge

	GICR |= (1<<INT2);//open INT2 enable

}

ISR (TIMER1_COMPA_vect)
{


		if(num1==9)
			num1=0;
		else
			num1++;
		tick2++;


	if(tick2==10)//for every 10 sec
	{
		if(num2==5)
			num2=0;
		else
		    num2++;

		tick2=0;
		tick3++;
	}

	if(tick3==6)//for every min
	{
		if(num3==9)
			num3=0;
		else
			num3++;
		tick3=0;
		tick4++;
	}

	if(tick4==10)//for every 10 min
	{
		if(num4==5)
			num4=0;
		else
		    num4++;

		tick4=0;
		tick5++;
	}

	if(tick5==6)//for every hour
	{
		if(num5==9)
			num5=0;
		else
	    	num5++;

		tick5=0;
		tick6++;
	}

	if(tick6==10)//for every 10 hour
	{
		if(num6==9)
			num6=0;
		else
	    	num6++;

		tick6=0;
	}


}

ISR(INT0_vect)
{
	num1=0;
	num2=0;
	num3=0;
	num4=0;
	num5=0;
	num6=0;
	tick1=0;
	tick2=0;
	tick3=0;
	tick4=0;
	tick5=0;
	tick6=0;
}


ISR(INT1_vect)
{
	TCCR1B &= ~(1<<CS10) & ~(1<<CS11) & ~(1<<CS12);
}

ISR(INT2_vect)
{
	TCCR1B |= (1<<CS10) | (1<<CS12);
	TCCR1B &= ~(1<<CS11);
}


int main(void)
{
	//make enables as output
	DDRA |= (1<<PA0) | (1<<PA1) | (1<<PA2) | (1<<PA3) | (1<<PA4) | (1<<PA5);
	PORTA &= ~(1<<PA0) & ~(1<<PA1) & ~(1<<PA2) & ~(1<<PA3) & ~(1<<PA4) & ~(1<<PA5);

	//make inputs of 7447 as outputs
	DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3);
	PORTC = (PORTC&0XF0) | (0X00);

	//make INT0,INT1,INT2 as input
	DDRD &= ~(1<<INT0) & (1<<INT0);
	DDRB &= (1<<INT2);

	inti_timer1A();

	inti_INT0();

	inti_INT1();

	inti_INT2();



	for(;;)
	{

		PORTA &= ~(1<<PA0) & ~(1<<PA4) & ~(1<<PA3) & ~(1<<PA2) & ~(1<<PA1) ;
		PORTA |= (1<<PA5);
        PORTC=num1;
		_delay_ms(2);


		PORTA &= ~(1<<PA5) & ~(1<<PA0) & ~(1<<PA3) & ~(1<<PA2) & ~(1<<PA1) ;
		PORTA |= (1<<PA4);
		PORTC=num2;
		_delay_ms(2);


		PORTA &= ~(1<<PA5) & ~(1<<PA4) & ~(1<<PA0) & ~(1<<PA2) & ~(1<<PA1) ;
		PORTA |= (1<<PA3);
		PORTC=num3;
		_delay_ms(2);


		PORTA &= ~(1<<PA5) & ~(1<<PA4) & ~(1<<PA3) & ~(1<<PA0) & ~(1<<PA1) ;
		PORTA |= (1<<PA2);
		PORTC=num4;
		_delay_ms(2);


		PORTA &= (1<<PA5) & ~(1<<PA4) & ~(1<<PA3) & ~(1<<PA2) & ~(1<<PA0) ;
		PORTA |= (1<<PA1);
		PORTC=num5;
		_delay_ms(2);

		PORTA &= ~(1<<PA5) & ~(1<<PA4) & ~(1<<PA3) & ~(1<<PA2) & ~(1<<PA1) ;
		PORTA = (1<<PA0);
		PORTC=num6;
		_delay_ms(2);



	}



}

