#include <at89c5131.h>
#include "lcd.h"

#define ROW_MASK 0xF0  // Mask for row bits (P3.7 - P3.4)
#define COL_MASK 0x0F  // Mask for column bits (P3.3 - P3.0)

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 382; j++);
}

char scan_keypad() {
    char key_map[4][4] = { {'1', '2', '3', 'A'},
                            {'4', '5', '6', 'B'},
                            {'7', '8', '9', 'C'},
                            {'*', '0', '#', 'D'} };
    int row, col;
    
    P3 |= COL_MASK; // Set column pins as input (high)
    P3 &= ~ROW_MASK; // Set row pins as output (low)
    
    if ((P3 & COL_MASK) == COL_MASK) return 0; // No key pressed
    
    delay_ms(20); // Debounce delay
    if ((P3 & COL_MASK) == COL_MASK) return 0; // Confirm no false trigger
    
    for (row = 0; row < 4; row++) {
        P3 |= ROW_MASK; // Set all rows high
        P3 &= ~(1 << (row + 4)); // Ground only the current row
        
        for (col = 0; col < 4; col++) {
            if ((P3 & (1 << col)) == 0 ) { // Check if key is pressed\\\!
                while ((P3 & (1 << col))); // Wait for release\\\!
                return key_map[row][col]; // Return key value
            }
        }
    }
    return 0;
}

void main() {
     char key;
    lcd_init(); // Initialize LCD
   lcd_cmd(0x80); // Move to first line
	
    lcd_write_string("Keypad Test");
    delay_ms(500);
    lcd_cmd(0xC0); // Move to second line
    lcd_write_string("Press Key:");
    
   while (1) {
        key = scan_keypad();
        if (key) {
            lcd_cmd(0xC9); // Move cursor position
            lcd_write_char(key); // Display key on LCD
					}
    }
}