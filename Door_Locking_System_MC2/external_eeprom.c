 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: Source file for the External EEPROM Memory
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/
#include "external_eeprom.h"

#include "i2c.h"

void EEPROM_init(void)
{
	/* just initialize the I2C(TWI) module inside the MC */
	TWI_init();
}

uint8 EEPROM_writeString(uint16 u16addr, const uint8 *Str)
{
    uint8 i = 0;
    while(Str[i] != '\0')
    {
        EEPROM_writeByte(u16addr++,Str[i++]);
        _delay_ms(100);
    }
    EEPROM_writeByte(u16addr,'\0');
    return SUCCESS;
}

uint8 EEPROM_readString(uint16 u16addr, uint8 *Str)
{

    EEPROM_readByte(u16addr++,Str);
    uint8 i = 0;
    while(*Str != '\0')
    {
        Str++;
        EEPROM_readByte(u16addr++,Str);
        _delay_ms(100);
    }
    *(Str+i) = '\0';
    return SUCCESS;
}

uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TW_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */ //0x0311
    //0000 0011 0001 0001 address ely b3teeno
    //     1098               
    //0000 0111 0000 0000 mask
    //0000 0000 0000 1110 or
    //0000 0000 1010 0000
    //0000 0000 1010 xxx0
    TWI_write((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TW_MT_SLA_W_ACK)
        return ERROR; 
		 
    /* Send the required memory location address */
    TWI_write((uint8)(u16addr));
    if (TWI_getStatus() != TW_MT_DATA_ACK)
        return ERROR;
		
    /* write byte to eeprom */
    TWI_write(u8data);
    if (TWI_getStatus() != TW_MT_DATA_ACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_stop();
	
    return SUCCESS;
}

uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TW_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_write((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TW_MT_SLA_W_ACK)
        return ERROR;
		
    /* Send the required memory location address */
    TWI_write((uint8)(u16addr));
    if (TWI_getStatus() != TW_MT_DATA_ACK)
        return ERROR;
		
    /* Send the Repeated Start Bit */
    TWI_start();
    if (TWI_getStatus() != TW_REP_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    TWI_write((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
    if (TWI_getStatus() != TW_MT_SLA_R_ACK)
        return ERROR;

    /* Read Byte from Memory without send ACK */
    *u8data = TWI_readWithNACK();
    if (TWI_getStatus() != TW_MR_DATA_NACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_stop();
    return SUCCESS;
}
