#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int term=500;

void check(){
	if(PINF==0b11000000){ //첫번째 스위치가 작동한경우
		_delay_ms(500);
		while(1){ //스위치가 다시 작동하면 루프문 빠져나가고, 그사이에 2,3번째 
//속도조절 스위치 작동시 작동하도록 설정.
			if(PINF==0b11100000)
			break;
		
			if(PINF==0b10000000){
				_delay_ms(250);
				if(term>100)
				term-=100;
			}
			if(PINF==0b01000000){
				_delay_ms(250);
				term+=100;
			}		
		}
	}
	
	if(PINF==0b10100000){//한번 누를때마다 100ms까지 100ms씩 term을 줄인다
		_delay_ms(250);
		if(term>100)
		term-=100;
	}
	if(PINF==0b01100000){//한번 누를때마다 term을100ms씩 늘린다.
		_delay_ms(250);
		term+=100;
	}
}

void delay(int t){
	for(int i=0;i<t;i++){
		_delay_ms(1);
		check();
	}
}

int main(void){
	DDRF = 0x00; // 입출력방향설정
	DDRB = 0xFF; // 입출력방향설정
	PORTF = 0b11100000; // 풀업저항설정
	PORTB=	0x00;
	
	while(1)
	{
		int led=1;
		while(led!=256){
			PORTB=0xFF-led;
			led*=2;
			if(led!=256)
			delay(term);
		}
		while(led!=1){
			led/=2;
			PORTB=0xFF-led;
			if(led!=1)
			delay(term);
		}
	}
}
