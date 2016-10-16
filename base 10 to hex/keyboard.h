uint keyscan()		
{
	uint keyh,keyl,keyvalue1,k;
	
	P3=0xff;
	keyh=0;
	keyl=0;
	keyvalue1=0;
	while(keyl==0)
	{
		P3=0x0f;
		if(P3!=0x0f)
		{
			delay(5);
			if(P3!=0x0f)
			{
				switch(P3)
				{
					case(0x0e): keyh=1;break;
					case(0x0d): keyh=2;break;
					case(0x0b): keyh=3;break;
					case(0x07): keyh=4;break;
				}
			}
		}
		P3=0xf0;
		if(P3!=0xf0)
		{
			delay(5);
			if(P3!=0xf0)
			{
				switch(P3)
				{
					case(0xe0): keyl=1;break;
					case(0xd0): keyl=2;break;
					case(0xb0): keyl=3;break;
					case(0x70): keyl=4;break;
				}
				while(P3!=0xf0);
				
			}
		}
		keyvalue1=keyl+(keyh-1)*4;
	}
	//keyvalue1=keyl+(keyh-1)*4;
	k=keyvalue1-1;
	if(k<10)
	{
		write_data(k+0x30);
	}
	
	return k;
	
	
}
