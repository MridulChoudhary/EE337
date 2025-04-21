#include "spi.h"
#include "lcd.h"
#include <at89c5131.h>

sbit SS = P3^0;

void main(void) {
    unsigned int p1 = 41;
    unsigned int p2 = 43;
    unsigned int result = 0;
		char adc_ip_data_ascii[6]={0,0,0,0,0,'\0'};
		
    spi_master_init();          
    lcd_init();
		lcd_write_string("Master Initializing");
    
    // Send primes to slave
		SS = 0;                  // Select slave
		spi_trx(p1);         // Send data
		SS = 1;
		// lcd_write_string("NUM1");
		//lcd_cmd(0x01);
		msdelay(500);
		SS = 0;
    spi_trx(p2);
		SS = 1;
		// lcd_write_string("NUM2");
		// lcd_cmd(0x01);
		msdelay(500);
    // Wait and receive result from slave
		result = spi_trx(0);
		lcd_cmd(0x01);    // 1 = PRIME, 2 = NOT PRIME
    if (result == 1) {
        lcd_write_string("PRIME");
    } else if(result == 2){
        lcd_write_string("NOT PRIME");
		}
		else
		{
			lcd_write_string("ERROR 404");
			//int_to_string(result, adc_ip_data_ascii);
			//lcd_write_string(adc_ip_data_ascii);
		}
    while (1);  // Keep display on
}