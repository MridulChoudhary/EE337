#include "spi.h"
#include "lcd.h"
#include <at89c5131.h>
#include "mcp3008.h"

sbit SS = P3^0;

unsigned int is_prime(unsigned int n) {
    unsigned int i;
    if (n < 2) return 2;
    for (i = 2; i * i <= n; ++i) {
        if (n % i == 0) return 2;
    }
    return 1;
}

void main(void) {
    unsigned int num1, num2, sum, result;
		char adc_ip_data_ascii[6]={0,0,0,0,0,'\0'};		
    spi_slave_init();     
    lcd_init();
		lcd_write_string("Slave Initializing");
		
		lcd_cmd(0x01);
    num1 = spi_trx(0x00);
		int_to_string(num1, adc_ip_data_ascii);
		lcd_write_string(adc_ip_data_ascii);
		
		num2 = spi_trx(0x00);
		lcd_write_char('+');
		int_to_string(num2, adc_ip_data_ascii);
		lcd_write_string(adc_ip_data_ascii);
    // Compute sum and check if prime
    sum = num1 + num2;
    result = is_prime(sum);
		lcd_cmd(0xC0);
    // Display sum
    lcd_write_string("Sum is ");
		int_to_string(sum, adc_ip_data_ascii);
		lcd_write_string(adc_ip_data_ascii);
    // Send result back to master
    spi_trx(result);

    while (1);  // Keep display on
}
