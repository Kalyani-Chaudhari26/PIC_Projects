// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include<xc.h>
#define _XTAL_FREQ 6000000

// Declare PWM duty cycle high and low byte variables
unsigned char duty20_high, duty20_low;
unsigned char duty60_high, duty60_low;
unsigned char duty90_high, duty90_low;

// Function prototypes
void initialize_pwm(void);
void update_pwm_dutycycle(void);

void main()
{
    initialize_pwm();  // Initialize PWM 
    
    while (1)
    {
        update_pwm_dutycycle();  // Update PWM duty cycle continuously
    }
}

// Define PWM duty cycle high and low byte values
void initialize_pwm(void)
{
    TRISC = 0xFB;    // Configure RC2 as output (1111 1011)
    CCP1CON = 0x0C;  // Set PWM mode for CCP1
    T2CON = 0x06;    // Enable Timer2 with prescaler 1:16
    PR2 = 0x2E;      // Set PWM period
    
    // Initialize PWM duty cycle values
    duty20_high = 0x09;   //0000 1001
    duty20_low  = 0x02;   //0000 0010

    duty60_high = 0x1C;    //0001 1100
    duty60_low  = 0x01;    //0000 0001

    duty90_high = 0x2A;    //0010 1010
    duty90_low  = 0x01;    //0000 0001
}

// Function to update PWM duty cycle
void update_pwm_dutycycle(void)
{
    // Set 20% duty cycle
    CCPR1L = duty20_high;  // High byte (0x09)
    CCP1CON = (CCP1CON & 0xCF) | (duty20_low << 4); // Low byte (0x02)
    __delay_ms(3000);  // Delay for 3 seconds

    // Set 60% duty cycle
    CCPR1L = duty60_high;  // High byte (0x1C)
    CCP1CON = (CCP1CON & 0xCF) | (duty60_low << 4); // Low byte (0x01)
    __delay_ms(3000);  // Delay for 3 seconds

    // Set 90% duty cycle
    CCPR1L = duty90_high;  // High byte (0x2A)
    CCP1CON = (CCP1CON & 0xCF) | (duty90_low << 4); // Low byte (0x01)
    __delay_ms(3000);  // Delay for 3 seconds
}
