#include "seven_segment.h"
#include "DS1307.h"

sbit set at RA0_bit;
sbit reset at RA1_bit;
sbit minplus at RA2_bit;
sbit hourplus at RA3_bit;

unsigned char second, minute, hour, week_day, day, month, year;

signed char inTemp, outTemp;

void init() {
    ANSEL = 0;
    ANSELH = 0;
    C1ON_bit = 0;                      // Disable comparators
    C2ON_bit = 0;
    TRISA = 255;
    TRISB = 0;
    TRISD = 0;
    TRISE = 0b1110;
    PORTB = 0;
    PORTD = 0;
    I2C1_Init(100000);
    
    OPTION_REG = 0x04; // Prescaler (1:32) is assigned to the timer TMR0
    TMR0 = 155;        // Timer T0 counts from 155 to 255
    OPTION_REG.INTEDG = 1;        // Set Rising Edge Trigger for INT
    INTCON.GIE = 1;               // Enable The Global Interrupt
    INTCON.T0IE = 1;              // Enable T0IE
}

void tempRead() {
    unsigned int adc;
    
    ADCON0 = 0b00011101;  //CHANEL7
    adc = Adc_Read(7);
    inTemp = (0.49 * adc - 273.15);
    
    ADCON0 = 0b00011001;  //CHANEL6
    adc = Adc_Read(6);
    outTemp = (0.49 * adc - 273.15);
}

void main() {
    char i = 0;
    init();
    //resetTime();
    //setTime(0, 24, 21, 0, 0, 0, 0);
    //setDisplayTemp(12, 0);
    

    
    while(1) {
        //readTime(&second, &minute, &hour, &week_day, &day, &month, &year);
        //setDisplayTime(hour, minute, second);
        //tempRead();
        //setDisplayTemp(inTemp, 0);
        //display();
        setDisplayTime(0, i, 0);
        delay_ms(200);
        i++;
    }
}

void interrupt() {
   display();
   TMR0 = 155;        // Timer (or counter) TMR0 returns its initial value
   INTCON.T0IF = 0;   // Clear the interrupt 0 flag
   INTCON.T0IE = 1;
}