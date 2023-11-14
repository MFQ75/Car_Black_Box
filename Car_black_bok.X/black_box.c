#include "main.h"
#include "rtc.h"
unsigned char sec;
extern char event_flag;
char time1,k = -1;
unsigned char time[9] = "00:00:00",h,sec,min;
/*fuction to display on the dashpoard screen*/

void read_rtc(unsigned char *time)
{
    time[0] = ((read_ds1307(HOUR_ADDR)>> 4) & 0x03) + '0';
    time[1] = (read_ds1307(HOUR_ADDR) & 0x0F) + '0';
    time[2] = ':';
    time[3] = ((read_ds1307(MIN_ADDR) >> 4) & 0x07) + '0';
    time[4] = (read_ds1307(MIN_ADDR) & 0x0F) + '0';
    time[5] = ':';
    time[6] = ((read_ds1307(SEC_ADDR)>> 4)& 0x07) + '0';
    time[7] = (read_ds1307(SEC_ADDR)&0x0F) + '0';
    time[8] = '\0'; 
    clcd_print(time,LINE2(0));
}

void display(unsigned char *event,unsigned char speed)
{
    clcd_print("  Time    EV  SP",LINE1(0));
    read_rtc(time); 
    clcd_print(event,LINE2(10));
    clcd_print_ch((speed/10)+'0',LINE2(14));
    clcd_print_ch((speed%10)+'0',LINE2(15));
}

/*function defination to check the password*/
unsigned char check_pssd(unsigned char key)
{
    static unsigned char pssd[5],attempt = 3,i = 0,t;
    if(attempt)
    {
        //cursor blinking
        if(++t < 125)
            clcd_print_ch('_',LINE2(6+i));
        else if(t == 250)
        {
            t = 0;
            time1++;            
        }
        else
            clcd_print_ch(' ',LINE2(6+i));
        //taking the user input
        clcd_print("Enter Password",LINE1(0));
        if(key == 11)
        {
           clcd_print_ch('*',LINE2(6+i));
           pssd[i++] = '0';
           time1 = 0;
        }
        else if(key == 12)
        {
            clcd_print_ch('*',LINE2(6+i));
            pssd[i++] = '1';
            time1 = 0;
        }
    }
    else
    {
        time1 = 0;
        sec = 120;
        CLEAR_DISP_SCREEN;
        /*blocking the user for 2 mins*/
        clcd_print("You are block",LINE1(0));
        clcd_print("for 120sec... ",LINE2(0));
        while(sec)
        {
            clcd_print_ch(sec/100 + '0', LINE2(4));
            clcd_print_ch((sec/10)%10 + '0', LINE2(5));
            clcd_print_ch(sec%10 + '0', LINE2(6));
            for(unsigned long i=300000; i--; );
            sec--;
        }
        attempt = 3;
        CLEAR_DISP_SCREEN;
    }
    if(i == 4)
    {
        /*reading the pssd from eeprom*/
        unsigned char s_pssd[5];
        for(char j=161; j<165 ; j++)
        {
            s_pssd[j-161] = read_to_eeprom(j); 
        }
        i = 0;
        if(--attempt)
        {
            //checking the password is matching or not
            if(!strncmp(s_pssd,pssd,4))           
            {
                attempt = 3;
                CLEAR_DISP_SCREEN;
                __delay_us(500);
                time1 = 0;
                return LOGIN_SCREEN;
            }
            else
            {
                CLEAR_DISP_SCREEN;
                clcd_print("Login Failed",LINE1(0));
                clcd_print_ch(attempt+'0',LINE2(0));
                clcd_print("attempt rem",LINE2(2));
                __delay_ms(1000);
                CLEAR_DISP_SCREEN;
            }
        }    
    }
    else if(time1 == 5)
    {
        i = 0;
        time1 = 0;
        return DASHBOARD;
    }
    return PASSWORD;
}

