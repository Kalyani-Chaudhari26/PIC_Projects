// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF  // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 6000000  // 6 MHz
void Lcd_Data(unsigned char);
void Lcd_Command(unsigned char);
void Lcdoutput(unsigned int);
void delay(unsigned int);
void keyscane();
void init();

unsigned char array[15] = {"SET SPD:    rpm"};
unsigned char x, m, n, value;
unsigned int i, j, d1, d2, d3, d4;

void main()
{
    init();
    while (1)
    {
        keyscane();
    }
}
void init()
{
    TRISC=0X00;   // set PORTC as output
    TRISD=0X00;   // setPORTD as output
    TRISB=0XF0;   // set R4toR7 as input others all output
    //PORTB=0x00;
    OPTION_REG=0X7F;   // use pullup reg
    //LCD Configuration
   
    // LCD configuration sequence
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

void keyscane()
{
    value = PORTB &0xF0;
    switch(value){
    case 0XE0:
        Lcd_Command(0x80);
        for(x=0; x<8; x++)
        {
            Lcd_Data(array[x]);
        }
        Lcd_Command(0X8C);
        for(x=12; x<15; x++)
        {
            Lcd_Data(array[x]);
        }
        Lcd_Command(0X88);
        Lcdoutput(j);
        break;

    case 0XD0:
    j++;
    if(j > 5000)
    {
        j = 5000;
    }
    Lcd_Command(0X88);
    Lcdoutput(j);
    break;

    case 0XB0:
    j--;
    if(j < 1)
    {
        j = 1;
    }
    Lcd_Command(0X88);
    Lcdoutput(j);
    break;
    
    case 0X70:
    j=0;
    Lcd_Command(0X88);
    Lcdoutput(j);
    break;
}
}
void Lcd_Command(unsigned char i)
{
    PORTC &= ~0x08; // RS=1 at RC3
    PORTD = i;      // data
    PORTC |= 0x01;  // EN=1 at RC0
    PORTC &= ~0x01; // EN=0 at RC0
    __delay_ms(100);
}
void Lcd_Data(unsigned char i)
{
    PORTC |= 0X08;  // RS=0 at RC3
    PORTD = i;      // data
    PORTC |= 0X01;  // EN=1 at RC0
    PORTC &= ~0X01; // EN=0 at RC0
    __delay_ms(100);
}
void Lcdoutput(unsigned int i)
  {
    d4 = (unsigned char)(i / 1000);
    d3 = (unsigned char)((i - (d4 * 1000)) / 100);
    d2 = (unsigned char)((i - (d4 * 1000) - (d3 * 100)) / 10);
    d1 = (unsigned char)(i - (d4 * 1000) - (d3 * 100) - (d2 * 10));

    Lcd_Command(0X88);
    Lcd_Data(0X30 + d4); // ASCII change
    Lcd_Command(0X89);
    Lcd_Data(0X30 + d3);
    Lcd_Command(0X8A);
    Lcd_Data(0X30 + d2);
    Lcd_Command(0X8B);
    Lcd_Data(0X30 + d1);
  }
