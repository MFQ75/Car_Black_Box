#include "main.h"
extern char event_flag;
unsigned int long_press;
unsigned char view_log(unsigned char key)
{
    static unsigned char i;
    if(key == 12)
    {
        long_press = 0;
        while(read_key(LEVEL) == 12)
        {
            if(++long_press == 50000)
            {
                i = 0;
                CLEAR_DISP_SCREEN;
                __delay_us(500);
                return DASHBOARD;
            }
        }
        if(i < event_flag)
        i++;
    }
    else if(key == 11 && i > 0)
    {
        i--;
    }
    if(event_flag)
    {
        char ch[16];
        for(int j=0; j<16; j++)
        {
            ch[j] = read_external_eeprom((i*16)+j);
        }
        clcd_print("My logs",LINE1(5));
        clcd_print(ch,LINE2(0));
    }
    else
    {
        clcd_print("No logs",LINE1(5));
    }
    return VIEW_LOG;
}

unsigned char clear_log()
{
    if(event_flag)
    {
        event_flag = 0;
        clcd_print("All logs",LINE1(5));
        clcd_print("Cleared",LINE2(6));
    }
    else
    {
        clcd_print("No logs",LINE1(5));
    }
    __delay_ms(1000);
    CLEAR_DISP_SCREEN;
    __delay_us(500);
    return DASHBOARD;
}
