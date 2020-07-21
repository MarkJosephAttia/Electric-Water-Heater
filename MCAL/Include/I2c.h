/**
 * @file I2c.h
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the user interface for the I2C Driver
 * @version 0.1
 * @date 2020-07-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef I2C_H_
#define I2C_H_

#define I2C_NO_ACK      0
#define I2C_ACK         !I2C_NO_ACK

/**
 * @brief I2C Initialization
 * 
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType I2C_Master_Init(void);
/**
 * @brief I2C Start of frame
 * 
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType I2c_Start(void);
/**
 * @brief I2C Stop of frame
 * 
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType I2c_Stop(void);
/**
 * @brief I2C Send Ack
 * 
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType I2c_ACK(void);
/**
 * @brief I2C Send No Ack
 * 
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType I2c_NACK(void);
/**
 * @brief I2C Reads A Byte of Data
 * 
 * @param data The data to be stored
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType I2c_Read(uint8_t* data);
/**
 * @brief I2C Writes A Byte
 * 
 * @param ack The Ack Returned
 *            @arg I2C_ACK
 *            @arg I2C_NO_ACK
 * @param data The Data to Be Written
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType I2c_Write(uint8_t* ack, uint8_t data);

#endif