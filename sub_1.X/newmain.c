
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
// PIC16F877A Configuration Bit Settings
#include <xc.h>
#define _XTAL_FREQ 6000000  // 6 MHz

// Function prototypes
void Lcd_Init(void);
void Lcd_Command(unsigned char);
void Lcd_Data(unsigned char);
void LcdOutput(int);

// Variable declarations
unsigned char Equal;
int num1, num2, sub;

void main() {
    Lcd_Init();
    
    num1 = 100;
    num2 = 200;
    Equal = '=';

    // Display first number (without sign)
    Lcd_Command(0x80);
    LcdOutput(num1);

    // Display '-' symbol
    Lcd_Command(0x83);
    Lcd_Data('-');

    // Display second number (without sign)
    Lcd_Command(0x84);
    LcdOutput(num2);

    // Display '=' symbol
    Lcd_Command(0x87);
    Lcd_Data(Equal);

    // Compute subtraction
    sub = num1 - num2;

    // Display sign of the answer
    Lcd_Command(0x88);
    if (sub < 0) {
        Lcd_Data('-');   // Display '-' if result is negative
        sub = -sub;      // Convert negative to positive for display
    } else {
        Lcd_Data('+');   // Display '+' if result is positive
    }

    // Display absolute value of the answer
    LcdOutput(sub);
    
    while(1);
}

void Lcd_Init(void) {
    TRISC = 0x00;  // Set PORTC as output
    TRISD = 0x00;  // Set PORTD as output

    // LCD Initialization sequence
    Lcd_Command(0x30);
    __delay_ms(100);
    Lcd_Command(0x30);
    __delay_ms(100);
    Lcd_Command(0x30);
    __delay_ms(100);
    Lcd_Command(0x38); // 2-line, 5x7 matrix
    __delay_ms(100);
    Lcd_Command(0x06); // Shift cursor to right
    __delay_ms(100);
    Lcd_Command(0x0C); // Display ON, cursor OFF
    __delay_ms(100);
    Lcd_Command(0x01); // Clear display
    __delay_ms(100);
}

void LcdOutput(int num) {
    unsigned char digits[5];  // Array to hold digits
    unsigned char i = 0;

    if (num == 0) {
        Lcd_Data('0');  // Directly print '0' if number is zero
        return;
    }

    while (num != 0) {
        digits[i] = (num % 10) + '0';  // Extract last digit and convert to ASCII
        num /= 10;
        i++;
    }

    // Print the digits in the correct order
    while (i > 0) {
        i--;
        Lcd_Data(digits[i]);
    }
}

void Lcd_Command(unsigned char cmd) {
    PORTC &= ~0x08;  // RS = 0 (Command mode) at RC3
    PORTD = cmd;     // Send command to PORTD
    PORTC |= 0x01;   // EN = 1 at RC0 (Enable high)
    PORTC &= ~0x01;  // EN = 0 at RC0 (Enable low)
    __delay_ms(100); // Delay for command execution
}

void Lcd_Data(unsigned char data) {
    PORTC |= 0x08;   // RS = 1 (Data mode) at RC3
    PORTD = data;    // Send data to PORTD
    PORTC |= 0x01;   // EN = 1 at RC0 (Enable high)
    PORTC &= ~0x01;  // EN = 0 at RC0 (Enable low)
    __delay_ms(100); // Delay for data execution
}
