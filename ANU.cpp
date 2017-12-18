#include<LPC21xx.h>

 unsigned long intshiftleft(unsigned long int,unsigned char);
 unsigned long intsbox_(unsigned long int);
 unsigned long intshiftright(unsigned long int,unsignedint );
 unsigned long int player(unsigned long longint);
 void tx(unsigned int t); //function that transmit char (user see on uart terminal)
 char rx(void); // function that receive anything


unsigned char sbox[16] = {2,9,7,0xE,1,0xC,0xA,0,4,3,8,0xD,0xF,0x6,0x5,0xB};
unsigned char p[32] = {20,16,28,24,17,21,25,29,22,18,30,26,19,23,27,31,11,15,3,7,14,10,6,2,9,13,1,5,12,8,4,0};



int main()
 {
	 unsigned int m;
 // all variable defined here___________________________________________________________
	unsigned long int msb_32bit,lsb_32bit,s_box1,s_box2,bn,bn1,sub_key[1],c,r,i1,j1,i,j[2]; 
	unsigned long longinttemp,k[2];
	//unsigned char r,i1,j1,i,j[2];
 //_____________________________________________________________________________________________	
// all pinsel and required register configuration_____________________________________________	
	PINSEL0 = 0x05; // configuration for tx and rx in pinsel
  U0LCR = 0x83; // configure the line control register
  U0DLL = 0x61;
  U0DLM = 0x00;// config baud rate 9600 (calculate in bps ---> convert into hex --> then load into DLL & DLM)
  U0LCR = 0x03; // lock baud rate by resetting baud rate bit in U0LCR register
//__________________________________________________________________________________________
tx('P');
tx('-');		
 for (j1=0;j1<2;j1++)
{
	k[j1]=0;
	{
		for (i1=0;i1<=7;i1++)
		{
			m = rx();
			tx(m);
				if (m>0x2f && m<0x40)
				{
					temp = m-0x30;
				}
			 if(m>=97 && m<=102)
				{
				 temp = m-87;
				}
				k[j1] += (temp & 0xf) << ((7-i1)*4); 
		}	
	}
}
msb_32bit = k[0];
lsb_32bit = k[1];

		tx(' ');
		tx('K');
		tx('-'); 
		for (j1=0; j1<2; j1++)
		{
			k[j1] =0;
				for (i1=0;i1<=15;i1++)
				{
					m = rx();
					tx(m);
			
					if (m>0x2F && m<0x40)
					{
						temp = m-0x30;
					}	
					if(m>=97 && m<=102)
					{
						temp = m-87;
					}
					k[j1] += (temp & 0xf) << ((15-i1)*4); 
				}	
		}
	
 //KEY2=k[0]; 
 //KEY1 = k[1];  
for(r=0;r<25;r++)
	{	
//_____________________________________
	c = shiftleft(msb_32bit,3);
  s_box1 = sbox_(c);
  c = shiftright(msb_32bit,8);
  s_box2 = sbox_(c);
	bn = player(msb_32bit);
//___________________________________	
	sub_key[0] = (k[1]&0XFFFFFFFF);	
		temp=k[1];
	k[1]= (temp<<13)|(k[0]>>(64-13));
	k[0]= (k[0]<<13)|(temp>>(64-13));
	//k[1] = K_UP1;
	//k[0] = K_UP2;

		for(i=0; i<2; i++)
		{
			j[i]=sbox[(k[1]>>(i*4))&0XF];
		}
		k[1] &= (0Xffffffffffffff00);  

		for(i=0;i<2;i++)
			{
				k[1] |= ((j[i]&0xf)<<(i*4));
			}  
				temp = (((k[1]&0XF800000000000000)>>(64-5))^(0x1f&r));
				k[1] &= 0X07FFFFFFFFFFFFFF;
				k[1] |= temp<<(64-5);
		temp =  (s_box1^s_box2^lsb_32bit^sub_key[0]);
//_____________________________________________________________			
		//	bn1=0;
      bn1 =  player(temp);
//______________________________________________________________
	 msb_32bit = bn1;
   lsb_32bit = bn;
}   
	tx(' ');
	tx('c');
	tx('-');

	for (i1=0; i1<=7; i1++)
	{
		temp=(msb_32bit>>(7-i1)*4)&0xf;	
			if(temp<10)
			tx(0x30+temp);
			else
			tx(87+temp);
	}
	for (i1=0; i1<=7; i1++)
	{
		temp=(lsb_32bit>>(7-i1)*4)&0xf;	
		if(temp<10)
			tx(0x30+temp);
		else
			tx(87+temp);
	}
}

 unsigned long intshiftleft(unsigned long int msb_32bit,unsigned char i)
{
	unsigned long inta,b,tempr;
	a = msb_32bit<<i;
	tempr = msb_32bit>>(32-i);
	b = a|tempr;
	return(b);
}

 unsigned long intsbox_(unsigned long int c)
{

	unsigned long int a=0,i,j[33],b=0;
	for (i=0;i<32;i=i+4)     
	{
	 j[b]= sbox[((c>>(28-i)&0xf))];
	 a |= ((((j[b])&0xf)<<(28-i)));
	 b++;
	}
	return(a);
}

unsigned long intshiftright(unsigned long int msb_32bit,unsigned inti)
{
	unsigned long inta,b,tempr;
	a = msb_32bit>>i;
	tempr = msb_32bit<<(32-i);
	b = a|tempr;
	return(b);
}

 unsigned long int player(unsigned long longinttempr)
 {
	unsigned inti, b=0;
	
    for (i=0; i<32;i++)
     {
		 b |= ((tempr>>i)&0x1)<<p[i];
		 }
		 return(b);
 }

void tx(unsigned int t)
{
 while(!(U0LSR & 0x20)); // check the transmitter data available bit in U0LSR
 U0THR = t; // if data is available it will transmit by jumping from above line (while !)
}

 char rx(void)
{
	unsigned int m;
	while(!(U0LSR & 0x01)); // check the transmitter data available bit in U0LSR
  m = U0RBR; // if data is available it will transmit by jumping from above line (while !)
  return(m);
}





