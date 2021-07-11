#define F_CPU 16000000
#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdio.h>

int ADC_Output;

void onechar(char c){
	while( (UCSR0A & (1<<UDRE0)) == 0 );//버퍼 쓸 준비 되지 않았다면 대기
	UDR0 = c;//c출력
}

void strprint(char *str){ //문자열 출력 함수
	while(*str!='\0'){
		onechar(*str);
		str++;
	}
}

void ADC_SingleConversion_Init(unsigned char port) {
	ADMUX = port; //ADMUX값을설정
}

int ADC_SingleConversion_read() {
	int output;
	ADCSRA |= (1<<ADSC) | (1<<ADEN) ; //Start single conversion
	while(ADCSRA & (1<<ADSC)); //wait Conversion to complete
	output = ADCL + (ADCH << 8);
	ADCSRA &= ~(1<<ADEN); //disable ADC
	return output;
}

void printint(int n){
	onechar((n/1000)+48);
	onechar((n/100)%10+48);
	onechar((n/10)%10+48);
	onechar(n%10+48);
}


int main(){
	DDRB=0xff;
	DDRE=0xff;
	DDRF=0b11111000;
	
	EICRA = 0xff;
	EIMSK = 0x0f;
	SREG = 0x80;

	UCSR0A = 0x00;
	UCSR0B = 0b10011000; // RXCIE0=1, TXEN0=1, RXEN0=1
	UCSR0C = 0b10000110; // 비동기통신, 패리티없음,
	// 데이터비트: 8비트, 정지비트: 1비트
	UBRR0H = 0;
	UBRR0L = 103;


	
	while(1){
		
		ADC_Output= ADC_SingleConversion_read(); // 변환된digital값읽기
		
		strprint("X-axis:");
		ADC_SingleConversion_Init(0x00);
		printint(ADC_SingleConversion_read());
		_delay_ms(10);
		
		strprint(" Y-axis:");
		ADC_SingleConversion_Init(0x01);
		printint(ADC_SingleConversion_read());
		_delay_ms(10);
		
		strprint(" Z-axis:");
		ADC_SingleConversion_Init(0x02);
		printint(ADC_SingleConversion_read());
		_delay_ms(500);
		UDR0=13;

		_delay_ms(10);
	}
}
