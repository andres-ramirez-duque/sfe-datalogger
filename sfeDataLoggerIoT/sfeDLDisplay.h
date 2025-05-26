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

//#ifdef THIS_IS_ENABLED
#include "sfeDLGrBattery.h"
#include "sfeDLGrWiFi.h"
#include "sfeDLGraphx.h"

#include <Flux/flxCoreEvent.h>
#include <Flux/flxDevMAX17048.h>
#include <Flux/flxDevMicroOLED.h>
#include <Flux/flxFSSDMMCard.h>
#include <Flux/flxWiFiESP32.h>

class sfeDLDisplay : public sfeDLGrView
{

  public:
    sfeDLDisplay() : _battery{nullptr}, _screen{nullptr}, _wifi{nullptr}, _card{nullptr}
    {
    }

    void initialize(flxDevMicroOLED *screen)//initialize(flxDevMicroOLED *screen, flxWiFiESP32 *wifi, flxDevMAX17048 *fuel, flxFSSDMMCard *card)
    {
        _screen = screen;
        //_wifi = wifi;
        //_battery = fuel;
        //_card = card;

        // Setup our WiFi graphic
        //_grWiFi.origin(4, 1);
        //_grWiFi.listenForUpdate(_on_wifi);
        //add(&_grWiFi);
        //_grWiFi.update();

        // Setup our Battery graphic
        _grBattery.origin(24, 1);
        _grBattery.listenForUpdate(_on_battery);
        add(&_grBattery);
        _grBattery.update();
    }

    void onGrUpdate(void)
    {
        if (!_screen)
            return;
        uint8_t level =  (uint8_t)random(1,5);
        _on_battery.emit(level);
        //if (_wifi)
        //    _on_wifi.emit(_wifi->rating());

        //if (_battery)
        //{
        //    float batterySOC = _battery->getSOC();
        //    uint level = batterySOC > 70. ? 4 : batterySOC > 40. ? 3 : batterySOC > 15. ? 2 : 1;
        //    _on_battery.emit(level);
        //}

        draw(_screen);
    }

    void update(void)
    {
        if (_screen)
            sfeDLGrView::update(_screen);
    }

  private:
    flxDevMAX17048 *_battery;
    flxDevMicroOLED *_screen;
    flxWiFiESP32 *_wifi;
    flxFSSDMMCard *_card;

    flxSignalUInt8 _on_wifi;
    //sfeDLGrWiFi _grWiFi;

    flxSignalUInt8 _on_battery;
    sfeDLGrBattery _grBattery;
};

//#endif