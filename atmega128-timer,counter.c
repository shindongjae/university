#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int count=0;

volatile char str[1][16]={{"Stop Watch"}};
volatile char str2[1][16]={{""}};


int hour=0, minute=0, second=0, st=0;


void cmd(int command){//lcd에 명령 하는 함수
	PORTE=command;
	PORTB=0x04;
	_delay_ms(1);
	PORTB=0x00;
}

void data(char str){//lcd에 data를 보내서 출력하는 함수
	PORTE=str;
	PORTB=0x05;
	_delay_ms(1);
	PORTB=0x01;
}

void numlcd(unsigned char num){//숫자를 lcd상에 출력하는 함수
	char str[]="00";
	str[0]='0'+num/10;
	str[1]='0'+num%10;
	data(str[0]);
	data(str[1]);
}

void display1(volatile char *str){ //전체 출력하는 함수
	cmd(0x80);
	int i=0;
	while(str[i]!='\0')
	{
		data(str[i++]);
	}
	cmd(0xc0);
	numlcd(hour);
	data(':');
	numlcd(minute);
	data(':');
	numlcd(second);
}

ISR(INT0_vect){//시작
	st=1;
}
ISR(INT1_vect){//일시정지
	st=0;
}
ISR(INT2_vect){//초기화
	minute=0;
	hour=0;
	second=0;
	st=0;
}


ISR(TIMER2_OVF_vect){//st가 1인 경우에만 숫자가 올라감.
	if(st==1)
	count++;

	if(count==61){ //오버플로우 인터럽트가 61번 발생하면 1초 경과한것이므로 led를 한칸 옆에 켜지게한다.
		second++;
		if(second==60)
		{
			second=0;
			minute++;
		}
		if(minute==60)
		{
			minute=0;
			hour++;
		}
		count=0;
	}
	
}

int main(){
	DDRB=0xff;
	DDRE=0xff;
	DDRD=0x00;
	PORTD=0xff;
	
	TCCR2=0b00000101; //일반모드+분주비 1024
	TIMSK=0b01000000;//오버플로우 인터럽트 허가
	TCNT2=0;//타이머 카운터 초기화
	SREG=0x80;//인터럽트 허가
	
	EICRA = 0b00101010; //인터럽트트리거방식설정
	EIMSK = 0b00000111; //인터럽트허용설정
	
	cmd(0x38); //set 8 bit 2line 5*7 dots
	cmd(0x01); //display clear
	cmd(0x80);//set ddram address or cursor position on display
	cmd(0x0c);//display on cursor off
	cmd(0x06);//entry mode

	
	while(1){
		display1(str[0]);
	}
}
