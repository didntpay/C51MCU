#define uint unsigned int
#define uchar unsigned char

sbit rs=P2^4;
sbit rw=P2^5;
sbit lcde=P2^6;
sbit PSB=P2^1;
sbit RES=P2^3;
void delay(uint z)
{
	uint x,y;
	for(x=200;x>0;x--)
		for(y=z;y>0;y--);
}
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
	writecmd(0x30);
	writecmd(0x14);
	writecmd(0x80);
	writecmd(0x0c);
	writecmd(0x01);
	delay(100);
}
void initpic()//显示图片初始化
{
	delay(20);
	PSB=1;
	delay(1);
	RES=0;
	delay(1);
	RES=1;
	writecmd(0x36);
	delay(1);
	writecmd(0x3e);
	delay(1);
	writecmd(0x80);
	delay(1);
	writecmd(0x01);
	delay(1);
}
void cleargdram()//清除gdram
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