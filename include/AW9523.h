/**
 * @file AW9523.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#ifndef AW9523_H
#define AW9523_H

#include <stdint.h>
#include <stdbool.h>

// ----------------------------------------------- Global Defines ------------------------------------------------ //

#define AW9523_BASE_ADDR  0x58   ///< AW9523 default address, the actual address is determined based on pin tying

// ------------------------------------------------ Register Defintions ------------------------------------------- //

/// @brief 
typedef enum AW9523REGISTER {

    AW9523_REG_OUTPUT_P0    = 0x02, ///< GPIO Output Register for Port 0
    AW9523_REG_OUTPUT_P1    = 0x03, ///< GPIO Output Register for Port 1
    AW9523_REG_CONFIG_P0    = 0x04, ///< GPIO Configuration Register for Port 0
    AW9523_REG_CONFIG_P1    = 0x05, ///< GPIO Configuration Register for Port 1
    AW9523_REG_INT_PO       = 0x06, ///< Interrupt enable/disable register for Port 0 interrupts
    AW9523_REG_INT_P1       = 0x07, ///< Interrupt enable/disable register for Port 1 Interrupts
    AW9523_REG_CTRL         = 0x11, ///< Global Config and Control Register
    AW9523_REG_MODE_P0      = 0x12, ///< Pin Mode Register for Port 0, select between LED and GPIO Modes
    AW9523_REG_MODE_P1      = 0x13, ///< Pin Mode Regsiter for Port 1, select between LED and GPIO Modes

    // Read Only Registers

    AW9523_REG_INPUT_P0     = 0x00, ///< The GPIO Input value for port 0
    AW9523_REG_INPUT_P1     = 0x01, ///< The GPIO Input Vallue for Port 1
    AW9523_REG_ID           = 0x10, ///< The Device ID Register

    // Write Only Registers`

    AW9523_REG_DIM_0        = 0x20, ///< The Zeroth LED Current Level (0 - Imax)
    AW9523_REG_DIM_1        = 0x21, ///< The First LED Current Level (0 - Imax)
    AW9523_REG_DIM_2        = 0x22, ///< The Second LED Current Level (0 - Imax)
    AW9523_REG_DIM_3        = 0x23, ///< The Third LED Current Level (0 - Imax)
    AW9523_REG_DIM_4        = 0x24, ///< The Fourth LED Current Level (0 - Imax)
    AW9523_REG_DIM_5        = 0x25, ///< The Fifth LED Current Level (0 - Imax)
    AW9523_REG_DIM_6        = 0x26, ///< The Sixth LED Current Level (0 - Imax)
    AW9523_REG_DIM_7        = 0x27, ///< The Seventh LED Current Level (0 - Imax)
    AW9523_REG_DIM_8        = 0x28, ///< The Eighth LED Current Level (0 - Imax)
    AW9523_REG_DIM_9        = 0x29, ///< The Ninth LED Current Level (0 - Imax)
    AW9523_REG_DIM_10       = 0x2A, ///< The Tenth LED Current Level (0 - Imax)
    AW9523_REG_DIM_11       = 0x2B, ///< The Eleventh LED Current Level (0 - Imax)
    AW9523_REG_DIM_12       = 0x2C, ///< The Twelveth LED Current Level (0 - Imax)
    AW9523_REG_DIM_13       = 0x2D, ///< The Thirteenth LED Current Level (0 - Imax)
    AW9523_REG_DIM_14       = 0x2E, ///< The Fourteenth LED Current Level (0 - Imax)
    AW9523_REG_DIM_15       = 0x2F, ///< The Fifteenth LED Current Level (0 - Imax)

    AW9523_REG_RST          = 0x7F  ///< Software Reset register, 0 to reset

} AW9523Register;

// ----------------------------------------------- Port Definitions ------------------------------------------------ //

/// @brief The GPIO Ports for the Device
typedef enum AW9523PORT {

    AW9523_PORT_0 = 0,  ///< Port Zero
    AW9523_PORT_1 = 1   ///< Port One

} AW9523Port;

// ----------------------------------------------- LED Enumerations ------------------------------------------------- //

/// @brief The LED Number Mapping to the GPIO Port and Pin
typedef enum AW9523LED {

    AW9523_LED_P0_0 = 0x4,  ///< Port 0 Pin 0 is LED 4
    AW9523_LED_P0_1 = 0x5,  ///< Port 0 Pin 1 is LED 5
    AW9523_LED_P0_2 = 0x6,  ///< Port 0 Pin 2 is LED 6
    AW9523_LED_P0_3 = 0x7,  ///< Port 0 Pin 3 is LED 7
    AW9523_LED_P0_4 = 0x8,  ///< Port 0 Pin 4 is LED 8
    AW9523_LED_P0_5 = 0x9,  ///< Port 0 Pin 5 is LED 9
    AW9523_LED_P0_6 = 0xA,  ///< Port 0 Pin 6 is LED 10
    AW9523_LED_P0_7 = 0xB,  ///< Port 0 Pin 7 is LED 11

    AW9523_LED_P1_0 = 0x0,  ///< Port 1 Pin 0 is LED 0
    AW9523_LED_P1_1 = 0x1,  ///< Port 1 Pin 1 is LED 1
    AW9523_LED_P1_2 = 0x2,  ///< Port 1 Pin 2 is LED 2
    AW9523_LED_P1_3 = 0x3,  ///< Port 1 Pin 3 is LED 3
    AW9523_LED_P1_4 = 0xC,  ///< Port 1 Pin 4 is LED 12
    AW9523_LED_P1_5 = 0xD,  ///< Port 1 Pin 5 is LED 13
    AW9523_LED_P1_6 = 0xE,  ///< Port 1 Pin 6 is LED 14
    AW9523_LED_P1_7 = 0xF   ///< Port 1 Pin 7 is LED 15

} AW9523LED;

// --------------------------------------------------------- Config Enums --------------------------------------------- //

/// @brief Maximum Current Levels for the Device, it is a fraction of the absolute max, 37mA
typedef enum AW9523CURRENT { 

    AW9523_CURR_37M     = 0x0,  ///< Absolute Max, 37mA per LED
    AW9523_CURR_27_75M  = 0x1,  ///< 3/4 of Absolute max
    AW9523_CURR_18_5M   = 0x2,  ///< 1/2 of Absolute Max
    AW9523_CURR_13_875M = 0x3   ///< 1/4 of Absolute Max

} AW9523Current;

// -------------------------------------------------- HAL and Device Struct ------------------------------------------- //

/// @brief Contains function pointers to necesary fucntions needed to drive the device and communicate with it
typedef struct AW9523HAL {

    /// @brief Writes to a register using i2c given the slave and register address
    uint8_t (*i2c_write_reg)(const uint8_t s_addr, const uint8_t r_addr, const void* const data, const uint8_t size);

    /// @brief Reads from a  register using i2c givent the slave and regsister address
    uint8_t (*i2c_read_reg)(const uint8_t s_addr, const uint8_t r_addr, void* const buffer, const uint8_t size);

} AW9523HAL;

/// @brief A Device struct, hold everything needed to operate the device and use it
typedef struct AW9523 {

    AW9523HAL hal;  ///< Hardware Abstraction Layer Functions to read and write from the device
    uint8_t address;///< The I2C Slave address of the device, is found at init time

} AW9523;

// ------------------------------------------- Init and Deinit ---------------------------------------------- //

/**
 * @brief Initializes the device with a HAL and figures out the address
 * 
 * @param[in] dev: Device to Initialize 
 * @param[in] hal: HAL to Init with 
 * @param[in] ad0: If the AD0 pin is tied to VDD 
 * @param[in] ad1: If the AD1 pin is tied to VDD
 * @return AW9523*: Inited device, NULL if there was an error on init
 */
