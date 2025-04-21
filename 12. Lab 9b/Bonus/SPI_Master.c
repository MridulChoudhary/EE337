#include <at89c5131.h>
#include "spi.h"
#include "serial.h"


sbit SS = P1^4;
unsigned char ch = 0;
int a1, a2;
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
//	int1_copy = int1;
//	int1_copy2 = int1;
	transmit_string("\r\nEnter Input-2: ");
	while(1){
		ch = receive_char();
		if (ch == 46) break;
		int2 = int2 * 10;
		int2 += (ch - 48);
	}
	
	transmit_string("\r\nEnter a1: ");
	while(1){
		ch = receive_char();
		if (ch == 46) break;
		a1 = a1 * 10;
		a1 += (ch - 48);
	}
	
	transmit_string("\r\nEnter a2: ");
	while(1){
		ch = receive_char();
		if (ch == 46) break;
		a2 = a2 * 10;
		a2 += (ch - 48);
	}
	
	//	int2_copy = int2;
//	int2_copy2 = int2;
//	while(int1_copy2 > 0){
//		digits++;
//		int1_copy2 /= 10;
//	}
    // Send primes to slave
//		SS = 0;                  // Select slave
//		spi_trx(digits);         // Send data
//		SS = 1;	
		
//	while(int1_copy > 0){
		SS = 0;                  // Select slave
		spi_trx(int1);         // Send data
		SS = 1;
//		int1_copy /= 10;
//	}

		msdelay(500);
	
//	digits = 0;
//	while(int2_copy2 > 0){
//		digits++;
//		int2_copy2 /= 10;
//	}

//		SS = 0;                  // Select slave
//		spi_trx(digits);         // Send data
//		SS = 1;	

//	while(int2_copy > 0){
		SS = 0;                  // Select slave
		spi_trx(int2);         // Send data
		SS = 1;
//		int2_copy /= 10;
//	}
		msdelay(500);

		SS = 0;                  // Select slave
		spi_trx(a1);         // Send data
		SS = 1;
		msdelay(500);
	
		SS = 0;                  // Select slave
		spi_trx(a2);         // Send data
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