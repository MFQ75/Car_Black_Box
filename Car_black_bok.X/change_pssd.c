#include "main.h"
char i,pssd[5],r_pssd[5],flag = 1;
int time6;
unsigned char change_pssd(unsigned char key)
{        
    clcd_print("Enter Password",LINE1(0));
    if(i < 4 && flag)
    {
        if(++time6 < 150)
            clcd_print_ch('_',LINE2(6+i));
        else if(time6 == 300)
            time6 = 0;
        else
            clcd_print_ch(' ',LINE2(6+i));
        if(key == 11)
        {
            clcd_print_ch('*',LINE2(6+i));
            pssd[i++] = '0';
        }
        else if(key == 12)
        {
            clcd_print_ch('*',LINE2(6+i));
            pssd[i++] = '1';
        }
        if(i == 4)
        {
            CLEAR_DISP_SCREEN;
            __delay_us(500);
            time6 = 0;
            i = 0;
            flag = 0;
        }
    }
    else if(i < 4)
    {
        if(++time6 < 150)
            clcd_print_ch('_',LINE2(6+i));
        else if(time6 == 300)
            time6 = 0;
        else
            clcd_print_ch(' ',LINE2(6+i));
        clcd_print("Renter Password",LINE1(0));
        if(key == 11)
        {
            clcd_print_ch('*',LINE2(6+i));
            r_pssd[i++] = '0';
        }
        else if(key == 12)
        {
            clcd_print_ch('*',LINE2(6+i));
            r_pssd[i++] = '1';
        }
    }
    else
    {
        i = 0;
        flag = 1;
        CLEAR_DISP_SCREEN;
        __delay_us(500);
        if(!strncmp(pssd,r_pssd,4))
        {
            clcd_print("Password Changed",LINE1(0));
            for(int i=161; i<165 ; i++)
            {
                write_to_eeprom(i,pssd[i-161]);
            }
            __delay_ms(500);
            return DASHBOARD;
        }
        else
        {
            clcd_print("Pssd Not Match",LINE1(0));
        }
        __delay_ms(500);
    }
    return CHANGE_PSSD;
}
