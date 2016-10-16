#define uint unsigned int
#define uchar unsigned char
#define ORI_add 0x80
#define	LCD_sta 0x0c//cursor on.
#define LCD_clear 0x01 // only for text.
#define NOR_functionset 0x30//used when displying text
#define EXTEND_functionset 0x38
#define GRA_on 0x36//EXTEND_ functionset required \

sbit rs=P2^4;
sbit rw=P2^5;
sbit lcde=P2^6;
sbit PSB=P2^1;
sbit RES=P2^3;

void lcdbusy()
{
	rs=0;
	rw=1;
	P0=0xff;
	lcde=1;
	while((P0&0x80)==0x80);
	lcde=0;
}
void writecmd(uchar com)
{
	lcdbusy();
	rs=0;
	rw=0;
	P0=com;
	delay(1);
	lcde=1;
	delay(1);
	lcde=0;
}
void write_data(uchar dat)
{
	lcdbusy();
	rs=1;
	rw=0;
	P0=dat;
	delay(1);
	lcde=1;
	delay(1);
	lcde=0;
}
void init()
{
	
	delay(40);
	PSB=1;
	delay(1);
	RES=0;
	delay(1);
	RES=1;
	writecmd(NOR_functionset);
	writecmd(0x14);
	writecmd(ORI_add);
	writecmd(LCD_sta);
	writecmd(LCD_clear);
	delay(100);
}
void initpic()//graphic init
{
	delay(20);
	PSB=1;
	delay(1);
	RES=0;
	delay(1);
	RES=1;
	writecmd(GRA_on);
	delay(1);
	writecmd(ORI_add);
	delay(1);
	writecmd(0x01);//stand by mode
	delay(1);
}
void cleargdram()// clear gdram
{
	uchar i;
	uint j,k;
	i=0x80;
	for(j=0;j<32;j++)
	{
		writecmd(0x80+j);
		writecmd(0x80);
		for(k=0;k<32;k++)
		{
			write_data(0x00);
		
		}
	}
	
	
}