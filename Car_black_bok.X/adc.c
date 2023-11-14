#include "main.h"
void init_adc()
{
    ADON = 1;
    
    ADCON1 = 0x0A;
    
    ADCON2 = 0x94;
    
}

unsigned int read_adc(unsigned char channel)
{
    ADCON0 = (ADCON0 & 0xC3) | (channel << 2);
    
    GO = 1;
    while(GO);
    
    return ((ADRESH & 0x03)<<8 | ADRESL);
}
