#include<reg52.h>
#include<lcd12864.h>
#include<keyboard.h>
#define uint unsigned int
#define uchar unsigned char
uint buf[9]={0};
uchar code table[16]=("0123456789ABCDEF");
uint turntohex(uint nmb1);
void hex();
void combine(uint x,uint num1);

void main()
{
	
	
	init();
	hex();
	
}
uint turntohex(uint nmb1)
{
	uint re,temp,tt;
	re=nmb1%16;
	temp=nmb1/16;
	combine(re,tt);
	tt++;
	if(temp<16)
	{
		combine(temp,tt);
		tt++;
	}
	while(temp>15)
	{
		
		re=temp%16;
		combine(re,tt);
		tt++;
		temp=temp/16;
		if(temp<16)
		{
			combine(temp,tt);
			tt++;
		}
			
	}
	//tt++;
	return tt;

}
 void combine(uint x,uint num1)
{
	buf[num1]=x;		
}
void hex()
{
	uint ch,w,loop;
	
	long int h;
	
		ch=keyscan();
		h=ch;
		//h=100;
		//ch=10;
		while(ch<10)
		{
			ch=keyscan();
			if(ch!=10)
			{
				h=h*10+ch;
			}
		}
		if(ch==10)
		{
			w=turntohex(h);
			write_data('=');
			write_data('0');
			write_data('x');
			loop=w;
			for(;loop!=0;loop--)
			{
				write_data(table[buf[loop-1]]);
			}
		}
		ch=keyscan();
		while(ch!=11)
		{
			ch=keyscan();
		}
		writecmd(0x01);
		
		
	  
	
}