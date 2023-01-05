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

#define AW9523_BASE_ADDR  0x58   ///< AW9523 default address

// ------------------------------------------------ Register Defintions ------------------------------------------- //

/// @brief 
typedef enum AW9523REGISTER {

    AW9523_REG_OUTPUT_P0    = 0x02,
    AW9523_REG_OUTPUT_P1    = 0x03,
    AW9523_REG_CONFIG_P0    = 0x04,
    AW9523_REG_CONFIG_P1    = 0x05,
    AW9523_REG_INT_PO       = 0x06,
    AW9523_REG_INT_P1       = 0x07,
    AW9523_REG_CTRL         = 0x11,
    AW9523_REG_MODE_P0      = 0x12,
    AW9523_REG_MODE_P1      = 0x13,    

    // Read Only Registers

    AW9523_REG_INPUT_P0     = 0x00,
    AW9523_REG_INPUT_P1     = 0x01,
    AW9523_REG_ID           = 0x10,

    // Write Only Registers`

    AW9523_REG_DIM_0        = 0x20,
    AW9523_REG_DIM_1        = 0x21,
    AW9523_REG_DIM_2        = 0x22,
    AW9523_REG_DIM_3        = 0x23,
    AW9523_REG_DIM_4        = 0x24,
    AW9523_REG_DIM_5        = 0x25,
    AW9523_REG_DIM_6        = 0x26,
    AW9523_REG_DIM_7        = 0x27,
    AW9523_REG_DIM_8        = 0x28,
    AW9523_REG_DIM_9        = 0x29,
    AW9523_REG_DIM_10       = 0x2A,
    AW9523_REG_DIM_11       = 0x2B,
    AW9523_REG_DIM_12       = 0x2C,
    AW9523_REG_DIM_13       = 0x2D,
    AW9523_REG_DIM_14       = 0x2E,
    AW9523_REG_DIM_15       = 0x2F,

    AW9523_REG_RST          = 0x7F

} AW9523Register;

// ----------------------------------------------- Port Definitions ------------------------------------------------ //

/// @brief 
typedef enum AW9523PORT {

    AW9523_PORT_0 = 0,
    AW9523_PORT_1 = 1

} AW9523Port;

// ----------------------------------------------- LED Enumerations ------------------------------------------------- //

/// @brief 
typedef enum AW9523LED {

    AW9523_LED_P0_0 = 0x4,
    AW9523_LED_P0_1 = 0x5,
    AW9523_LED_P0_2 = 0x6,
    AW9523_LED_P0_3 = 0x7,
    AW9523_LED_P0_4 = 0x8,
    AW9523_LED_P0_5 = 0x9,
    AW9523_LED_P0_6 = 0xA,
    AW9523_LED_P0_7 = 0xB,

    AW9523_LED_P1_0 = 0x0,
    AW9523_LED_P1_1 = 0x1,
    AW9523_LED_P1_2 = 0x2,
    AW9523_LED_P1_3 = 0x3,
    AW9523_LED_P1_4 = 0xC,
    AW9523_LED_P1_5 = 0xD,
    AW9523_LED_P1_6 = 0xE,
    AW9523_LED_P1_7 = 0xF

} AW9523LED;

// --------------------------------------------------------- Config Enums --------------------------------------------- //

/// @brief 
typedef enum AW9523CURRENT { 

    AW9523_CURR_37M     = 0x0,
    AW9523_CURR_27_75M  = 0x1,
    AW9523_CURR_18_5M   = 0x2,
    AW9523_CURR_13_875M = 0x3

} AW9523Current;

// -------------------------------------------------- HAL and Device Struct ------------------------------------------- //

/// @brief 
typedef struct AW9523HAL {

    /// @brief 
    uint8_t (*i2c_write_reg)(const uint8_t s_addr, const uint8_t r_addr, const void* const data, const uint8_t size);

    /// @brief 
    uint8_t (*i2c_read_reg)(const uint8_t s_addr, const uint8_t r_addr, void* const buffer, const uint8_t size);

} AW9523HAL;

/// @brief 
typedef struct AW9523 {

    AW9523HAL hal;
    uint8_t address;

} AW9523;

// ------------------------------------------- Init and Deinit ---------------------------------------------- //

/**
 * @brief 
 * 
 * @param dev 
 * @param hal 
 * @param ad0 
 * @param ad1 
 * @return AW9523* 
 */
AW9523* AW9523Init(AW9523* const dev, const AW9523HAL* const hal, const bool ad0, const bool ad1);

/**
 * @brief 
 * 
 * @param dev 
 * @param port0_od 
 * @param max_current 
 * @return uint8_t 
 */
uint8_t AW9523SetConfig(const AW9523* const dev, const bool port0_od, const AW9523Current max_current);

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