unsigned char login_screen(unsigned char key)
{
    char arr[][17] = {"View Log    ","Download Log ","Clear log    ","set time    ","change passd "};
    static char i,flag = 0;
    if(flag)
    {
        i = 0;
        flag = 0;
    }
    static unsigned int long_press;
    long_press = 0;
    if(key == 12)
    {
        while(read_key(LEVEL) == 12)
        {
            if(++long_press == 50000)
            {
                CLEAR_DISP_SCREEN;
                __delay_us(500);
                i = 0;
                return DASHBOARD;
            }
        }
        if(i < 4)
        i++;
    }
    else if(key == 11)
    {
        while(read_key(LEVEL) == 11)
        {
            if(++long_press == 50000)
            {
                CLEAR_DISP_SCREEN;
                __delay_us(500);
                flag = 1;
                return (i+4);
            }
        }
        if(i > 0)
        i--;
    }
    if(i == 0)
    {
        clcd_print_ch(' ',LINE2(0));
        clcd_print(arr[i],LINE1(3));
        clcd_print(arr[i+1],LINE2(3));
        clcd_print_ch('*',LINE1(0));
    }
    else 
    {
        clcd_print_ch(' ',LINE1(0));
        clcd_print(arr[i-1],LINE1(3));
        clcd_print(arr[i],LINE2(3));
        clcd_print_ch('*',LINE2(0));
    }
    return LOGIN_SCREEN;
}

void log_event(unsigned char *event,unsigned char speed)
{
    char log[16];
    char i,j;
    strncpy(log,time,8);
    log[8] = ' ';
    log[9] = ' ';
    log[10] = event[0];
    log[11] = event[1];
    log[12] = ' ';
    log[13] = ' ';
    log[14] = speed/10 + '0';
    log[15] = speed%10 + '0';
    k++;
    if(k == 10)
    {
        k = 0;
    }
    for(unsigned char i = 0; i < 16 ; i++)
    {
        write_external_eeprom((k*16) + i,log[i]);
    }
}
void get_time()
{
    h = ((time[0] - '0')*10) + time[1] - '0';
    min = ((time[3] - '0')*10) + time[4] - '0';
    sec = ((time[6] - '0')*10) + time[7] - '0';
}

unsigned char set_time(unsigned char key)
{
    char num;
    static unsigned int long_press,t;
    static char j = 0;
    if(key == 12)
    {
        t=0;
        long_press = 0;
        while(read_key(LEVEL) == 12)
        {
            if(++long_press == 50000)
            return DASHBOARD;
        }
        if(j!= 2)
        j++;
        else
            j=0;
    }
    else if(key == 11)
    {
        long_press = 0;
        while(read_key(LEVEL) == 11)
        {
            if(++long_press == 50000)
            {
                num = ((sec/10)<<4) | (sec%10);
                write_ds1307(SEC_ADDR,num);
                num = ((min/10)<<4) | (min%10);
                write_ds1307(MIN_ADDR,num);
                num = ((h/10)<<4) | (h%10);
                write_ds1307(HOUR_ADDR,num);
                return DASHBOARD;
            }
        }
    }
    if(j == 0)
    {
        if(key == 11)
        if(++sec == 60)
        sec = 0;
        if(++t < 150)
        {
            clcd_print_ch(' ',LINE2(6));
            clcd_print_ch(' ',LINE2(7));
        }
        else if(t == 300)
            t = 0;
        else
        {
            clcd_print_ch(sec/10 + '0',LINE2(6));
            clcd_print_ch(sec%10 + '0',LINE2(7));
        }
        
    }
    else if(j == 1)
    {
        if(key == 11)
        if(++min == 60)
           min = 0;
        if(++t < 150)
        {
            clcd_print_ch(' ',LINE2(3));
            clcd_print_ch(' ',LINE2(4));
        }
        else if(t == 300)
            t = 0;
        else
        {
            clcd_print_ch(min/10 + '0',LINE2(3));
            clcd_print_ch(min%10 + '0',LINE2(4));
        }
    }
    else if(j == 2)
    {
        if(key == 11)
        if(++h == 24)
           h = 0;
        if(++t < 150)
        {
            clcd_print_ch(' ',LINE2(0));
            clcd_print_ch(' ',LINE2(1));
        }
        else if(t == 300)
            t = 0;
        else
        {
            clcd_print_ch(h/10 + '0',LINE2(0));
            clcd_print_ch(h%10 + '0',LINE2(1));
        }
    }    
    
    if(j != 2)
    {
        clcd_print_ch(h/10 + '0',LINE2(0));
        clcd_print_ch(h%10 + '0',LINE2(1));
    }
    clcd_print_ch(':',LINE2(2));
    if(j != 1)
    {
        clcd_print_ch(min/10 + '0',LINE2(3));
        clcd_print_ch(min%10 + '0',LINE2(4));
    }
    clcd_print_ch(':',LINE2(5));
    if(j != 0)
    {
        clcd_print_ch(sec/10 + '0',LINE2(6));
        clcd_print_ch(sec%10 + '0',LINE2(7));
    }
    return SET_TIME;
}



