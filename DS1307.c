// Read time from RTC
void readTime (char  *sec, char *min, char *hr, char *week_day, char *day, char *mn, char *year) {
  I2C1_Start();
  I2C1_Wr(0xD0);
  I2C1_Wr(0);
  I2C1_Repeated_Start();
  I2C1_Wr(0xD1);
  *sec = I2C1_Rd(1);
  *min = I2C1_Rd(1);
  *hr = I2C1_Rd(1);
  *week_day = I2C1_Rd(1);
  *day = I2C1_Rd(1);
  *mn = I2C1_Rd(1);
  *year = I2C1_Rd(0);
  I2C1_Stop();
  
  // Transform time
  *sec  =  ((*sec & 0x70) >> 4)*10 + (*sec & 0x0F);
  *min  =  ((*min & 0xF0) >> 4)*10 + (*min & 0x0F);
  *hr   =  ((*hr & 0x30) >> 4)*10 + (*hr & 0x0F);
  *week_day = (*week_day & 0x07);
  *day  =  ((*day & 0xF0) >> 4)*10 + (*day & 0x0F);
  *mn   =  ((*mn & 0x10) >> 4)*10 + (*mn & 0x0F);
  *year =  ((*year & 0xF0)>>4)*10+(*year & 0x0F);
}

void setTime (char  sec, char min, char hr, char week_day, char day, char mn, char year) {
    char temp;
    I2C1_Start();              // issue I2C start signal
    I2C1_Wr(0xD0);             // send byte via I2C  (device address + W)
    I2C1_Wr(0x00);             // send byte (address of EEPROM location)
    temp = ((sec / 10) << 4) + (sec % 10);
    I2C1_Wr(temp);
    temp = ((min / 10) << 4) + (min % 10);
    I2C1_Wr(temp);
    temp = ((hr / 10) << 4) + (hr % 10);
    I2C1_Wr(temp);
    temp = ((week_day / 10) << 4) + (week_day % 10);
    I2C1_Wr(temp);
    temp = ((day / 10) << 4) + (day % 10);
    I2C1_Wr(temp);
    temp = ((mn / 10) << 4) + (mn % 10);
    I2C1_Wr(temp);
    temp = ((year / 10) << 4) + (year % 10);
    I2C1_Wr(temp);
    I2C1_Stop();
}

void resetTime () {
    char i;
    
    I2C1_Start();              // issue I2C start signal
    I2C1_Wr(0xD0);             // send byte via I2C  (device address + W)
    I2C1_Wr(0x00);             // send byte (address of EEPROM location)
    for (i = 0; i < 7; i++)
        I2C1_Wr(0x00);         // send data (data to be written)
    I2C1_Stop();               // issue I2C stop signal
}