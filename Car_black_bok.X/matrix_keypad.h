/* 
 * File:   matrix_keypad.h
 * Author: mdfai
 *
 * Created on 26 September, 2023, 12:01 PM
 */

#ifndef MATRIX_KEYPAD_H
#define	MATRIX_KEYPAD_H

#define ROW3					PORTBbits.RB7
#define ROW2					PORTBbits.RB6
#define ROW1					PORTBbits.RB5
#define COL4					PORTBbits.RB4
#define COL3					PORTBbits.RB3
#define COL2					PORTBbits.RB2
#define COL1					PORTBbits.RB1
#define LEVEL                    1
#define EDGE                     2
void init_matrix();
unsigned char read_key(unsigned char);
unsigned char scan_key();

#endif	/* MATRIX_KEYPAD_H */

