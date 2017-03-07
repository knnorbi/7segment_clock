// Common cathode
char digitsValue[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00, 0x63, 0x39, 0x54, 0x5C};
char segments[] = {0b00000001, 0b00000010, 0b00000100, 0b00001000};
char displayValue[4];
char dots[] = {0, 0, 0, 0};
bit colon;

void setDisplayTemp (signed char temp, char outTemp) {
    char i;

    if (abs(temp) > 99) {
       displayValue[0] = 13;
       displayValue[1] = 14;
       displayValue[2] = 10;
       displayValue[3] = 10;
    }
    else {
        displayValue[0] = abs(temp) / 10;
        displayValue[1] = abs(temp) % 10;
        displayValue[2] = 11;
        displayValue[3] = 12;
    }

    if(outTemp != 0)
        colon = 1;
    else
        colon = 0;
        
    for (i = 0; i < 4; i ++) {
        if (temp < 0) {
            if (i < 2)
               dots[i] = 1;
            else
                dots[i] = 0;
        }
        else
            dots[i] = 0;
    }
}

void setDisplayTime (char hour, char minute, char second) {
    char i;
    // Set all dots off
    for (i = 0; i < 4; i++)
        dots[i] = 0;
    // Set digits
    displayValue[0] = hour / 10;
    displayValue[1] = hour % 10;
    displayValue[2] = minute / 10;
    displayValue[3] = minute % 10;
    // Blink colon
    if (second % 2 == 0)
        colon = 0;
    else
        colon = 1;
}

void setAtPosition (char position, char value) {
    displayValue[position] = value;
}

void display () {
    char i;
    
    RE0_bit = colon;
    PORTD = 0;
    for (i = 0; i < 4; i++) {
        PORTB = digitsValue[displayValue[i]];
        if (dots[i] != 0)
            PORTB += 128;
        PORTD = segments[i];
        delay_ms(1);
        PORTD = 0;
    }
}