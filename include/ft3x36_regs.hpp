/**
 * @file ft3x36_regs.hpp
 * @author melektron (matteo@elektron.work)
 * @brief definition of registers and bit masks in the FT6x36 chip
 * @version 0.1
 * @date 2023-08-03
 * 
 * @copyright Copyright HinsTech GmbH (c) 2023-now
 * 
 */

#pragma once

// register addresses
#define FT_REG_DEV_MODE     0x00
#define FT_REG_GEST_ID      0x01
#define FT_REG_TD_STATUS    0x02
#define FT_REG_P1_XH        0x03
#define FT_REG_P1_XL        0x04
#define FT_REG_P1_YH        0x05
#define FT_REG_P1_YL        0x06
#define FT_REG_P1_WEIGHT    0x07
#define FT_REG_P1_MISC      0x08
#define FT_REG_P2_XH        0x09
#define FT_REG_P2_XL        0x0A
#define FT_REG_P2_YH        0x0B
#define FT_REG_P2_YL        0x0C
#define FT_REG_P2_WEIGHT    0x0D
#define FT_REG_P2_MISC      0x0E
#define FT_REG_TH_GROUP     0x80
#define FT_REG_TH_DIFF      0x85
#define FT_REG_CTRL         0x86
#define FT_REG_TIME_ENTER_MONITOR   0x87
#define FT_REG_PERIOD_ACTIVE        0x88
#define FT_REG_PERIOD_MONITOR       0x89
#define FT_REG_RADIAN_VALUE         0X91
#define FT_REG_OFFSET_LEFT_RIGHT    0x92
#define FT_REG_OFFSET_UP_DOWN       0x93
#define FT_REG_DISTANCE_LEFT_RIGHT  0x94
#define FT_REG_DISTANCE_UP_DOWN     0x95
#define FT_REG_DISTANCE_ZOOM        0x96
#define FT_REG_LIB_VER_H    0xA1
#define FT_REG_LIB_VER_L    0xA2
#define FT_REG_CIPHER       0xA3
#define FT_REG_G_MODE       0xA4
#define FT_REG_PWR_MODE     0xA5
#define FT_REG_FIRMID       0xA6
#define FT_REG_FOCALTECH_ID 0xA8
#define FT_REG_RELEASE_CODE_ID      0xAF
#define FT_REG_STATE        0xBC

// offset between point 1 and point 2 regs
#define FT_POINT_REGS_OFFSET 6

// some macros to extract or set special bits
#define FT_WORKING_MODE     0b00000000
#define FT_FACTORY_MODE     0b01000000

#define FT_GET_EVENT_FLAG(xh_reg)   (xh_reg & 0x80)
#define FT_GET_TOUCH_ID(yh_reg)     (yh_reg >> 4)
#define FT_GET_TOUCH_AREA(misc_reg) (misc_reg >> 4)

