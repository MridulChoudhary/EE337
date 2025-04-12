#include <at89c5131.h>
#include "lcd.h"
#include <stdio.h>
#include <string.h>

// Instead of adding <string.h>, we can use the following declaration
// char *strcpy(char *dest, const char *src);  // Function prototype


sbit OUTPUT = P0^7;
int x=0;

sbit Row_0 = P3^4;
sbit Row_1 = P3^5;
sbit Row_2 = P3^6;
sbit Row_3 = P3^7;

sbit Col_0 = P3^3;
sbit Col_1 = P3^2;
sbit Col_2 = P3^1;
sbit Col_3 = P3^0;

	int k;
	int l;
	int pin1 = 0x01;
	int pin2 = 0x01;
	int value1;
	int value2;
//	char *temp1;
	char temp[16];
	char temp2[16];

//0xEFB9  --  240Hz   change to this value in all parts of the code for 240Hz
//0xF063  --  240Hz
//0xF188  --  270Hz
//0xF2FB  --  300Hz
//0xF3CB  --  320Hz
//0xF526  --  360Hz
//0xF63C  --  400Hz	
//0xF752  --  450Hz
//0xF7DD  --  480Hz

/*	
void msdelay(unsigned int time) {
    int i, j;
    for (i = 0; i < time; i++) {
        for (j = 0; j < 382; j++);
    }
}
*/

void timer0_isr () interrupt 1
{
    switch (x) {
    case 1:
				OUTPUT = ~OUTPUT;
				TH0 = 0xEF;    // Reload for 1.5 ms delay (since 3 ms period requires toggling every 1.5 ms)
				TL0 = 0xB9;
				TR0 = 1;       // Restart timer
        break;

    case 2:
				OUTPUT = ~OUTPUT;
				TH0 = 0xF1;    // Reload for 1.5 ms delay (since 3 ms period requires toggling every 1.5 ms)
				TL0 = 0x88;
				TR0 = 1;       // Restart timer
				break;

    case 3:
				OUTPUT = ~OUTPUT;
				TH0 = 0xF2;    // Reload for 1.5 ms delay (since 3 ms period requires toggling every 1.5 ms)
				TL0 = 0xFB;
				TR0 = 1;       // Restart timer
        break;

    case 4:
				OUTPUT = ~OUTPUT;
				TH0 = 0xF3;    // Reload for 1.5 ms delay (since 3 ms period requires toggling every 1.5 ms)
				TL0 = 0xCB;
				TR0 = 1;       // Restart timer
        break;

    case 5:
				OUTPUT = ~OUTPUT;
				TH0 = 0xF5;    // Reload for 1.5 ms delay (since 3 ms period requires toggling every 1.5 ms)
				TL0 = 0x26;
				TR0 = 1;       // Restart timer
        break;

    case 6:
				OUTPUT = ~OUTPUT;
				TH0 = 0xF6;    // Reload for 1.5 ms delay (since 3 ms period requires toggling every 1.5 ms)
				TL0 = 0x3C;
				TR0 = 1;       // Restart timer
        break;
		
    case 7:
				OUTPUT = ~OUTPUT;
				TH0 = 0xF7;    // Reload for 1.5 ms delay (since 3 ms period requires toggling every 1.5 ms)
				TL0 = 0x52;
				TR0 = 1;       // Restart timer
        break;

    case 8:
				OUTPUT = ~OUTPUT;
				TH0 = 0xF7;    // Reload for 1.5 ms delay (since 3 ms period requires toggling every 1.5 ms)
				TL0 = 0xDD;
				TR0 = 1;       // Restart timer
        break;
		
		case 9:
				OUTPUT = 0;
				break;
		
//    default:
//        printf("Default case is Matched.");
//        break;
    }
}


