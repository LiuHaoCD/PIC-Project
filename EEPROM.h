/* 
 * File:   EEPROM.h
 * Author: charl
 *
 * Created on 2019?9?10?, ??5:30
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif
    

#define  uint8_t unsigned char
void WriteByte(uint8_t addr,uint8_t * pdata);
void ReadByte(uint8_t   addr,uint8_t * pdata);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

