// Common cathode
char digitsValue[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00};
char segments[] = {0b00000001, 0b00000010, 0b00000100, 0b00001000};
char displayValue[4];

void displayAtPosition (char position, char value) {
    displayValue[position] = value;
}

void display () {
    char i;
    
    PORTD = 0;
    for (i = 0; i < 4; i++) {
        PORTB = digitsValue[displayValue[i]];
        PORTD = segments[i];
        delay_ms(1);
        PORTD = 0;
    }
}