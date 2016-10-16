void ack();
void start();
void nack();
void stop();
void writedata(uchar dat);
uchar read();



void start()
{
   scl=1;
   _nop_();
   sda=1;
   _nop_();
   sda=0;
   _nop_();
   
}
void stop()
{
   scl=1;
   _nop_();
   sda=0;
   _nop_();
   sda=1;
   _nop_();
}
void ack()
{
	sda=0;
	_nop_();
	scl=1;
	_nop_();
	scl=0;
	_nop_();
}
void nack()
{
	sda=1;
	_nop_();
	scl=1;
	_nop_();
	scl=0;
}
void writedata(uchar dat)
{
	uint ww;
	
	for(ww=0;ww<8;ww++)
	{
		scl=0;
		_nop_();
		if((dat&0x80)==0x80)
		{
			sda=1;
		}
		else
		{
			sda=0;
		}
		scl=1;
		_nop_();
		dat=dat<<1;
	}
	scl=0;
}
uchar read()
{
	uchar temp;
	uint ww;
	sda=1;
	for(ww=0;ww<25;ww++)
	{
		scl=0;
		_nop_();
		scl=1;
		if(sda==1)
		{
			temp=temp|0x01;
			
		}
		else
		{
			temp=temp&0xfe;
			
		}
		temp=temp<<1;
	}
	scl=0;	
	return temp;
}