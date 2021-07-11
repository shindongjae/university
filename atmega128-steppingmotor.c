#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int status=0;
volatile int speed=200;


ISR(INT0_vect){
	speed+=10;
}

ISR(INT1_vect){
	speed-=10;
}

ISR(INT2_vect){
	if(status==1)
	status=0;
	else if(status==0)
	status=1;
}

ISR(INT3_vect){

}


int main(){
	DDRB = 0xff ;
	PORTB = 0x00001000;
	
	DDRD=0x00;
	PORTD=0xff;
	
	EICRA = 0b10101010; //인터럽트트리거방식설정
	EIMSK = 0b00001111; //인터럽트허용설정
	SREG = 0x80; //전체인트럽트허가


	while(1){
		if(status==0){
			PORTB = 0b00001000;
			_delay_ms(speed);
			PORTB = 0b00000100;
			_delay_ms(speed);
PORTB = 0b00000010;
			_delay_ms(speed);
PORTB = 0b00000001;
			_delay_ms(speed);
		}
		else if(status==1)
		{
			PORTB = 0b00000001;
			_delay_ms(speed);
			PORTB = 0b00000010;
			_delay_ms(speed);
PORTB = 0b00000100;
			_delay_ms(speed);
PORTB = 0b00001000;
			_delay_ms(speed);
		}
	}
	return 0 ;
}
