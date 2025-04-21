#include "spi.h"
#include <at89c5131.h>
#include "lcd.h"
#include <stdio.h>

sbit SS = P1^4;

extern void mac_operation(void);

//data unsigned int num1 = (unsigned int )0x30;
//data unsigned int num2 = (unsigned int )0x31;
//data unsigned int sum = (unsigned int )0x32;

xdata unsigned int num1, num2, sum, a1, a2;
//int sum;
int result;
int digits = 0;
char adc_ip_data_ascii[6] = {'0','0','0','0','0','\0'};
int i=0;
int p=1;
char buffer[20];
int sum2 = 0;

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

/*	digits = spi_trx(0x00);
	p = 1;
	for(i=0; i<digits; i++){
		num1 += (p * (spi_trx(0x00)));
		p *= 10;
	}
*/
	num1 = spi_trx(0x00);
//	int_to_string(num1, adc_ip_data_ascii);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
//	lcd_write_string(adc_ip_data_ascii);


	
/*	digits = spi_trx(0x00);
	p = 1;
	for(i=0; i<digits; i++){
		num2 += (p * (spi_trx(0x00)));
		p *= 10;
	}
*/
	num2 = spi_trx(0x00);

	a1 = spi_trx(0x00);
	a2 = spi_trx(0x00);

	lcd_write_string('*');
	sprintf(buffer, "%d*%d+%d*%d", num1, a1, num2, a2);  // Convert integer to string
	lcd_write_string(buffer);
//	lcd_write_char('+');
//	int_to_string(num2, adc_ip_data_ascii);
//	lcd_write_string(adc_ip_data_ascii);
//	lcd_write_string('*');
//	int_to_string(a2, adc_ip_data_ascii);
//	lcd_write_string(adc_ip_data_ascii);	
	
//  sum = num1 + num2;
//   add_numbers();           // Call assembly function to compute sum
  mac_operation();
//	sum2 = num1 * a1 + num2 * a2;
	result = is_prime(sum);
	lcd_cmd(0xC0);
	
	sprintf(buffer, "Sum is %d", sum);  // Convert integer to string	
	lcd_write_string(buffer);

	spi_trx(result);
	
	while (1);  // Keep display on

}