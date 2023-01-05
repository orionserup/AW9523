/**
 * @file AW9523.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "AW9523.h"
#include <stddef.h>

AW9523* AW9523Init(AW9523* const dev, const AW9523HAL* const hal, const bool ad0, const bool ad1) {

    if(dev == NULL || hal == NULL)
        return NULL;

    if(hal->i2c_read_reg == NULL || hal->i2c_write_reg == NULL)
        return NULL;

    dev->hal = *hal;
    dev->address = AW9523_BASE_ADDR | ad0 | (ad1 << 1);

    return dev;
}

uint8_t AW9523SetConfig(const AW9523* const dev, const bool port0_od, const AW9523Current max_current)  {

    const uint8_t config = (port0_od << 4) | max_current;
    return AW9523Write(dev, AW9523_REG_CTRL, &config, 1);

}

uint8_t AW9523SetGPIOPinMode(const AW9523* const dev, const AW9523Port port, const uint8_t input_mask) {

    const AW9523Register reg = AW9523_REG_CONFIG_P0 + port;
    return AW9523Write(dev, reg, &input_mask, 1);

}

uint8_t AW9523SetPinMode(const AW9523* const dev, const AW9523Port port, const uint8_t gpio_mask) {

    const AW9523Register reg = AW9523_REG_MODE_P0 + port;
    return AW9523Write(dev, reg, &gpio_mask, 1);

}

uint8_t AW9523Reset(const AW9523* const dev) { return AW9523Write(dev, AW9523_REG_RST, "\0", 1); }

uint8_t AW9523SetIntState(const AW9523* const dev, const AW9523Port port, const bool is_not_enabled) {

    const AW9523Register reg = AW9523_REG_INT_PO + port;
    return AW9523Write(dev, reg, &is_not_enabled, 1);

}

uint8_t AW9523SetGPIOOutput(const AW9523* const dev, const AW9523Port port, const uint8_t value) {

    const AW9523Register reg = AW9523_REG_OUTPUT_P0 + port;
    return AW9523Write(dev, reg, &value, 1);

}

uint8_t AW9523GetGPIOInput(const AW9523* const dev, const AW9523Port port)  {

    const AW9523Register reg = AW9523_REG_INPUT_P0 + port;
    uint8_t res = 0;
    
    AW9523Read(dev, reg, &res, 1);
    return res;
}

uint8_t AW9523SetLEDCurrent(const AW9523* const dev, const uint8_t led, const uint8_t current_pwm) {

    const AW9523Register reg = AW9523_REG_DIM_0 + led;
    return AW9523Write(dev, reg, &current_pwm, 1);

}

uint8_t AW9523SetLEDsCurrent(const AW9523* const dev, const uint8_t led_start, const uint8_t led_end, const uint8_t* const values) {

    const AW9523Register reg = AW9523_REG_DIM_0 + led_start;
    return AW9523Write(dev, reg, values, led_end - led_start);

}

uint8_t AW9523Write(const AW9523* const dev, const AW9523Register reg, const void* const data, const uint8_t size) {

    return dev->hal.i2c_write_reg(dev->address, reg, data, size);

}

uint8_t AW9523Read(const AW9523* const dev, const AW9523Register reg, void* const buffer, const uint8_t size) {

    return dev->hal.i2c_read_reg(dev->address, reg, buffer, size);

}
