#include "main.h"

void init_matrix()
{
    ADCON1 = 0x0F;
    
    TRISB = 0x1E;
    
    RBPU = 0;
    
    PORTB |= 0xE0;
    
}
unsigned char scan_key()
{
    ROW1 = 0;
    ROW2 = 1;
    ROW3 = 1;
    if(COL1 == 0)
        return 1;
    ROW1 = 1;
    ROW2 = 0;
    ROW3 = 1;
    if(COL1 == 0)
        return 2;
    else if(COL4 == 0)
        return 11;
    ROW1 = 1;
    ROW2 = 1;
    ROW3 = 0;
    ROW3 = 0;
    if(COL1 == 0)
        return 3;
     else if(COL4 == 0)
        return 12;
    return 0xFF;
}

unsigned char read_key(unsigned char state)
{
    static unsigned char once = 1;
    unsigned char key = scan_key();
    if(state == EDGE)
    {
        if(key != 0xFF && once)
        {
            once = 0;
            return key;
        }
        else if(key == 0xFF)
            once = 1;
    }
    else if(state == LEVEL)
    {
        return key;
    }
    return 0xFF;
}
