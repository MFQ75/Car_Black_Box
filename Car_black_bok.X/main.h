/* 
 * File:   main.h
 * Author: mdfai
 *
 * Created on 26 September, 2023, 9:41 AM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include <string.h>
#include "clcd.h"
#include "matrix_keypad.h"
#include "adc.h"
#include "black_box.h"
#include "eeprom.h"
#include "i2c.h"
#include "ext_eeprom.h"
#include "log.h"
#include "uart.h"

unsigned char change_pssd(unsigned char key);

#endif	/* MAIN_H */

