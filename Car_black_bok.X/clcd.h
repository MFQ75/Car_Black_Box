/* 
 * File:   clcd.h
 * Author: mdfai
 *
 * Created on 26 September, 2023, 9:41 AM
 */

#ifndef CLCD_H
#define	CLCD_H

#define CLCD_PORT			PORTD
#define CLCD_EN				RC2
#define CLCD_RS				RC1
#define CLCD_RW				RC0
#define CLCD_BUSY			RD7
#define PORT_DIR			TRISD7


#define HI												1
#define LO												0

#define INPUT											0xFF
#define OUTPUT											0x00

#define DATA_COMMAND									1
#define INSTRUCTION_COMMAND								0
#define _XTAL_FREQ                                      20000000
#define LINE1(x)                        				(0x80 + (x))
#define LINE2(x)										(0xC0 + (x))

#define TWO_LINE_5x8_MATRIX_8_BIT                   	clcd_write(0x38, INSTRUCTION_COMMAND)
#define CLEAR_DISP_SCREEN				                clcd_write(0x01, INSTRUCTION_COMMAND)
#define CURSOR_HOME                                     clcd_write(0x02, INSTRUCTION_COMMAND)
#define DISP_ON_AND_CURSOR_OFF                      	clcd_write(0x0C, INSTRUCTION_COMMAND)
#define EIGHT_BIT_MODE                                  0x33

void init_clcd();
void clcd_print(unsigned char *data, unsigned char addr);
void clcd_write(unsigned char byte,unsigned char control_bit);
void clcd_print_ch(unsigned char data, unsigned char addr);

#endif	/* CLCD_H */

