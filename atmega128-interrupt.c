#define F_CPU 16000000
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int count=0;
int flag=0;

ISR(INT0_vect){
	PORTB=255;
	_delay_ms(250);
	flag=1; //불꺼진상태

	while(1)
	{
		if(PIND==0b11111110){
			flag=0;//켜진상태
			PORTB=255-count;
			_delay_ms(250);
			break;
		}
	}
}
ISR(INT1_vect){
	_delay_ms(150);

	if(flag==0){
		count++;
		PORTB=255-count;

	}
}
ISR(INT2_vect){
	_delay_ms(150);

	if(flag==0){
		if(count>0)
			count--;
		PORTB=255-count;
	}
}

ISR(INT3_vect){
	_delay_ms(150);
	count=0;
	PORTB=255-count;
	flag=0;
}

int main(void){
	DDRB = 0b11111111;// 출력설정
	DDRD = 0b00000000;// 입력설정
	PORTD = 0b11111111; // 풀업저항설정
	
	EICRA = 0b10101010; //인터럽트트리거방식설정
	EIMSK = 0b00001111; //인터럽트허용설정
	SREG = 0x80; //전체인트럽트허가

	PORTB=255;
	while(1){
	}
}
