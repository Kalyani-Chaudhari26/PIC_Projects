// CONFIG
#pragma config FOSC = HS    // Oscillator Selection bits (RC oscillator)
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
unsigned char pwm10_high, pwm10_low;
unsigned char pwm50_high, pwm50_low;
unsigned char pwm80_high, pwm80_low;

// Function prototypes
void pwm_init(void);
void pwm_dutycycle_update(void);

void main()
{
    pwm_init();  // Initialize PWM settings
    
    while (1)
    {
        pwm_dutycycle_update();  // Update PWM duty cycle continuously
    }
}
// Define PWM duty cycle high and low byte values
void pwm_init(void)
{
    TRISC = 0xFB;    // Configure RC2 as output (1111 1011)
    CCP1CON = 0x0C;  // Set PWM mode for CCP1
    T2CON = 0x06;    // Enable Timer2 with prescaler 1:16
    PR2 = 0x5E;      // Set PWM period
// Initialize PWM duty cycle values
// Additional configurations can be added based on requirements
pwm10_high = 0x09;
pwm10_low  = 0x02;

pwm50_high = 0x2F;
pwm50_low  = 0x00;

pwm80_high = 0x4B;
pwm80_low  = 0x00;
}
// Function to update PWM duty cycle
void pwm_dutycycle_update(void)
{
    // Set 10% duty cycle
    CCPR1L = pwm10_high;  // High byte (0x09)
    CCP1CON = (CCP1CON & 0xCF) | (pwm10_low << 4); // Low byte (0x02)
    __delay_ms(3000);  // Delay for 3 seconds

    // Set 50% duty cycle
    CCPR1L = pwm50_high;  // High byte (0x2F)
    CCP1CON = (CCP1CON & 0xCF) | (pwm50_low << 4); // Low byte (0x00)
    __delay_ms(3000);  // Delay for 3 seconds

    // Set 80% duty cycle
    CCPR1L = pwm80_high;  // High byte (0x4B)
    CCP1CON = (CCP1CON & 0xCF) | (pwm80_low << 4); // Low byte (0x00)
    __delay_ms(3000);  // Delay for 3 seconds
}
