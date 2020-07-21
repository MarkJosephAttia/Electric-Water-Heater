/**
 * @file Eeprom.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the implementation for the EEPROM driver 
 * @version 0.1
 * @date 2020-07-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "Eeprom.h"
#include "I2c.h"
/* Read Command With EEPROM Address */
#define EEPROM_READ 0xA1
/* Write Command With EEPROM Address */
#define EEPROM_WRITE 0xA0
/* Second Byte Shift */
#define EEPROM_SECOND_BYTE      0x08

/**
 * @brief Initializes the EEPROM
 * 
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Eeprom_Init(void)
{
    /* Initialize The I2C Module */
    return I2C_Master_Init();
}
/**
 * @brief Writes a byte to the EEPROM
 * 
 * @param address The address to write data in
 * @param data The data to write
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Eeprom_WriteByte(Eeprom_Address_t address, uint8_t data)
{
    uint8_t ack;
    /* I2C Start */
    I2c_Start();
    do
    {
        /* I2C Write Command In The Specified Address */
        I2c_Write(&ack, EEPROM_WRITE);
    }while(ack == I2C_NO_ACK);
    /* I2C Write High Byte Of The Address */
    I2c_Write(&ack, (uint8_t)(address>>EEPROM_SECOND_BYTE));
    /* I2C Write Low Byte Of The Address */
    I2c_Write(&ack, (uint8_t)address);
    /* I2C Write The Data */
    I2c_Write(&ack, data);
    /* I2C Stop */
    I2c_Stop();
    return E_OK;
}
/**
 * @brief Reads a byte from the EEPROM
 * 
 * @param address The address to read data from
 * @param data The data to read
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Eeprom_ReadByte(Eeprom_Address_t address, uint8_t* data)
{
    uint8_t ack;
    /* I2C Start */
    I2c_Start();
    do
    {
        /* I2C Write Command In The Specified Address */
        I2c_Write(&ack, EEPROM_WRITE);
    }while(ack == I2C_NO_ACK);
    /* I2C Write High Byte Of The Address */
    I2c_Write(&ack, (uint8_t)(address>>EEPROM_SECOND_BYTE));
    /* I2C Write Low Byte Of The Address */
    I2c_Write(&ack, (uint8_t)address);
    /* I2C Start */
    I2c_Start();
    /* I2C Read Command At The Specified Address */
    I2c_Write(&ack, EEPROM_READ);
    /* I2C Write The Data */
    I2c_Read(data);
    /* I2C Send No Ack */
    I2c_NACK();
    /* I2C Stop */
    I2c_Stop();
    return E_OK;
}
