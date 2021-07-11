#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

volatile  char str[10][40]={
	{"He'd forgotten all about the people in c"},
	{"locks until he passed a group of them ne"},
	{"xt to the baker's. He eyed them angrily "},
	{"as he passed. He didn't know why, but th"},
	{"He'd forgotten all about the people in c"},
	{"locks until he passed a group of them ne"},
	{"xt to the baker's. He eyed them angrily "},
	{"as he passed. He didn't know why, but th"},
	{"He'd forgotten all about the people in c"},
	{"locks until he passed a group of them ne"}
};

int x=0,y=0;
void cmd(int command){
	PORTE=command;
	PORTB=0x04;
	_delay_ms(1);
	PORTB=0x00;
}

void data(char str){
	PORTE=str;
	PORTB=0x05;
	_delay_ms(1);
	PORTB=0x01;
}

void display1(int x,int y){
	//y줄 x번째부터 y+1번째줄 x+15번째까지 출력
	cmd(0x01);
	cmd(0x80);
	
	for(int j=0;j<16;j++)
		data(str[x][y+j]);
		
	cmd(0xc0);
	for(int j=0;j<16;j++)
		data(str[x+1][y+j]);
}

int main(){
	DDRB=0xff;
	DDRE=0xff;
	DDRD=0x00;
	PORTD=0x0f; //풀업저항 설정.
	
	
	
	cmd(0x38); //set 8 bit 2line 5*7 dots
	cmd(0x01); //display clear
	cmd(0x80);//set ddram address or cursor position on display
	cmd(0x0c);//display on cursor off
	cmd(0x06);//entry mode

	display1(x,y); //0,0일 때 출력
	while(1){
		if(PIND==0b00001110)//위
		{
			if(x>0) //이동 가능하다면 한줄 위쪽으로
			x=x-1;
			display1(x,y);
			_delay_ms(250);	
		}
		if(PIND==0b00001101)//왼쪽
		{
			if(y>0) //이동 가능하다면 한줄 왼쪽으로
			y=y-1;
			display1(x,y);
			_delay_ms(250);
		}
		if(PIND==0b00001011)//오른쪽
		{
			if(y<24) //이동 가능하다면 한줄 오른쪽으로
			y=y+1;
			display1(x,y);
			_delay_ms(250);
		}
		if(PIND==0b00000111)//아래
		{
			if(x<8) //이동 가능하다면 한줄 아래쪽으로
			x=x+1;
			display1(x,y);
			_delay_ms(250);
		}
	}
}

