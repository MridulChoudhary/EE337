/**********************************************************
EE337: ADC IC MCP3008 interfacing with pt-51
(1) Complete spi_init() function from spi.h 

***********************************************************/

#include <at89c5131.h>
#include "lcd.h"																				//Driver for interfacing lcd 
#include "mcp3008.h"																		//Driver for interfacing ADC ic MCP3008


char adc_ip_data_ascii[6]={0,0,0,0,0,'\0'};							//string array for saving ascii of input sample
	char temp_ip_data_ascii[6] = {0, 0, 0, 0, 0, '\0'};   


code unsigned char display_msg1[]="Volt.: ";						//Display msg on 1st line of lcd
code unsigned char display_msg2[]=" mV";								//Display msg on 2nd line of lcd

	code unsigned char display_msg3[]="Temp.: ";
	code unsigned char display_msg4[]=" oC";
	
	


void main(void)
{
	int j=0;
	unsigned int adc_data=0;
	
	unsigned int temp_data=0;
	
	
	
	spi_init();																					
	adc_init();
    lcd_init();
	
	
	
	while(1)
	{
	 	unsigned int x;
		
		 
		x = adc(4);																					//Read analog value from 0th channel of ADC Ic MCP3008
		adc_data = (unsigned int) (x*3.2258); 	
		lcd_cmd(0x80);
		lcd_write_string(display_msg1);
		int_to_string(adc_data,adc_ip_data_ascii);
		lcd_write_string(adc_ip_data_ascii);
		lcd_write_string(display_msg2);
		
	 
		/*
		    Display "Volt: " on first line of lcd
		    Print analog sampled input on lcd using int_to_string function and 
		    Display "XXXXX mV" on second line of LCD
		
		*/	
		x = adc(3) ; // reding temperature from channel 3
		temp_data = (unsigned int) (x*3.2258/10);
		lcd_cmd(0xC0);
		lcd_write_string(display_msg3);
		int_to_string(temp_data,temp_ip_data_ascii);
		lcd_write_string(temp_ip_data_ascii);
		lcd_write_string(display_msg4);
		
		msdelay(1000);
		
		
	}
}

