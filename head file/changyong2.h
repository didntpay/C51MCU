#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char

 void delay(uchar ms)	
{
	uchar x,y;
	for(x=0;x<ms;x++)
		for(y=0;y<210;y++);
}
void splitnum(uint num)//num has to be less than 65535(buf require)
{
	uint num1,tt;
	tt=0;
	while(num>0)
	{
		num1=num%10;
		combine(num1,tt);
		tt++;
		num=num/10;
	}
}
 void combine(uint x,uint num1)//have to define buf
{
	buf[num1]=x;		
}