#include "seven_segment.h"
#include "DS1307.h"

sbit set at RA0_bit;
sbit reset at RA1_bit;
sbit minplus at RA2_bit;
sbit hourplus at RA3_bit;

unsigned char second, minute, hour, week_day, day, month, year;
bit setting, buttonDown;
unsigned char mode = 0;
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
    setting = 0;
    buttonDown = 0;
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
    long modecounter = 0;
    init();
    //resetTime();
    //setTime(0, 24, 21, 0, 0, 0, 0);
    //setDisplayTemp(12, 0);


    
    while(1) {
        if(modecounter < 500)
            mode = 0;
        else
            mode = 1;
            

        if(modecounter > 400)
            modecounter = 0;
        
        //ENTERING SET TIME
        if (set) {
           buttonDown = 1;
           while (buttonDown) {
               if (!set)
                   buttonDown = 0;
           }
           setting = 1;
           setDisplayTime(hour, minute, second);
           setDots();
        }

        if (!setting) {
            modecounter ++;
            switch (mode) {
                case 0:
                    readTime(&second, &minute, &hour, &week_day, &day, &month, &year);
                    setDisplayTime(hour, minute, second);
                    break;
                case 1:
                    if(modecounter == 501)
                        tempRead();
                    setDisplayTemp(inTemp, 0);
                    break;
                case 2:
                    tempRead();
                    setDisplayTemp(outTemp, 1);
                    break;
            }
        }
        else {
            // SETTINGS
            
            //EXIT
            if (set) {
                buttonDown = 1;
                while (buttonDown) {
                    if (!set)
                        buttonDown = 0;
                }
                setting = 0;
                modecounter = 0;
            }
            
            if(reset) {
                buttonDown = 1;
                while (buttonDown) {
                    if(!reset)
                        buttonDown = 0;
                }
                resetTime();
                readTime(&second, &minute, &hour, &week_day, &day, &month, &year);
                setDisplayTime(hour, minute, second);
                setDots();
            }
            
            if(minplus) {
                buttonDown = 1;
                while (buttonDown) {
                    if(!minplus)
                        buttonDown = 0;
                }
                if(minute >= 59)
                    minute = 0;
                else
                    minute++;

                setTime(0, minute, hour, 0, 0, 0, 0);
                readTime(&second, &minute, &hour, &week_day, &day, &month, &year);
                setDisplayTime(hour, minute, second);
                setDots();
            }
            
            if(hourplus) {
                buttonDown = 1;
                while (buttonDown) {
                    if(!hourplus)
                        buttonDown = 0;
                }
                if(hour >= 23)
                    hour = 0;
                else
                    hour++;

                setTime(0, minute, hour, 0, 0, 0, 0);
                readTime(&second, &minute, &hour, &week_day, &day, &month, &year);
                setDisplayTime(hour, minute, second);
                setDots();
            }
            
        }
    }
}

void interrupt() {
   display();
   TMR0 = 155;        // Timer (or counter) TMR0 returns its initial value
   INTCON.T0IF = 0;   // Clear the interrupt 0 flag
   INTCON.T0IE = 1;
}