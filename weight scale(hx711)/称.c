/*there is a 128 gain for this chip, this program is using 64 gain 
chip# hx711.*/
#include<changyong2.h>
#include<lcd12864.h>
#include<intrins.h>
sbit scl=P1^4;
sbit sda=P1^3;
uchar flag;
uint buf[8]=(0);
uchar temp;
uint read();

void splitnum(uint num);
void combine(uint x,uint num1);
void timer1init();
void lcddis(uchar add,uint count);
void main()
{
	unsigned long zero,dat;
	uint temp;
	init();
	timer1init(); 
	for(temp=5;temp>0;temp--)
	{
		zero=zero+read();// take the weight of items above the sensor.	
	}
	zero=zero/5;// take average.	  
		
	TR1=1;//timer1 activate
	while(1)
	{
		
		lcddis(0x80,4);
		if(flag==2)
		{
			flag=0;
			dat=read();
			dat=dat-zero;
			splitnum(dat);
			lcddis(0x80,4);
			dat=0;
			
		}			
	}		  	
}
uint read()
{
	uint ww;
	unsigned long count;//variable for data.
	sda=1;
	_nop_();
	scl=0;
	_nop_();//1/4 of ns delay.
	count=0;
	while(sda);//if sda is busy then wait!
	for(ww=0;ww<24;ww++)
	{
		count=count<<1;//transfering data from H to L.
		scl=1;
		_nop_();
		scl=0;
		if(sda)
		{
			count++;
		}
		
			
	}
	scl=1;
	_nop_();
	scl=0;
	
	count=~(count-1);//convert 2's complement into binary coded decimal.
	count=count>>8;//ignore
	return count;
}

void splitnum(uint num)//take a number with multiple digits sperate it and put it into buf.  
{
	uint num1,tt;	
	uint i;
	tt=0;
	for(i=0;i<8;i++)
	{
		buf[i]=0;  			
	}
	while(num>0)
	{
		num1=num%10;
		combine(num1,tt);
		tt++;
		num=num/10;
	}

	
}
 void combine(uint x,uint num1)
{
	buf[num1]=x;		
}
void timer1init()
{
	TMOD|=0x10;
	TH1=(65536-50000)/256;	      //给定初值，这里使用定时器50ms溢出
	TL1=(65536-50000)%256;
	EA=1;
	ET1=1;	
}
void lcddis(uchar add,uint count)
{
	writecmd(add);
	for(count;count>0;count--)
	{
		write_data(buf[count-1]+0x30);
	}
}

void time1_hx() interrupt 3  
{
	TF1=0;
	TH1=(65536-50000)/256;	      //给定初值，这里使用定时器50ms溢出
	TL1=(65536-50000)%256;
	flag++;
}