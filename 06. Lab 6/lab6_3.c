#include <at89c5131.h>

sbit LED1 = P0^7;
sbit LED2 = P3^7;
int count = 0;

void timer0_isr() interrupt 1{
   LED1=~LED1;
   //Reload values for TH0 and TL0. Start timer 0.
   if(count<20){
      TH0=0xEF;
      TL0=0xB9;
   }else if(count<50){
      TH0=0xF1;
      TL0=0x88;
   }else if(count<90){
      TH0=0xF2;
      TL0=0xFB;
   }else if(count<110){
      TH0=0xF3;
      TL0=0xCB;
   }else if(count<150){
      TH0=0xF5;
      TL0=0x26;
   }else if(count<180){
      TH0=0xF6;
      TL0=0x3C;
   }else if(count<220){
      TH0=0xF7;
      TL0=0x52;
   }else if(count<240){
      TH0=0xF7;
      TL0=0xDD;
   }else{
      count=0;
      TH0=0xEF;
      TL0=0xB9;
   }
}


void timer1_isr() interrupt 3{
   LED2=~LED2;
   count++;
   TH1=0x3C;
   TL1=0xB0;
   //Reload values for TH1 and TL1. Start timer 1.
}



void main(void)
{
	TMOD = 0x11;
	TH1 = 0x3C;
	TL1 = 0xB0;
	TH0 = 0xEF;
	TL0 = 0xB9;
	ET0 = 1;
	ET1 = 1;
	EA = 1;
	TR0 = 1;
	TR1 = 1;
		while(1);
}