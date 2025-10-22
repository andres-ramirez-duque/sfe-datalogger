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


class sfeDLGrLoc : public sfeDLGraphic
{

  public:
    sfeDLGrLoc() : _lat{0}, _long{0}
    {
        rect.width = 64;
        rect.height = 9;
    }

    void onDraw(flxDevMicroOLED *screen)
    {
        erase(screen);
        std::string strLocLat = std::format("Lat:{:.2f}", _lat);
        std::string strLocLong = std::format("Lon:{:.2f}", _long);
        screen->text(rect.x, rect.y, strLocLat.c_str());
        screen->text(rect.x, rect.y+rect.height, strLocLong.c_str());
    }

    void updateValue(float value_lat, float value_long)
    {
        if (_long != value_long || _lat != value_lat)
        {
            _lat = value_lat;
            _long = value_long;
            update();
        }
    }
    void listenForUpdate(flxSignalFloat_2Args &theEvent)
    {
        theEvent.call(this, &sfeDLGrLoc::updateValue);
    }

  private:
    float _lat;
    float _long;
};
//#endif
