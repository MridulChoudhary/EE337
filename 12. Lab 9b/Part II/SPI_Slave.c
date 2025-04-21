#include "spi.h"
#include <at89c5131.h>
#include "lcd.h"

sbit SS = P1^4;

int num1, num2, sum, result;
int digits = 0;
char adc_ip_data_ascii[6] = {'0','0','0','0','0','\0'};
int i=0;
int p=1;
unsigned int is_prime(unsigned int n) {
    unsigned int i;
    if (n < 2) return 2;
    for (i = 2; i * i <= n; ++i) {
        if (n % i == 0) return 2;
    }
    return 1;
}


void main(void) {	

	spi_slave_init();
    lcd_init();
	num1=0;
	num2=0;
	sum=0;
	
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_write_string("Slave Initialize");

	num1 = spi_trx(0x00);
	int_to_string(num1, adc_ip_data_ascii);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_write_string(adc_ip_data_ascii);
	
	num2 = spi_trx(0x00);
	lcd_write_char('+');
	int_to_string(num2, adc_ip_data_ascii);
	lcd_write_string(adc_ip_data_ascii);
	
	sum = num1 + num2;

	result = is_prime(sum);

	lcd_cmd(0xC0);
	lcd_write_string("Sum is ");
	int_to_string(sum, adc_ip_data_ascii);
	lcd_write_string(adc_ip_data_ascii);

	spi_trx(result);
	
	while (1);

}