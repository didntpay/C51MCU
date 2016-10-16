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
void displaypic(unsigned char code *adder);
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
void displaypic(unsigned char code *adder)
{
	uint m,n;	
	for(m=0;m<32;m++)
	{
		writecmd(0x80+m);
		writecmd(0x80);
		for(n=0;n<16;n++)
		{
			
			write_data(*adder);
			adder++;
		}
	}
	lcdbusy();	
	for(m=0;m<32;m++)
	{
		writecmd(0x80+m);
		writecmd(0x88);
		for(n=0;n<16;n++)
		{
			write_data(*adder);
			adder++;
		}
	}
}
void lcd_drawpoint(uchar x,uchar y)//x is row y is comlumn. It allows users to drawpoint at 
{//where ever they want.
	uint point=0,read=0;
	uchar x_adr,y_adr,h_bit,l_bit;
	y_adr=0x80+y%32;
	if(y>31)
   		x_adr=0x88+x/16;
	else
		x_adr=0x80+x/16;
	point=0x800>>(x%16);
	sendcom(0x34);
	sendcom(0x34);
	sendcom(y_adr);
	sendcom(x_adr);
	readdata();
	read=readdata();
	read<<=8; 
	read|=readdata();
	point=point|read;
	h_bit=point>>8;
	l_bit=point; 
	sendcom(y_adr);
	sendcom(x_adr);
	senddata(h_bit);
	senddata(l_bit);
	sendcom(0x36);
	sendcom(0x30);
}