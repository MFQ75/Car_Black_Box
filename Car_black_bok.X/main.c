/*
 * File:   main.c
 * Author: Md Faizan Quamar
 *
 * Created on 26 September, 2023, 9:42 AM
 */


#include "main.h"
#include "rtc.h"
char event_flag = 1;
void init_config()
{
    /*Intializing the periferrel*/
    init_uart();
    init_clcd();
    init_matrix(); 
    init_adc();
    init_i2c();
    init_ds1307();
}
void main(void) {
    init_config();
    unsigned char ev[][3]={"ON","GR","GN","G1","G2","G3","G4","C "},key,i = 0,speed = 0,s_flag = DASHBOARD,l,long_press=0,flag=0,key1;
    log_event(ev[0],speed);
    /*storing the password in eeprom*/
    for(char i=161; i<165 ; i++)
    {
        write_to_eeprom(i,'0');
    }  
    while(1)
    {
        speed = read_adc(4)/10.33;  
        key = read_key(EDGE);
        for(int i = 1000; i--; );  //ignoring the bouncing effect
        if(key == 1)
        {
            if(event_flag != 10)
                event_flag++;
            i = 7;
            log_event(ev[i],speed);
        }
        else if(key == 2 && i != 6)
        {
            if(event_flag != 10)
                event_flag++;
            ++i; 
            log_event(ev[i],speed);
        }
        else if(key == 3 && i != 1 && i != 0)
        {
            if(event_flag != 10)
                event_flag++;
            --i;   
            log_event(ev[i],speed);
        }
        else if((key == 11 || key == 12) && s_flag == DASHBOARD)
        {
            CLEAR_DISP_SCREEN;
            __delay_us(500);
            s_flag = PASSWORD;
            key = 0;
        }
        
        switch(s_flag)
        {
            case DASHBOARD    : display(ev[i],speed);
                                break;
            case PASSWORD     : s_flag = check_pssd(key);
                                break;
            case LOGIN_SCREEN : s_flag = login_screen(key);
                                if(s_flag == SET_TIME)
                                    get_time();
                                break;
            case VIEW_LOG     : s_flag = view_log(key);
                                break;
            case DOWNLOAD_LOG : download_log();
                                s_flag = DASHBOARD;
                                break;
            case CLEAR_LOG    : s_flag = clear_log();
                                break;
            case SET_TIME     : clcd_print("  Time    EV  SP",LINE1(0));
                                clcd_print(ev[i],LINE2(10));
                                clcd_print_ch((speed/10)+'0',LINE2(14));
                                clcd_print_ch((speed%10)+'0',LINE2(15));
                                s_flag = set_time(key);
                                break;
            case CHANGE_PSSD  : s_flag = change_pssd(key);       
        }
    }
    return;
}
