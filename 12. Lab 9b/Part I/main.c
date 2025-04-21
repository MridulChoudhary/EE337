/**********************************************************
EE337: ADC IC MCP3008 interfacing with pt-51
(1) Complete spi_init() function from spi.h 

***********************************************************/

#include <at89c5131.h>
#include "lcd.h"																				//Driver for interfacing lcd 
#include "mcp3008.h"																		//Driver for interfacing ADC ic MCP3008


char adc_ip_data_ascii[6]={0,0,0,0,0,'\0'};							//string array for saving ascii of input sample
code unsigned char display_msg1[]="Volt.: ";						//Display msg on 1st line of lcd
code unsigned char display_msg2[]=" mV";								//Display msg on 2nd line of lcd
code unsigned char display_msg3[] = "Temp.: ";
code unsigned char display_msg4[] = " oC";

unsigned char whole[6];      

void main(void)
{
    float adc_data = 0, y1;
    unsigned int temperature_w;

    spi_init();    
    adc_init();
    lcd_init();

    while (1)
    {
        unsigned int x, y; 
        x = adc(4);  //Read analog value from 0th channel of ADC Ic MCP3008
        adc_data = (x * 3.2258);  //Converting received 10 bits value to milli volt (3.3*1000*i/p /1023)
			/*
		    Display "Volt: " on first line of lcd
		    Print analog sampled input on lcd using int_to_string function and 
		    Display "XXXXX mV" on second line of LCD
		
		*/
        lcd_cmd(0x80);   
        lcd_write_string(display_msg1);
        int_to_string(adc_data, adc_ip_data_ascii); 
        lcd_write_string(adc_ip_data_ascii);
        lcd_write_string(display_msg2);

        lcd_cmd(0xC0);   
        lcd_write_string(display_msg3);

			
				y = adc(3);
				y1 = (y * 3.2258);
				
        temperature_w = y1 / 10;  

        int_to_string(temperature_w, whole);  
        lcd_write_string(whole + 2);          
       

        lcd_write_string(display_msg4);       
    }
}