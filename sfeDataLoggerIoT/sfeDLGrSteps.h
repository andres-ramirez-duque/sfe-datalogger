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

class sfeDLGrSteps : public sfeDLGraphic
{

  public:
    sfeDLGrSteps() : _stepscount{0}
    {
        rect.width = 64;
        rect.height = 9;
    }

    void onDraw(flxDevMicroOLED *screen)
    {
        erase(screen);
        std::string strStepCount = std::format("Nstp:{}", _stepscount);
        screen->text(rect.x, rect.y, strStepCount.c_str());
    }

    void updateValue(uint8_t value)
    {
        if (value > 0 && _stepscount != value)
        {
            _stepscount = value;
            update();
        }
    }
    void listenForUpdate(flxSignalUInt8 &theEvent)
    {
        theEvent.call(this, &sfeDLGrSteps::updateValue);
    }

  private:
    uint32_t _stepscount;
};
//#endif
