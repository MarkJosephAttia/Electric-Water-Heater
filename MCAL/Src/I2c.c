/**
 * @file I2c.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the implementation for the I2C Driver
 * @version 0.1
 * @date 2020-07-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "I2c.h"
#include "I2c_Cfg.h"
#include "Gpio.h"
/* I2C Registers */
#define I2C_SSPBUF              *(uint8_t*)0x13
#define I2C_SSPCON              *(uint8_t*)0x14
#define I2C_SSPCON2             *(uint8_t*)0x91
#define I2C_SSPADD              *(uint8_t*)0x93
#define I2C_SSPSTAT             *(uint8_t*)0x94
/* Interrupt Registers */
#define INTERRUPT_PIR1          *(uint8_t*)0x0C
/* Interrupt Masks */
#define INTERRUPT_SSPIF         0x08
#define INTERRUPT_SSPIF_CLR     0xF7
/* I2C Configurations Initial States */
#define I2C_SSPCON_CONF         0x28
#define I2C_SSPCON2_CONF        0x00
#define I2C_SSPSTAT_CONF        0x00
/* I2C Masks */
#define I2C_READABLE    0x04
#define I2C_SEN         0x01
#define I2C_PEN         0x04
#define I2C_RCEN        0x08
#define I2C_SSPCON2_EN  0x1F
#define I2C_ACK_EN      0x10
#define I2C_ACK_STAT    0x40
#define I2C_ACK_DT_CLR  0xEF
#define I2C_ACK_DT      0x00
#define I2C_NO_ACK_DT   0x10

/**
 * @brief I2C Initialization
 * 
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType I2C_Master_Init(void)
{
  /* Initialize GPIO Pins For The SDA & SCLK*/
  gpio_t gpio = {
        .pins= GPIO_PIN_3 | GPIO_PIN_4,
        .mode= GPIO_MODE_OUTPUT_PP,
        .port= GPIO_PORTC};
  /* Set The Initial Configurations */
  I2C_SSPCON = I2C_SSPCON_CONF;
  I2C_SSPCON2 = I2C_SSPCON2_CONF;
  I2C_SSPSTAT = I2C_SSPSTAT_CONF;
  /* Set The Baudrate*/
  I2C_SSPADD = ((I2C_CLK_FREQ/4)/I2C_BaudRate) - 1;
  Gpio_InitPins(&gpio);
  return E_OK;
}
/**
 * @brief I2C Start of frame
 * 
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType I2c_Start(void)
{
  /* Wait For The Bus To Be Ready */
  while ((I2C_SSPSTAT & I2C_READABLE) | (I2C_SSPCON2 & I2C_SSPCON2_EN));
  /* Send The Start Bit */
  I2C_SSPCON2 |= I2C_SEN;
  return E_OK;
}
/**
 * @brief I2C Stop of frame
 * 
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType I2c_Stop(void)
{
  /* Wait For The Bus To Be Ready */
  while ((I2C_SSPSTAT & I2C_READABLE) | (I2C_SSPCON2 & I2C_SSPCON2_EN));
  /* Send The Stop Bit */
  I2C_SSPCON2 |= I2C_PEN;
  return E_OK;
}
/**
 * @brief I2C Send Ack
 * 
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType I2c_ACK(void)
{
  /* Wait For The Bus To Be Ready */
  while ((I2C_SSPSTAT & I2C_READABLE) | (I2C_SSPCON2 & I2C_SSPCON2_EN));
  /* Clears The Ack Bit */
  I2C_SSPCON2 &= I2C_ACK_DT_CLR;
  /* Sets The Ack */
  I2C_SSPCON2 |= I2C_ACK_DT;
  /* Trigger The Ack Transmission */
  I2C_SSPCON2 |= I2C_ACK_EN;
  return E_OK;
}
/**
 * @brief I2C Send No Ack
 * 
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType I2c_NACK(void)
{
  /* Wait For The Bus To Be Ready */
  while ((I2C_SSPSTAT & I2C_READABLE) | (I2C_SSPCON2 & I2C_SSPCON2_EN));
  /* Clears The Ack Bit */
  I2C_SSPCON2 &= I2C_ACK_DT_CLR;
  /* Sets The No Ack */
  I2C_SSPCON2 |= I2C_NO_ACK_DT;
  /* Trigger The Ack Transmission */
  I2C_SSPCON2 |= I2C_ACK_EN;
  return E_OK;
}
/**
 * @brief I2C Reads A Byte of Data
 * 
 * @param data The data to be stored
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType I2c_Read(uint8_t* data)
{
  /* Wait For The Bus To Be Ready */
  while ((I2C_SSPSTAT & I2C_READABLE) | (I2C_SSPCON2 & I2C_SSPCON2_EN));
  /* Read Bit Set */
  I2C_SSPCON2 |= I2C_RCEN;
  /* Wait For The Flag To Be Raised */
  while(!(INTERRUPT_PIR1 & INTERRUPT_SSPIF));
  /* Clears The Read Interrupt Flag */
  INTERRUPT_PIR1 &= INTERRUPT_SSPIF_CLR;
  /* Wait For The Read To Be Finished */
  while ((I2C_SSPSTAT & I2C_READABLE) | (I2C_SSPCON2 & I2C_SSPCON2_EN));
  /* Saves The Data */
  *data = I2C_SSPBUF;
  return E_OK;
}
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
Std_ReturnType I2c_Write(uint8_t* ack, uint8_t data)
{
  /* Wait For The Bus To Be Ready */
  while ((I2C_SSPSTAT & I2C_READABLE) | (I2C_SSPCON2 & I2C_SSPCON2_EN));
  I2C_SSPBUF = data;
  /* Wait For The Write To Be Done */
  while ((I2C_SSPSTAT & I2C_READABLE) | (I2C_SSPCON2 & I2C_SSPCON2_EN));
  /* Saves The Ack */
  *ack = !(I2C_SSPCON2 & I2C_ACK_STAT);
  return E_OK;
}