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
}