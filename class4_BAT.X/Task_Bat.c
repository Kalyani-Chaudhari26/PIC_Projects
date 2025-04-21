// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 6000000  // 6 MHz

float j = 17.5;  // Start from 17.5V
void Lcd_Data(unsigned char);
void Lcd_Command(unsigned char);
void delay(unsigned int);
void displayVoltage(float voltage);
void displayBatteryStatus(float voltage);
void buttonScan();
void init();
void Lcd_Write_String(const char *str);  
void Lcd_Write_String( const char *str) {
    while (*str) {   // Loop through the string until null terminator '\0'
        Lcd_Data(*str);  // Print each character on the LCD
        str++;  // Move to the next character
    }
}
unsigned char array[15] = {"BAT VOLT     V"};
unsigned char x, m, n, value;
unsigned int i;

void main()
{
    init();
    while (1)
    {
         buttonScan ();
    }
}
void init()
{
    TRISC=0X00;   // set PORTC as output
    TRISD=0X00;   // setPORTD as output
    TRISB=0XF0;   // set R4toR7 as input others all output
  
    OPTION_REG=0X7F;   // use pullup register
    
    Lcd_Command(0x38); // 8-bit mode, 2-line display
    __delay_ms(100);
    
    Lcd_Command(0x30);
    __delay_ms(100);
    
    Lcd_Command(0x30);
     __delay_ms(100);
    
    Lcd_Command(0x30);
     __delay_ms(100);
    
    Lcd_Command(0x38);
    __delay_ms(100);
    
    Lcd_Command(0x06); // Set cursor to right shift
     __delay_ms(100);
    
    Lcd_Command(0x0C); // Display on, cursor off
    __delay_ms(100);
    
    Lcd_Command(0x01); // Clear display
    __delay_ms(100);
}

 void buttonScan ()
{
    value = PORTB &0xF0;
    switch(value){
    case 0XE0:
           
        Lcd_Command(0x80);
        for(x=0; x<8; x++)
        {
            Lcd_Data(array[x]);  //print an array on lcd
        }
        
    j = 17.5;  // Initialize voltage
    Lcd_Command(0x8C);  // Move cursor to correct position for value
    displayVoltage(j);  // Print 17.5 V correctly
    Lcd_Data('V');  // Print 'V' after voltage
    Lcd_Command(0xC0);
    displayBatteryStatus(j);
    break;
    
    case 0XD0:
         j += 0.1;   //increment by 0.1
         if (j > 22.5) {  
              j = 22.5;  // Force it to stay at 22.5
        }
        Lcd_Command(0xC0);
        displayVoltage(j);
        displayBatteryStatus(j);
    break;

    case 0XB0:
         j -= 0.1; //decrement by 0.1
        if (j < 15.5) {  
          j = 15.5;  // Force it to stay at 22.5
        }
        Lcd_Command(0xC0);
        displayVoltage(j);
        displayBatteryStatus(j);
    break;
    
    case 0X70:
        j = 17.5 ; //reset to again 17.5
        Lcd_Command(0xC0);
        displayVoltage(j);
        displayBatteryStatus(j);
    break;
} 
}
void Lcd_Command(unsigned char i)
{
    PORTC &= ~0x08; // RS=1 at RC3
    PORTD = i;      // data
    PORTC |= 0x01;  // EN=1 at RC0
    PORTC &= ~0x01; // EN=0 at RC0
    __delay_ms(10);  //Delay for command execution
}
void Lcd_Data(unsigned char i)
{
    PORTC |= 0X08;  // RS=0 at RC3
    PORTD = i;      // data
    PORTC |= 0X01;  // EN=1 at RC0
    PORTC &= ~0X01; // EN=0 at RC0
    __delay_ms(10);  //Delay for data execution
}

void displayVoltage(float voltage) {
    int intPart = (int)voltage;        // Extract integer part (e.g., 17)
    int decimalPart = (int)(voltage * 10) % 10;  // Extract decimal part (e.g., 5 from 17.5)
    Lcd_Command(0x88);  // Set cursor position
    Lcd_Data('=');  // Print '=' symbol

    if (intPart >= 10) {  
        Lcd_Data((intPart / 10) + '0');  // Print tens digit
    }
    Lcd_Data((intPart % 10) + '0');  // Print ones digit
    Lcd_Data('.');  // Print decimal point
    Lcd_Data(decimalPart + '0');  // Print decimal part
}
void displayBatteryStatus(float voltage) {
  
    Lcd_Command(0xC0);  // Move cursor to the second line 
    if (j>= 15.5 && j <= 17.5) {
        Lcd_Write_String("BATT LOW      ");
    } else if (j>= 17.6 && j <= 20.5) {
        Lcd_Write_String("BATT MEDIUM   ");
    } else if (j >= 20.6 && j <= 22.5) {
        Lcd_Write_String("BATT HIGH     ");
    } 
}


