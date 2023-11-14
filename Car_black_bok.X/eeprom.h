/* 
 * File:   eeprom.h
 * Author: mdfai
 *
 * Created on 1 October, 2023, 11:33 AM
 */

#ifndef EEPROM_H
#define	EEPROM_H

void write_to_eeprom(unsigned char address, unsigned char data);
unsigned char read_to_eeprom(unsigned char address);

#endif	/* EEPROM_H */