AW9523* AW9523Init(AW9523* const dev, const AW9523HAL* const hal, const bool ad0, const bool ad1);

/**
 * @brief Deinits the device and clears everything
 * 
 * @param[in] dev: Device to deinit 
 */
void AW9523Deinit(AW9523* const dev);

// ------------------------------------------- Global Configuration ------------------------------------------------- //
/**
 * @brief Sets the global confiuaration register of the device
 * 
 * @param[in] dev 
 * @param[in] port0_od 
 * @param[in] max_current 
 * @return uint8_t 
 */
uint8_t AW9523SetConfig(const AW9523* const dev, const bool port0_od, const AW9523Current max_current);

// ------------------------------------------------ Pin Mode Configuration ----------------------------------------------- //

/**
 * @brief 
 * 
 * @param dev 
 * @param port 
 * @param input_mask 
 * @return uint8_t 
 */
uint8_t AW9523SetGPIOPinMode(const AW9523* const dev, const AW9523Port port, const uint8_t input_mask);

/**
 * @brief 
 * 
 * @param dev 
 * @param port 
 * @param gpio_mask 
 * @return uint8_t 
 */
uint8_t AW9523SetPinMode(const AW9523* const dev, const AW9523Port port, const uint8_t gpio_mask);

// ------------------------------------------------------------- Basic Helper Functions ------------------------------------------------- //

/**
 * @brief 
 * 
 * @param dev 
 * @return uint8_t 
 */
uint8_t AW9523Reset(const AW9523* const dev);

/**
 * @brief 
 * 
 * @param dev 
 * @param port 
 * @param is_enabled 
 * @return uint8_t 
 */
uint8_t AW9523SetIntState(const AW9523* const dev, const AW9523Port port, const bool is_not_enabled);

// ----------------------------------------------- GPIO State Functions -------------------------------------------- //

/**
 * @brief 
 * 
 * @param dev 
 * @param port 
 * @param output_mask 
 * @return uint8_t 
 */
uint8_t AW9523SetGPIOOutput(const AW9523* const dev, const AW9523Port port, const uint8_t output_mask);

/**
 * @brief 
 * 
 * @param dev 
 * @param port 
 * @return uint8_t 
 */
uint8_t AW9523GetGPIOInput(const AW9523* const dev, const AW9523Port port);

// ------------------------------------------- LED Value Setting ----------------------------------------- //

/**
 * @brief 
 * 
 * @param dev 
 * @param led 
 * @param current_pwm 
 * @return uint8_t 
 */
uint8_t AW9523SetLEDCurrent(const AW9523* const dev, const uint8_t led, const uint8_t current_pwm);

/**
 * @brief 
 * 
 * @param dev 
 * @param led_start 
 * @param led_end 
 * @param values 
 * @return uint8_t 
 */
uint8_t AW9523SetLEDsCurrent(const AW9523* const dev, const uint8_t led_start, const uint8_t led_end, const uint8_t* const values);

// ---------------------------------------------------- Low Level API ----------------------------------------------- //

/**
 * @brief 
 * 
 * @param dev 
 * @param reg 
 * @param data 
 * @param size 
 * @return uint8_t 
 */
uint8_t AW9523Write(const AW9523* const dev, const AW9523Register reg, const void* const data, const uint8_t size);

/**
 * @brief 
 * 
 * @param dev 
 * @param reg 
 * @param buffer 
 * @param size 
 * @return uint8_t 
 */
uint8_t AW9523Read(const AW9523* const dev, const AW9523Register reg, void* const buffer, const uint8_t size);

#endif // include guard

