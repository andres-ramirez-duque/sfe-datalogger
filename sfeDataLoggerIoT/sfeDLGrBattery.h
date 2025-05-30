/*
 *---------------------------------------------------------------------------------
 *
 * Copyright (c) 2022-2024, SparkFun Electronics Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 *---------------------------------------------------------------------------------
 */
#pragma once

//#ifdef IF_THIS_IS_ENABLED
#include "sfeDLGraphx.h"

// Icons
const int kIconBatteryHeight = 12;
const int kIconBatteryWidth = 19;

const uint8_t kIconsSteps[] =
    {0x03, 0x80, 0x00, 0x07, 0xc0, 0x00, 0x07, 0xc0, 0x00, 0x07, 0xe0, 0x00, 0x07, 0xe0, 0x00, 0x07, 0xe0, 0x00, 0x07,
     0xc0, 0x00, 0x07, 0xc0, 0x00, 0x07, 0xc0, 0x00, 0x03, 0xc1, 0xc0, 0x00, 0x03, 0xe0, 0x00, 0xc3, 0xe0, 0x03, 0xc7,
     0xe0, 0x03, 0xc7, 0xe0, 0x01, 0xc7, 0xe0, 0x00, 0x07, 0xe0, 0x00, 0x03, 0xe0, 0x00, 0x03, 0xc0, 0x00, 0x03, 0xc0,
     0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0x80, 0x00, 0x07, 0x80, 0x00, 0x07, 0x00};

const uint8_t kIconsLocation[] = 
    {0x0f, 0x00, 0x11, 0x80, 0x20, 0x40, 0x46, 0x60, 0x49, 0x20, 0x49, 0x20,
     0x46, 0x60, 0x60, 0x40, 0x30, 0xc0, 0x19, 0x80, 0x0f, 0x00, 0x06, 0x00};

const uint8_t kIconsBattery[4][38] = {
    // Dead
    {0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x0F, 0x08, 0xF8,
     0x0F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x01, 0x01},
    // 1
    {0xFF, 0x01, 0xFD, 0xFD, 0xFD, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x0F, 0x08, 0xF8,
     0x0F, 0x08, 0x0B, 0x0B, 0x0B, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x01, 0x01},
    // 2
    {0xFF, 0x01, 0xFD, 0xFD, 0xFD, 0x01, 0x01, 0xFD, 0xFD, 0xFD, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x0F, 0x08, 0xF8,
     0x0F, 0x08, 0x0B, 0x0B, 0x0B, 0x08, 0x08, 0x0B, 0x0B, 0x0B, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x01, 0x01},
    // FULL
    {0xFF, 0x01, 0xFD, 0xFD, 0xFD, 0x01, 0x01, 0xFD, 0xFD, 0xFD, 0x01, 0x01, 0xFD, 0xFD, 0xFD, 0x01, 0x0F, 0x08, 0xF8,
     0x0F, 0x08, 0x0B, 0x0B, 0x0B, 0x08, 0x08, 0x0B, 0x0B, 0x0B, 0x08, 0x08, 0x0B, 0x0B, 0x0B, 0x08, 0x0F, 0x01, 0x01}};

class sfeDLGrBattery : public sfeDLGraphic
{

  public:
    sfeDLGrBattery() : _currentBitmap{3}
    {
        rect.width = kIconBatteryWidth + 2;
        rect.height = kIconBatteryHeight + 2;
    }

    void onDraw(flxDevMicroOLED *screen)
    {
        erase(screen);
        screen->bitmap(rect.x + 1, rect.y + 1, (uint8_t *)kIconsBattery[_currentBitmap], kIconBatteryWidth,
                       kIconBatteryHeight);
    }

    void updateValue(uint8_t value)
    {
        if (value < 4 && _currentBitmap != value)
        {
            _currentBitmap = value;
            update();
        }
    }
    void listenForUpdate(flxSignalUInt8 &theEvent)
    {
        theEvent.call(this, &sfeDLGrBattery::updateValue);
    }

  private:
    uint16_t _currentBitmap;
};
//#endif
