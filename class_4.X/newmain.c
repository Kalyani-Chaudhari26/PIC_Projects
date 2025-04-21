// CONFIGURATION BITS
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage ICSP disabled
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection off
#pragma config WRT = OFF        // Flash Program Memory Write Enable off
#pragma config CP = OFF         // Flash Program Memory Code Protection off

#include <xc.h>

#define _XTAL_FREQ 6000000  // Define crystal frequency (6 MHz)

// Function Prototypes
void Lcd_Init(void);
void Lcd_Command(unsigned char);
void Lcd_Data(unsigned char);
void LcdOutput(unsigned int);
void delay(unsigned int);

// Global Variable Declarations
unsigned char j, k[5], Equal, Plus;
unsigned int num1, num2, sum, delaycount, m, n;

void main() {
    // Initialize LCD
    Lcd_Init();

    num1 = 468;
    num2 = 253;
    Equal = '=';
    Plus = '+';

    // Display first number on LCD
    Lcd_Command(0x80);  // Set cursor to starting position
    LcdOutput(num1);

    // Display '+' symbol
    Lcd_Command(0x83);
    Lcd_Data(Plus);

    // Display second number
    Lcd_Command(0x84);
    LcdOutput(num2);

    // Display '=' symbol
    Lcd_Command(0x87);
    Lcd_Data(Equal);

    // Compute sum and display result
    sum = num1 + num2;
    Lcd_Command(0x88);
    LcdOutput(sum);

    while (1);  // Infinite loop
}

// LCD Initialization
void Lcd_Init(void) {
    TRISC = 0x00;  // Set PORTC as output
    TRISD = 0x00;  // Set PORTD as output

    // LCD configuration sequence
    Lcd_Command(0x30);
    __delay_ms(100);
    Lcd_Command(0x30);
    __delay_ms(100);
    Lcd_Command(0x30);
    __delay_ms(100);
    Lcd_Command(0x38); // 8-bit mode
    __delay_ms(100);
    Lcd_Command(0x06); // Shift cursor right
    __delay_ms(100);
    Lcd_Command(0x0C); // Display on, cursor off
    __delay_ms(100);
    Lcd_Command(0x01); // Clear display
    __delay_ms(100);
}

// Function to Display Numbers on LCD
void LcdOutput(unsigned int i) {
    unsigned char s, j = 1;
    m = i;

    // Extract digits and store them in k[]
    while (m != 0) {
        //s = m % 10;
        //k[j] = s;
        //j++;
        //m /= 10;
         s= m-((m/10)*10);
        k[j] = s;
        j++;
        m = m/10;
    }
    k[j] = '\0'; // Assign null termination
    j--;

    // Display digits on LCD
    while (j != 0) {
        n = 0x30 + k[j]; // Convert to ASCII
        Lcd_Data(n);
        j--;
    }
}

// Function to Send Commands to LCD
void Lcd_Command(unsigned char cmd) {
    PORTC &= ~0x08;  // RS = 0 (Command mode) at RC3
    PORTD = cmd;     // Send command to PORTD
    PORTC |= 0x01;   // EN = 1 at RC0 (Enable high)
    __delay_ms(1);
    PORTC &= ~0x01;  // EN = 0 at RC0 (Enable low)
    __delay_ms(3);   // Delay for command execution
}

// Function to Send Data to LCD
void Lcd_Data(unsigned char data) {
    PORTC |= 0x08;   // RS = 1 (Data mode) at RC3
    PORTD = data;    // Send data to PORTD
    PORTC |= 0x01;   // EN = 1 at RC0 (Enable high)
    __delay_ms(1);
    PORTC &= ~0x01;  // EN = 0 at RC0 (Enable low)
    __delay_ms(3);   // Delay for data execution
}

// Delay Function
void delay(unsigned int delaycount) {
    while (--delaycount);
}

