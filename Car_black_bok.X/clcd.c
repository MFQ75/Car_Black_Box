#include "main.h"

void init_clcd()
{
   /* Set PortD as output port for CLCD data */
	TRISD = 0x00;
	/* Set PortC as output port for CLCD control */
	TRISC = TRISC & 0xF8;

	CLCD_RW = LO;

	
     /* Startup Time for the CLCD controller */
    __delay_ms(30);
    
    /* The CLCD Startup Sequence */
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND	);
    __delay_us(4100);
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND	);
    __delay_us(100);
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND	);
    __delay_us(1); 
    
    CURSOR_HOME;
    __delay_us(100);
    TWO_LINE_5x8_MATRIX_8_BIT;
    __delay_us(100);
    CLEAR_DISP_SCREEN;
    __delay_us(500);
    DISP_ON_AND_CURSOR_OFF;
    __delay_us(100);
}
void clcd_write(unsigned char byte,unsigned char control_bit)
{
    RC1 = control_bit;
    PORTD = byte;
    /*enabling the enable bit*/
    RC2 = 1;
    /*disabling the enable bit*/
    RC2 = 0;
    
    TRISD7 = 1;
    RC0 = 1;
    RC1 = INSTRUCTION_COMMAND;
    
    do
    {
        RC2 = 1;
        RC2 = 0;
    }while(RD7);
    
    RC0 = 0;
    TRISD7 = 0;
}

void clcd_print(unsigned char *data, unsigned char addr)
{
    clcd_write(addr,INSTRUCTION_COMMAND);
    while(*data)
    {
       clcd_write(*data++,DATA_COMMAND); 
    }
}

void clcd_print_ch(unsigned char data, unsigned char addr)
{
    clcd_write(addr,INSTRUCTION_COMMAND);
    clcd_write(data,DATA_COMMAND);
}

