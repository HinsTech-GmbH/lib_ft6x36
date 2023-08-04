/**
 * @file ft6x36.hpp
 * @author melektron (matteo@elektron.work)
 * @brief FD6x36 driver class
 * @version 0.1
 * @date 2023-08-03
 * 
 * @copyright Copyright HinsTech GmbH (c) 2023-now
 * 
 */

#pragma once

#include <stm32f4xx_hal.h>

struct touch_point_t
{
    uint16_t x, y;
    uint8_t touch_id, weight, area, event;
};

#define FT_EVENT_PRESS      0x00    // indicates a touch has just started
#define FT_EVENT_RELEASE    0x01    // indicates a touch has ended or is no longer pressed
#define FT_EVENT_CONTACT    0x02    // indicates the finger is held on screen
#define FT_EVENT_NONE       0x03    // indicates nothing, this is the value at startup before first touch. After first release, the value will stay as released

class FT6x36
{
protected:  // data
    // I2C handle to use for communication
    I2C_HandleTypeDef &hi2c;
    // the address of the FD3x36 chip on the bus (this is fixed)
    const uint8_t addr;  // already shifted in constructor

protected:  // methods
    /**
     * @brief reads the value of a register and returns it
     * 
     * @param _reg_addr register address
     * @return uint8_t value of the register
     */
    uint8_t readRegister(uint8_t _reg_addr) const;

    /**
     * @brief sets the value of a register in the chip
     * 
     * @param _reg_addr register address
     * @param _val value to set the register to
     */
    void writeRegister(uint8_t _reg_addr, uint8_t _val) const;

public:
    /**
     * @brief creates a new instance of the class and saves interface instance
     * 
     * @param _hi2c I2C interface to use
     * @param _addr I2C address of the chip (only the 7 address bits, NOT shifted by 1). 
     * This is fixed to 0x38 shouldn't need changing.
     */
    FT6x36(I2C_HandleTypeDef &_hi2c, uint8_t _addr = 0x38);

    /**
     * @return uint8_t chip ID of the connected FT6x36 chip
     */
    uint8_t readID();

    /**
     * @return uint8_t number of active touches or 0 if none
     * Range: 0-2
     */
    uint8_t getNrTouches();

    /**
     * @brief reads the nth touch point info from chip and 
     * stores it in provided structure.
     * This does not check whether the touch is active.
     * 
     * @param _n point number 1 or 2
     * @param _point [out] structure to store data
     */
    void getPoint(uint8_t _n, touch_point_t *_point);

    /**
     * @return uint8_t the value of the gesture register 
     */
    uint8_t getGesture();

    /**
     * @return uint8_t touch threshold value from the threshold register
     */
    uint8_t getThreshold();

    /**
     * @brief Sets the touch detection threshold by writing to the
     * threshold register
     * 
     * @param _threshold new touch threshold value
     */
    void setThreshold(uint8_t _threshold);

    /**
     * @brief enables or disables mode switching.
     * When enabled (default) the FT6x36 chip will switch to 
     * a mode called "monitor mode" if no active touch is detected after
     * a certain period of time. Once a touch is detected, the device will 
     * switch in active mode. If mode switching is disabled, the device will
     * always be in active mode.
     * Presumably, the difference is that the sampling rate is higher in active mode,
     * however it might not make any difference. 
     * 
     * @param _onoff true = on, false = off
     */
    void setModeSwitching(bool _onoff);

    /**
     * @brief Sets the amount of time to wait before switching to monitor
     * mode after a touch has finished when mode switching is enabled
     * 
     * @param _delay time to wait in arbitrary units
     */
    void setModeSwitchDelay(uint8_t _delay);

    /**
     * @return uint8_t sampling period in active mode from register 
     * (probably in ms but not documented)
     */
    uint8_t getPeriodActive();
    
    /**
     * @return uint8_t sampling period in monitor mode from register
     * (probably in ms but not documented)
     */
    uint8_t getPeriodMonitor();

    /**
     * @brief Sets the sampling period in active mode
     * 
     * @param _rate sampling period register value (probably in ms but not documented)
     */
    void setPeriodActive(uint8_t _rate);

    /**
     * @brief Sets the sampling period in monitor mode
     * 
     * @param _rate sampling period register value (probably in ms but not documented)
     */
    void setPeriodMonitor(uint8_t _rate);

};