void main() {
	TMOD = 0x01; //Timer 0 in mod 1
	TH0 = 0xEF;
	TL0 = 0xB9;
	ET0 = 1; //activate interrupts for both timers
	EA = 1;  //activate global interrupts
	TR0 = 1; //start timer 0

//	P3 = 0x0F;
	Row_0 = Row_1 = Row_2 = Row_3 = 0;
	Col_0 = Col_1 = Col_2 = Col_3 = 1;
	lcd_init();									// Initialize LCD

	while(1){
		Row_0 = Row_1 = Row_2 = Row_3 = 0;
		Col_0 = Col_1 = Col_2 = Col_3 = 1;
		for(k=0; k<4; k++){
			pin1 = 0x01;
			value1 = P3 & (pin1 << k);
			if (value1 == 0){
				msdelay(20);
				value1 = P3 & (pin1 << k);
				if (value1 == 0){
					for(l=0; l<4; l++){
//						pin2 = 0x01;
//						value2 = P3 & (pin1 << (l + 4));
						if(l == 0){
							Row_0 = 0;
							Row_1 = Row_2 = Row_3 = 1;
							value1 = P3 & (pin1 << k);
							if(value1 == 0){
/*								sprintf(temp2, "%d", l);									// Store the print output to temp variable
								lcd_cmd(0x80);													//Move cursor to first line
								lcd_write_string(temp2);
								sprintf(temp, "%d", 3-k);									// Store the print output to temp variable
								lcd_cmd(0xC0);
								lcd_write_string(temp);
*/
								if(k == 0){
									*temp = 'A';
							    lcd_cmd(0x01); // Clear display command
									lcd_cmd(0x80);													//Move cursor to first line
									lcd_write_char(*temp);
								}
								if(k == 1){
//									temp = '3';
									strcpy(temp, "Ga");
									x = 3;
							    lcd_cmd(0x01); // Clear display command
									lcd_cmd(0x80);													//Move cursor to first line
									lcd_write_string(temp);
								}
								if(k == 2){
//									temp = '2';
									strcpy(temp, "Re");
									x = 2;
							    lcd_cmd(0x01); // Clear display command
									lcd_cmd(0x80);													//Move cursor to first line
									lcd_write_string(temp);
								}
								if(k == 3){
//									temp = '1';
									strcpy(temp, "Sa");
									x = 1;
							    lcd_cmd(0x01); // Clear display command
									lcd_cmd(0x80);													//Move cursor to first line
									lcd_write_string(temp);
								}								
							}
						}
						if(l == 1){
							Row_1 = 0;
							Row_0 = Row_2 = Row_3 = 1;
							value1 = P3 & (pin1 << k);
							if(value1 == 0){
/*								sprintf(temp2, "%d", l);									// Store the print output to temp variable
								lcd_cmd(0x80);													//Move cursor to first line
								lcd_write_string(temp2);
								sprintf(temp, "%d", 3-k);									// Store the print output to temp variable
								lcd_cmd(0xC0);
								lcd_write_string(temp);							
*/
								if(k == 0){
									*temp = 'B';
							    lcd_cmd(0x01); // Clear display command
									lcd_cmd(0x80);													//Move cursor to first line
									lcd_write_char(*temp);
								}
								if(k == 1){
//									temp = '6';
									strcpy(temp, "Dha");
									x = 6;
							    lcd_cmd(0x01); // Clear display command
									lcd_cmd(0x80);													//Move cursor to first line
									lcd_write_string(temp);
								}
								if(k == 2){
//									temp = '5';
									strcpy(temp, "Pa");
									x = 5;
							    lcd_cmd(0x01); // Clear display command
									lcd_cmd(0x80);													//Move cursor to first line
									lcd_write_string(temp);
								}
								if(k == 3){
//									temp = '4';
									strcpy(temp, "Ma");
									x = 4;
							    lcd_cmd(0x01); // Clear display command
									lcd_cmd(0x80);													//Move cursor to first line
									lcd_write_string(temp);
								}																
								}
						}
						if(l == 2){
							Row_2 = 0;
							Row_0 = Row_1 = Row_3 = 1;
							value1 = P3 & (pin1 << k);
							if(value1 == 0){
/*								sprintf(temp2, "%d", l);									// Store the print output to temp variable
								lcd_cmd(0x80);													//Move cursor to first line
								lcd_write_string(temp2);
								sprintf(temp, "%d", 3-k);									// Store the print output to temp variable
								lcd_cmd(0xC0);
								lcd_write_string(temp);							
*/							
								if(k == 0){
									*temp = 'C';
							    lcd_cmd(0x01); // Clear display command
									lcd_cmd(0x80);													//Move cursor to first line
									lcd_write_char(*temp);
								}
								if(k == 1){
//									temp = '9';
									strcpy(temp, "Silence");
									x = 9;
							    lcd_cmd(0x01); // Clear display command
									lcd_cmd(0x80);													//Move cursor to first line
									lcd_write_string(temp);
								}
								if(k == 2){
//									temp = '8';
									strcpy(temp, "Sa");
									x = 8;
							    lcd_cmd(0x01); // Clear display command
									lcd_cmd(0x80);													//Move cursor to first line
									lcd_write_string(temp);
								}
								if(k == 3){
//									temp = '7';
									strcpy(temp, "Ni");
									x = 7;
							    lcd_cmd(0x01); // Clear display command
									lcd_cmd(0x80);													//Move cursor to first line
									lcd_write_string(temp);
								}															
							}
						}						
						if(l == 3){
							Row_3 = 0;
							Row_0 = Row_1 = Row_2 = 1;
							value1 = P3 & (pin1 << k);
							if(value1 == 0){
/*								sprintf(temp2, "%d", l);									// Store the print output to temp variable
								lcd_cmd(0x80);													//Move cursor to first line
								lcd_write_string(temp2);
								sprintf(temp, "%d", 3-k);									// Store the print output to temp variable
								lcd_cmd(0xC0);
								lcd_write_string(temp);							
*/							
								if(k == 0){
									*temp = 'D';
							    lcd_cmd(0x01); // Clear display command
									lcd_cmd(0x80);													//Move cursor to first line
									lcd_write_char(*temp);
								}
								if(k == 1){
									*temp = '#';
							    lcd_cmd(0x01); // Clear display command
									lcd_cmd(0x80);													//Move cursor to first line
									lcd_write_char(*temp);
								}
								if(k == 2){
									*temp = '0';
							    lcd_cmd(0x01); // Clear display command
									lcd_cmd(0x80);													//Move cursor to first line
									lcd_write_char(*temp);
								}
								if(k == 3){
									*temp = '*';
							    lcd_cmd(0x01); // Clear display command
									lcd_cmd(0x80);													//Move cursor to first line
									lcd_write_char(*temp);
								}															
							}
						}
					}
				}
			}
		}
	}	
}