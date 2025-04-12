#include <at89c5131.h>
#include "lcd.h"
#include "serial.h"

sbit speaker = P0^7;

unsigned char current_th0, current_tl0;
unsigned char current_key = 0;

// Timer0 ISR for tone generation
void timer0_isr(void) interrupt 1 {
    speaker = ~speaker;       // Toggle speaker
    TH0 = current_th0;        // Reload timer values
    TL0 = current_tl0;
}

void main(void) {
    unsigned char key;
    
    lcd_init();               // Initialize LCD
    uart_init();              // Initialize UART
    lcd_cmd(0x80);
    lcd_write_string("Press a key...");

    TMOD |= 0x01;             // Timer0 in Mode 1 (16-bit)
    ET0 = 1;                  // Enable Timer0 interrupt
    EA = 1;                   // Global interrupt enable

    while(1) {
        if(RI) {             // Check if UART received a key
           RI = 0;

            key = SBUF;       // Read the received key

            lcd_cmd(0x01);    // Clear LCD
            lcd_cmd(0x80);

		
            switch(key) {
                case 's':     // Sa (Low)
                    current_th0 = 0xEF;
                    current_tl0 = 0xB9;
                    lcd_write_string("Sa(Low)");
                    TR0 = 1;
                    break;
                case 'r':     // Re
                    current_th0 = 0xF1;
                    current_tl0 = 0x88;
                    lcd_write_string("Re");
                    TR0 = 1;
                    break;
                case 'g':     // Ga
                    current_th0 = 0xF2;
                    current_tl0 = 0xFB;
                    lcd_write_string("Ga");
                    TR0 = 1;
                    break;
                case 'm':     // Ma
                    current_th0 = 0xF3;
                    current_tl0 = 0xCB;
                    lcd_write_string("Ma");
                    TR0 = 1;
                    break;
                case 'p':     // Pa
                    current_th0 = 0xF5;
                    current_tl0 = 0x26;
                    lcd_write_string("Pa");
                    TR0 = 1;
                    break;
                case 'd':     // Dha
                    current_th0 = 0xF6;
                    current_tl0 = 0x3C;
                    lcd_write_string("Dha");
                    TR0 = 1;
                    break;
                case 'n':     // Ni
                    current_th0 = 0xF7;
                    current_tl0 = 0x52;
                    lcd_write_string("Ni");
                    TR0 = 1;
                    break;
                case 'a':     // Sa (High)
                    current_th0 = 0xF7;
                    current_tl0 = 0xDD;
                    lcd_write_string("Sa(High)");
                    TR0 = 1;
                    break;
                case 'q':     // Silence
                    TR0 = 0;
                    speaker = 0;
                    lcd_write_string("Silence");
                    break;
                default:
                    lcd_write_string("Invalid Key");
                    break;
            }
        }
    }
}