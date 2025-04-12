#include <at89c5131.h>
#include "lcd.h"
#include <stdio.h>

/*
		The task performed here is unsigned MAC (Multiply and Accumulate)
		We will get 3 inputs from the switches (P1.3 - P1.0). We shall use LEDs to display which inputs are being fetched from the switches.
		We will multiply these results with some constants -- a*input_1 + b*input_2 + c*input_3
		The final answer is set in the LCD display as output along with all LEDs glowing when tbe output is displayed.
*/

// Input texts used everytime to show message in LCD which will be stored in the code segment.
code unsigned char display_msg1[]="   SET INPUT 1  ";
code unsigned char display_msg2[]="   SET INPUT 2  ";
code unsigned char display_msg3[]="   SET INPUT 3  ";
code unsigned char display_msg4[]="  FINAL RESULT  ";

void main()
{
	unsigned int x1 , x2, x3;		// Input Values
	unsigned int w0 = 10;				// Constant 1
	unsigned int w1 = 10;				// Constant 2
	unsigned int w2 = 20;				// Constant 3
	unsigned int y;							// Result
	char temp[16];
	
	lcd_init();									// Initialize LCD
	
	// Set First Input for LCD
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg1);
	
	// Get input 1
	P1 = 0x1F;				// Setting P1 as input and making LED to represent 1
	sdelay(5);				// Wait 5 seconds
	x1 = P1 & 0x0F;		// Taking the input collected in Port 1
	
	// Set Second Input for LCD
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg2);
	
	// Get input 2
	P1 = 0x2F;				// Setting P1 as input and making LED to represent 2
	sdelay(5);				// Wait 5 seconds
	x2 = P1 & 0x0F;  	// Taking the input collected in Port 1
	
	// Set Second Input for LCD
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg3);
	
	// Get input 3
	P1 = 0x3F;				// Setting P1 as input and making LED to represent 3
	sdelay(5);				// Wait 5 seconds
	x3 = P1 & 0x0F;		// Taking the input collected in Port 1
	
	// Perform MAC Operation
	y = (w0 * x1) + (x2 * w1) + (x3 * w2);
	sprintf(temp, "%d", y);									// Store the print output to temp variable
	
	// Display the result with all LEDs turning ON.
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg4);
	
	// Print the result in second line
	lcd_cmd(0xC0);
	lcd_write_string(temp);
	
	
	while(1);
		
}