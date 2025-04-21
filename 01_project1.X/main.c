// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 4000000 // Define the crystal frequency for delay function

void init(void);
void Lcd_command(unsigned char);
void Lcd_data(unsigned char);

unsigned char array[7] = "BHAVANA";

// Arrays for cursor positions
unsigned char upper[16] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 
    0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F
};

unsigned char lower[16] = {
    0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 
    0xC7, 0xC6, 0xC5, 0xC4, 0xC3, 0xC2, 0xC1, 0xC0
};

void main()
{
    unsigned char i;

    init();
    
    // Print normally in the first row starting from 0x82
    for (i = 0; i < 7; i++)
    {
        Lcd_command(upper[2 + i]); // Starting from 0x82
        Lcd_data(array[i]);    // Display the character
    }

    // Print in reverse in the second row starting from 0xCD
    for (i = 0; i < 7; i++)
    {
        Lcd_command(lower[2 + i]); // Starting from 0xCD
        Lcd_data(array[6 - i]);    // Reverse display
    }

    while(1); // Loop forever
}

void init()
{
    TRISC = 0x00; // Configure PORTC as output
    TRISD = 0x00; // Configure PORTD as output

    Lcd_command(0x30); // 0011 0000 - Initialization
    __delay_ms(100);
    Lcd_command(0x30); // Initialization
    __delay_ms(100);
    Lcd_command(0x30); // Initialization
    __delay_ms(100);
    Lcd_command(0x38); // Function set: 8-bit, 2 lines, 5x8 dots
    __delay_ms(100);   
    Lcd_command(0x0C); // Display on, cursor off
    __delay_ms(100);
    Lcd_command(0x01); // Clear display
    __delay_ms(100);
}

void Lcd_data(unsigned char i)
{
    RC3 = 1;   // RS = 1 (data mode)
    PORTD = i; // Send data to PORTD
    RC0 = 1;   // EN = 1 (Enable high)
    __delay_ms(5);
    RC0 = 0;   // EN = 0 (Enable low)
}

void Lcd_command(unsigned char i)
{
    RC3 = 0;   // RS = 0 (command mode)
    PORTD = i; // Send command to PORTD
    RC0 = 1;   // EN = 1 (Enable high)
    __delay_ms(5);
    RC0 = 0;   // EN = 0 (Enable low)
}