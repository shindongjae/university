#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

volatile unsigned char ch;

ISR(USART0_RX_vect){//0이 1번에게
	ch=UDR0;
	UDR0=ch;
	UDR1=ch;
}


ISR(USART1_RX_vect){//1번이 0번에게
	ch=UDR1;
	UDR0=ch;
	UDR1=ch;
}



int main(void)
{
	UCSR0A = 0x00;
	UCSR0B = 0b10011000; // RXCIE0=1, TXEN0=1, RXEN0=1
	UCSR0C = 0b10000110; // 비동기통신, 패리티없음,
	// 데이터비트: 8비트, 정지비트: 1비트
	UCSR1A = 0x00;
	UCSR1B = 0b10011000;
	UCSR1C = 0b10000110;
	

	UBRR0H = 0;
	UBRR0L = 103; 
	UBRR1H = 0;
	UBRR1L = 103; 
	SREG = 0x80;
	
	while(1){
	}
}
