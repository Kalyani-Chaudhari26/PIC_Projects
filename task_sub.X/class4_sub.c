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
// Function prototypes
void Lcd_Init(void);
void Lcd_Command(unsigned char);
void Lcd_Data(unsigned char);
void delay(unsigned int);
void LcdOutput(unsigned int);
void Lcd_PrintSubtraction(int, int);
// Variable declarations
unsigned char j, k[5], Equal, minus ;
unsigned int num1, num2, sub, delaycount, m,n ;

void main() {
    Lcd_Init();
    
    num1 = 200;
    num2 = 100;
    Equal = '=';
    minus = '-';

    // Display first number on LCD
    Lcd_Command(0x80);  // Set cursor to starting position
    LcdOutput(num1);

    // Display '+' symbol
    Lcd_Command(0x83);
    Lcd_Data(minus);

    // Display second number
    Lcd_Command(0x84);
    LcdOutput(num2);

    // Display '=' symbol
    Lcd_Command(0x87);
    Lcd_Data(Equal);

    // Compute sum and display result
    Lcd_Command(0x88);  // Set cursor position (example)
    Lcd_PrintSubtraction(200,100);  // Subtract 10 - 5 and display result on LCD
    
while(1);
}
    // Further implementation goes here
void Lcd_PrintSubtraction(int num1, int num2) {
    int sub;

    if (num1 < num2) {
        Lcd_Data('-');  // Display negative sign
        sub = num2 - num1;  // Ensure positive value for display
  } else {
        sub = num1 - num2;
         Lcd_Data('+');
    }
 LcdOutput(sub);  // Display the absolute result
}

void Lcd_Init(void) {
// Set PORTC and PORTD as output
TRISC = 0x00;  // Set PORTC as output
TRISD = 0x00;  // Set PORTD as output

// LCD Initialization
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
void LcdOutput(unsigned int i) {
    unsigned char s,j = 1;
    m = i;
    while(m!=0){
        s= m-((m / 10)*10);
        k[j] = s;
        j++;
        m = m/10;
    }
    k[j] = '\0'; // assign null
    j=j-1;
    while(j!= 0) {
       n = 0x30 +k[j];
       Lcd_Data(n);
       j--;
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
void delay(unsigned int delaycount)
{
    while(--delaycount);
}
