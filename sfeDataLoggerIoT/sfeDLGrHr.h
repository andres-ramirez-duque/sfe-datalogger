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
#include <format>


class sfeDLGrHr : public sfeDLGraphic
{

  public:
    sfeDLGrHr() : _bpm{0}
    {
        rect.width = 64;
        rect.height = 9;
    }

    void onDraw(flxDevMicroOLED *screen)
    {
        erase(screen);
        std::string strhr = std::format("Bpm:{}", _bpm);
        screen->text(rect.x, rect.y, strhr.c_str());
    }

    void updateValue(uint8_t value)
    {
        if (value >= 0 && _bpm != value)
        {
            _bpm = value;
            update();
        }
    }
    void listenForUpdate(flxSignalUInt8 &theEvent)
    {
        theEvent.call(this, &sfeDLGrHr::updateValue);
    }

  private:
    uint32_t _bpm;
};
//#endif
