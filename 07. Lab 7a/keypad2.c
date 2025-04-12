#include <at89c5131.h>
#include <stdio.h>
#include "lcd.h"  

sbit ROW0 = P3^4;  
sbit ROW1 = P3^5;  
sbit ROW2 = P3^6;  
sbit ROW3 = P3^7;  

sbit COL0 = P3^3;  
sbit COL1 = P3^2; 
sbit COL2 = P3^1;  
sbit COL3 = P3^0;  


unsigned char keypad_map[4][4] = {
    {'1', '2', '3', 'A'},  
    {'4', '5', '6', 'B'},  
    {'7', '8', '9', 'C'},  
    {'*', '0', '#', 'D'}  
};


void init_keypad(void);
unsigned char scan_keypad(void);
void delay_ms(unsigned int ms);
void display_key(unsigned char key);


void main(void) {
    unsigned char key;
    
    lcd_init();
    lcd_cmd(0x80);
    init_keypad();
    
    while(1) {
        key = scan_keypad();
         
            display_key(key);
            
            while((COL0 == 0) || (COL1 == 0) || (COL2 == 0) || (COL3 == 0));
            delay_ms(20);
    }
}


void init_keypad(void) {
    ROW0 = 1;
    ROW1 = 1;
    ROW2 = 1;
    ROW3 = 1;
    
    // Columns are inputs with pull-ups (they should be high when not pressed)
    // This is handled by the hardware as mentioned in the PDF
}


unsigned char scan_keypad(void) {
    unsigned char row;
    
    if((COL0 == 1) && (COL1 == 1) && (COL2 == 1) && (COL3 == 1)) {
        return 0;  
    }
    
    delay_ms(20);
    
    for(row = 0; row < 4; row++) {
        ROW0 = 1;
        ROW1 = 1;
        ROW2 = 1;
        ROW3 = 1;
        
        switch(row) {
            case 0: ROW0 = 0; break;
            case 1: ROW1 = 0; break;
            case 2: ROW2 = 0; break;
            case 3: ROW3 = 0; break;
        }
        
        if(COL0 == 0) return keypad_map[row][0];  
        if(COL1 == 0) return keypad_map[row][1];  
        if(COL2 == 0) return keypad_map[row][2];  
        if(COL3 == 0) return keypad_map[row][3];  
    }
    
    return 0;  
}

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++) {
        for(j = 0; j < 328; j++);  
    }
}


void display_key(unsigned char key) {
    lcd_cmd(0x8C);  
    lcd_write_string(key);
}