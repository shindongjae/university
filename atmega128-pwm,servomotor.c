#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>


volatile unsigned char ch;
volatile unsigned char temp[100];
volatile unsigned int a=0;

void onechar(char c){
	while( (UCSR0A & (1<<UDRE0)) == 0 );//버퍼 쓸 준비 되지 않았다면 대기
	UDR0 = c;//c출력
}

void str(char *str){ //문자열 출력 함수
	while(*str!='\0'){
		onechar(*str);
		str++;
	}
}
ISR(USART0_RX_vect){//각도를 입력받아서 엔터키 누르면 setservo로 전달
	ch= UDR0;
	UDR0= ch;

	if(ch!=13)
		a=a*10+(ch-48); //바로 temp[i]=UDR0 했을시 오류남.
		
	else
		setservo(a);
}

void setservo(int n){ //입력받은 각도를 10ms~20ms에 해당하는 값으로 변환.
	unsigned volatile int x=250;
	unsigned volatile int y=250*n;
	unsigned volatile int z=y/180; //안해주면 오류남.
	OCR1A=x+z;
	_delay_ms(1000);
}


int main(void)
{
	UCSR0A = 0x00;
	UCSR0B = 0b10011000; // RXCIE0=1, TXEN0=1, RXEN0=1
	UCSR0C = 0b10000110; // 비동기통신, 패리티없음,
	// 데이터비트: 8비트, 정지비트: 1비트
	UBRR0H = 0;
	UBRR0L = 103;
	SREG = 0x80;
	
	DDRB=255;
	PORTB=255;
	
	TCCR1A=0b10000010;//OC1A noninverting mode, fast pwm mode
	TCCR1B=0b00011011;//,fast pwm mode, 분주비 64
	ICR1=4999;//0~4999시 16000000/64*5000=50 이므로 주기는 20ms
	//250이 10ms 500이 20ms
	
	str("input : \n");

	while(1){
	}
}
