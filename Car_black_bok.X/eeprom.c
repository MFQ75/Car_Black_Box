#include "main.h"

void write_to_eeprom(unsigned char address, unsigned char data)
{
    EEADR = address;
    EEDATA = data;
    EEPGD = 0;
    CFGS = 0;
    WREN = 1;
    
    GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    
    WR = 1;
    GIE = 1;
    while(WR);
    
}

unsigned char read_to_eeprom(unsigned char address)
{
    EEADR = address;
    EEPGD = 0;
    CFGS = 0;
    RD = 1;
    
    return EEDATA;
}
