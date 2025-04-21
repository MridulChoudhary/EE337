#include <at89c5131.h>
#include "spi.h"
#include "serial.h"


sbit SS = P1^4;
unsigned char ch = 0;
int int1=0, int2=0;
int int1_copy=0, int2_copy=0;
int int1_copy2=0, int2_copy2=0;
int digits = 0;
int result = 0;

void msdelay(unsigned int time)
{
	int i,j;
	for(i = 0; i < time; i++)
	{
		for(j = 0; j < 382; j++);
	}
}

void main(void) {
	
	spi_master_init();          
	uart_init();

	transmit_string("\r\nEnter Input-1: ");
	while(1){
		ch = receive_char();
		if (ch == 46) break;
		int1 = int1 * 10;
		int1 += (ch - 48);
	}

	transmit_string("\r\nEnter Input-2: ");
	while(1){
		ch = receive_char();
		if (ch == 46) break;
		int2 = int2 * 10;
		int2 += (ch - 48);
	}

		SS = 0;                  
		spi_trx(int1);        
		SS = 1;

		msdelay(500);

		SS = 0;                  
		spi_trx(int2);         
		SS = 1;

		msdelay(500);
	
		result = spi_trx(0);
        if (result == 1) {
        	transmit_string("\r\nPRIME\r\n");
        } else if(result == 2){
        	transmit_string("\r\nNOT PRIME\r\n");
		}
		
	while(1);
}