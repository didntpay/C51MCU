#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char

 void delay(uchar ms)	
{
	uchar x,y;
	for(x=0;x<ms;x++)
		for(y=0;y<210;y++);
}