#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


volatile int direction=0;//0이 정방향.
volatile int currentspeed=2500;

void turnAndOff(){
	_delay_ms(500);
	while(PINE!=0b11111110){
		PORTB=0b00100011;
	}
	_delay_ms(500);
	if(direction==0)
	PORTB=0b00100010;	
	else if(direction==1)
	PORTB=0b00100001;
}

void changeDirection(){
	if(direction==1){
		PORTB=0b00100010;
		direction=0;
	}
	else if(direction==0){//정방향이면 역방향으로.
		PORTB=0b00100001;
		direction=1;
	}
}

void upSpeed(int n)
{
	if(currentspeed<4500)
	{
		currentspeed+=n;
		OCR1A=currentspeed;
	}
}

void downSpeed(int n)
{
	if(currentspeed>500)
	{
		currentspeed-=n;
		OCR1A=currentspeed;
	}
	
}
int main(){
	DDRE=0x00;
	PORTE=0xff;
	DDRB=0xff;
	
	
	PORTB=0b00100010;	
	//PORTD가 10이면 정방향 01이면 역방향
	
	//PORTD=0b00000000;
	//11이나 00시 정지
	
	TCCR1A=0b10000010;//OC1A noninverting mode, fast pwm mode
	TCCR1B=0b00011011;//,fast pwm mode, 분주비 64
	ICR1=4999;//0~4999시 16000000/64*5000=50 이므로 주기는 20ms
	

	SREG = 0x80;
	
	
	//PortB의 1의 비율이 높을수록 빨라짐.
	while(1){
		OCR1A=currentspeed;
		
		if(PINE==0b11111110)//첫번째 스위치
			turnAndOff();
		if(PINE==0b11111101)//두번째 스위치
			{changeDirection(); _delay_ms(2000);}
		if(PINE==0b11111011)//세번째 스위치
			{upSpeed(500); _delay_ms(2000); }
		if(PINE==0b11110111)
			{downSpeed(500); _delay_ms(2000);}
	}
	return 0;
}
