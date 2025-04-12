/*************************************************
 	lcd.h: Header file for 16x2 LCD interfacing  
**************************************************/

//Functions contained in this header file
void msdelay(unsigned int);																	//fn takes integer value as an input and generates corresponding delay in milli seconds
void lcd_init(void);																				//Initialize LCD
void lcd_cmd(unsigned int i);																//Sends commands to lcd
void lcd_char(unsigned char ch);														//display character on a lcd corresponding to input ascii
void lcd_write_string(unsigned char *s);										//takes pointer of a string which ends with null and display on a lcd 


//Signals to LCD
sbit RS=P0^0;	//Register select
sbit RW=P0^1;	//Read from or write to register
sbit EN=P0^2;	//Enable pin of lcd


//Function definitions
/************************************************
   lcd_init():
	Initializes LCD port and 
	LCD display parameters
************************************************/
void lcd_init(void)
{
	P2=0x00;
	EN=0;
	RS=0;
	RW=0;
	
	lcd_cmd(0x38);	// Function set: 2 Line, 8-bit, 5x7 dots
	msdelay(4);
	lcd_cmd(0x06);	// Entry mode, auto increment with no shift
	msdelay(4);
	lcd_cmd(0x0C);	// Display on, Curson off
	msdelay(4);
	lcd_cmd(0x01);	// LCD clear
	msdelay(4);
	lcd_cmd(0x80);	//Move cursor to Row 1 column 0
}

/**********************************************************
   msdelay(<time_val>): 
	Delay function for delay value <time_val>ms
***********************************************************/	
void msdelay(unsigned int time)
{
	int i,j;
	for(i=0;i<time;i++)
	{
		for(j=0;j<382;j++);
	}
}

/**********************************************************
    lcd_cmd(<char command>):
	Sends 8 bit command
	LCD display parameters
***********************************************************/	
void lcd_cmd(unsigned int i)
{
	RS=0;
	RW=0;
	EN=1;
	P2=i;
	msdelay(10);
	EN=0;
}


/**********************************************************
   lcd_write_char(<char data>):
	Sends 8 bit character(ASCII)
	to be printed on LCD
***********************************************************/	
void lcd_write_char(unsigned char ch)
{
	RS=1;
	RW=0;
	EN=1;
	P2=ch;
	msdelay(10);
	EN=0;
}


/***********************************************************
  lcd_write_string(<string pointer>):
	Prints string on LCD. Requires string pointer 
	as input argument.
***********************************************************/	
void lcd_write_string(unsigned char *s)
{
	while(*s!='\0')
	{
		lcd_write_char(*s++);
	}
}

void lcd_float(float value) {
    int int_part = (int)value;
    float decimal_part = value - int_part;
	
    char str[16];
    int digits = 0, i;
		int flag = 1;

    while (int_part > 0) {
				flag = 0;
        str[digits++] = '0' + (int_part % 10);
        int_part /= 10;
    }

    for (i = 0; i < digits / 2; ++i) {
        char temp = str[i];
        str[i] = str[digits - i - 1];
        str[digits - i - 1] = temp;
    }
		if (flag) {
			str[digits++] = '0';
			str[digits++] = '.';
		}
		else str[digits++] = '.';
		
    for (i = 0; i < 3; ++i) {
        decimal_part *= 10;
        str[digits++] = '0' + (int)decimal_part;
        decimal_part -= (int)decimal_part;
    }

    str[digits] = '\0';
	lcd_write_string(str);
}