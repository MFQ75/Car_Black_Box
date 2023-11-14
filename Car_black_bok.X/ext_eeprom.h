/* 
 * File:   ext_eeprom.h
 * Author: mdfai
 *
 * Created on 6 October, 2023, 2:33 PM
 */

#ifndef EXT_EEPROM_H
#define	EXT_EEPROM_H

#define SLAVE_READ		0xA1
#define SLAVE_WRITE		0xA0


void write_external_eeprom(unsigned char address1,  unsigned char data);
unsigned char read_external_eeprom(unsigned char address1);

#endif	/* EXT_EEPROM_H */

