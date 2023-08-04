# lib_ft6x36

STM32Cube PlatformIO HAL library for the FT62366/FT6336/FT6436L/FT6436 capacitive touchscreen controller

## Usage

Simply connect the chip's SDA to STM32 SDA and SCL to STM32 SCL.
Configure the I2C interface you want to use in CubeMX (or manually if you whish to).

To use the library just create an instance of ```FT6x36``` and pass it the 
HAL I2C handle. That's it. The chip doesn't need any initialization and you can then start reading touch points. 

The following pseudo-example (not working example code) shows how to use the driver API:

```cpp
// Library
#include <ft6x36.hpp>
// CubeMX handle definition of I2C handle
#include "main.h"

// replace with your i2c handle
FT6x36 ts(hi2c2);

...


void touchscreen_function()
{
    // reads chip ID
    ts.readID();

    // returns number of touches
    ts.getNrTouches();

    // read touch locations
    touch_point_t _p1, _p2;
    getPoint(0, &_p1);
    getPoint(1, &_p2);

    // returns gesture data, but doesn't seem to be
    // supported by chip and is always 0
    ts.getGesture();

    // returns current threshold value
    ts.getThreshold();

    // sets new threshold value
    ts.setThreshold(128);

    // turn active/monitor switching mode on/off
    ts.setModeSwitching(false);

    // set delay to switch to monitor mode after a touch
    ts.setModeSwitchDelay(123); // arbitrary value

    // gets sample period in active/monitor mode 
    ts.getPeriodActive();
    ts.getPeriodMonitor();

    // sets sample period in active/monitor mode
    ts.setPeriodActive(10);
    ts.setPeriodMonitor(30);
}

```

For more info see the method's doxygen comments

You can change settings like threshold or sampling rate, however most of them seem to have a noticeable effect.


## Limitations

According to the datasheet, the chip does in theory support two-point touch and integrated gestures however the relevant registers do not seem to output any data. According to this issue on some Linux driver code provided by the manufacturer for this chip this is a common issue and it does apparently not actually support gestures or at least they are not documented: https://github.com/focaltech-systems/drivers-input-touchscreen-FTS_driver/issues/1

Multi-Point touch does also not seem to spit out any usable results. The touch points simply move around between the points arbitrarily.