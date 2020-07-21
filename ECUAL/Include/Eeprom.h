/**
 * @file Eeprom.h
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the user interface for the EEPROM driver 
 * @version 0.1
 * @date 2020-07-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef EEPROM_H_
#define EEPROM_H_

typedef uint16_t Eeprom_Address_t;

/**
 * @brief Initializes the EEPROM
 * 
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Eeprom_Init(void);

/**
 * @brief Writes a byte to the EEPROM
 * 
 * @param address The address to write data in
 * @param data The data to write
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Eeprom_WriteByte(Eeprom_Address_t address, uint8_t data);

/**
 * @brief Reads a byte from the EEPROM
 * 
 * @param address The address to read data from
 * @param data The data to read
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Eeprom_ReadByte(Eeprom_Address_t address, uint8_t* data);

#endif