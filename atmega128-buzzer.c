#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int press=0;

ISR(TIMER2_COMP_vect){
	if(press==1)
	PORTB=(~PORTB);
}


int main(void){
	unsigned char key;
	DDRB = 0b00000001;
	DDRE = 0b00000000;
	PORTE= 0b11111111;


	TCCR2=0b00001100; // CTC모드, 프리스케일러분주비256
	TIMSK=0b10000000;// 타이머2의비교일치인터럽트설정
	OCR2=119;// 비교일치값지정
	TCNT2=0; // 초기값
	SREG=0x80; // 전역인터럽트허용
	
	unsigned char input;
	
	while(1) {
		input=PINE;
		switch(input){
			case 0b11111110: // 도
			OCR2=119;
			press=1;
			break;
			
			case 0b11111101: // 레
			OCR2=106;
			press=1;
			break;
			
			case 0b11111011: // 미
			OCR2=95;
			press=1;
			break;
			
			case 0b11110111: // 파
			OCR2=89;
			press=1;
			break;
			
			case 0b11101111: // 솔
			OCR2=80;
			press=1;
			break;
			
			case 0b11011111: // 라
			OCR2=71;
			press=1;
			break;
			
			case 0b10111111: // 시
			OCR2=63;
			press=1;
			break;
			
			case 0b01111111: // 도
			OCR2=60;
			press=1;
			break;
			
			default:
			press=0;
			break;
		}
	}
}

