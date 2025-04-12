#include <at89c5131.h>

sbit LED1 = P1^4;
sbit LED2 = P1^5;
sbit LED3 = P1^6;
sbit LED4 = P1^7;
sbit sw1 = P1^0;
sbit sw2 = P1^1;
sbit sw3 = P1^2;
sbit sw4 = P1^3;

void msdelay(unsigned int time){
	int i,j;
	for(i=0;i<time;i++){
		for(j=0;j<382;j++);
	}
}


void main(){
	unsigned int debounce = 2000;
	unsigned int allOn = 1000;
	
	unsigned int sw1Prev = 0, sw2Prev = 0, sw3Prev = 0, sw4Prev = 0;
	while(1){
		
		sw1 = 1;
		sw2 = 1;
		sw3 = 1;
		sw4 = 1;
		
		// S1 OFF to ON
		if(sw1 && !sw1Prev){
			msdelay(debounce);
			if(sw1 == 1){
				LED1 = 1;
				LED2 = 0;
				LED3 = 0;
				LED4 = 0;
				sw1Prev = 1;
			}
		}
		// S1 ON to OFF
		else if(!sw1 && sw1Prev){
			msdelay(debounce);
			if(sw1 == 0){
				LED1 = 1;
				LED2 = 1;
				LED3 = 1;
				LED4 = 1;
				msdelay(allOn);
				LED1 = 0;
				LED2 = 0;
				LED3 = 0;
				LED4 = 0;
				sw1Prev = 0;
			}
		}
		// S2 OFF to ON
		if(sw2 && !sw2Prev){
			msdelay(debounce);
			if(sw2 == 1){
				LED1 = 0;
				LED2 = 1;
				LED3 = 0;
				LED4 = 0;
				sw2Prev = 1;
			}
		}
		// S2 ON to OFF
		else if(!sw2 && sw2Prev){
			msdelay(debounce);
			if(sw2 == 0){
				LED1 = 1;
				LED2 = 1;
				LED3 = 1;
				LED4 = 1;
				msdelay(allOn);
				LED1 = 0;
				LED2 = 0;
				LED3 = 0;
				LED4 = 0;
				sw2Prev = 0;
			}
		}
		// S3 OFF to ON
		if(sw3 && !sw3Prev){
			msdelay(debounce);
			if(sw3 == 1){
				LED1 = 0;
				LED2 = 0;
				LED3 = 3;
				LED4 = 0;
				sw3Prev = 1;
			}
		}
		// S3 ON to OFF
		else if(!sw3 && sw3Prev){
			msdelay(debounce);
			if(sw3 == 0){
				LED1 = 1;
				LED2 = 1;
				LED3 = 1;
				LED4 = 1;
				msdelay(allOn);
				LED1 = 0;
				LED2 = 0;
				LED3 = 0;
				LED4 = 0;
				sw3Prev = 0;
			}
		}
		// S4 OFF to ON
		if(sw4 && !sw4Prev){
			msdelay(debounce);
			if(sw4 == 1){
				LED1 = 0;
				LED2 = 0;
				LED3 = 0;
				LED4 = 1;
				sw4Prev = 1;
			}
		}
		// S4 ON to OFF
		else if(!sw4 && sw4Prev){
			msdelay(debounce);
			if(sw4 == 0){
				LED1 = 1;
				LED2 = 1;
				LED3 = 1;
				LED4 = 1;
				msdelay(allOn);
				LED1 = 0;
				LED2 = 0;
				LED3 = 0;
				LED4 = 0;
				sw4Prev = 0;
			}
		}
	}
}