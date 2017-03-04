#include "seven_segment.h"
#include "DS1307.h"

unsigned char second, minute, hour, week_day, day, month, year;

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
}

void main() {
    init();
    //resetTime();
    //setTime(0, 24, 21, 0, 0, 0, 0);
    
    while(1) {
        readTime(&second, &minute, &hour, &week_day, &day, &month, &year);
        setDisplayTime(hour, minute, second);
        display();
    }
}