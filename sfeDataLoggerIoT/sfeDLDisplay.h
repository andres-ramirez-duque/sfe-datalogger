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
#include "sfeDLGrSteps.h"
#include "sfeDLGrLoc.h"
#include "sfeDLGrHr.h"
#include <SparkFun_Bio_Sensor_Hub_Library.h>

#include <Flux/flxCoreEvent.h>
#include <Flux/flxDevMAX17048.h>
#include <Flux/flxDevMicroOLED.h>
#include <Flux/flxFSSDMMCard.h>
#include <Flux/flxWiFiESP32.h>
#include <Flux/flxDevGNSS.h>

class sfeDLDisplay : public sfeDLGrView
{

  public:
    sfeDLDisplay() : _battery{nullptr}, _screen{nullptr}, _wifi{nullptr}, _card{nullptr}, _bioHub{nullptr}, _onBoardIMU{nullptr}, _gnss{nullptr}
    {
    }

    void initialize(flxDevMicroOLED *screen, flxWiFiESP32 *wifi, flxDevMAX17048 *fuel, flxDevISM330_SPI *onBoardIMU, flxDevBioHub *bioHub, flxDevGNSS *gnss)//initialize(flxDevMicroOLED *screen, flxWiFiESP32 *wifi, flxDevMAX17048 *fuel, flxFSSDMMCard *card)
    {
        _screen = screen;
        _onBoardIMU = onBoardIMU;
        _bioHub = bioHub;
        _wifi = wifi;
        _battery = fuel;
        _gnss = gnss;
        //_card = card;

        // Setup our WiFi graphic
        _grWiFi.origin(50, 3);
        _grWiFi.listenForUpdate(_on_wifi);
        add(&_grWiFi);
        _grWiFi.update();

        // Setup our Battery graphic
        _grBattery.origin(1, 1);
        _grBattery.listenForUpdate(_on_battery);
        add(&_grBattery);
        _grBattery.update();

        // Setup our Steps graphic
        _grSteps.origin(1, 14);
        _grSteps.listenForUpdate(_on_steps);
        add(&_grSteps);
        _grSteps.update();
        // Setup our location graphic
        _grLoc.origin(1, 23); // 14 + 9
        _grLoc.listenForUpdate(_on_loc);
        add(&_grLoc);
        _grLoc.update();
        // Setup our bpm graphic
        _grHr.origin(1, 41); // 23 + 9 + 9
        _grHr.listenForUpdate(_on_hr);
        add(&_grHr);
        _grHr.update();
    }

    void onGrUpdate(void)
    {
        if (!_screen)
            return;
        if(_bioHub->isInitialized())
        {
            _body = _bioHub->readBpm();
            _on_hr.emit((uint8_t)_body.heartRate);
        }
        //uint8_t level =  (uint8_t)random(1,5);
        // _on_battery.emit(level);
        if (_wifi)
            _on_wifi.emit(3);

        if (_battery)
        {
            float batterySOC = _battery->getSOC();
            uint level = batterySOC > 70. ? 4 : batterySOC > 40. ? 3 : batterySOC > 15. ? 2 : 1;
            _on_battery.emit(level);
        }
        if (_onBoardIMU)
        {
            _on_steps.emit((uint8_t)_onBoardIMU->getStepCounter());
        }
        if(_gnss)
        {
            double latitude = (((double)_gnss->getLatitude()) / 10000000);
            double longitude = (((double)_gnss->getLongitude()) / 10000000);
            _on_loc.emit((float)latitude,(float)longitude);
        }
        
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
    flxDevISM330_SPI *_onBoardIMU;
    flxDevBioHub *_bioHub;
    flxDevGNSS *_gnss;
    bioData _body;

    flxSignalUInt8 _on_wifi;
    sfeDLGrWiFi _grWiFi;

    flxSignalUInt8 _on_battery;
    sfeDLGrBattery _grBattery;
    
    flxSignalUInt8 _on_steps;
    sfeDLGrSteps _grSteps;

    flxSignalUInt8 _on_hr;
    sfeDLGrHr _grHr;

    flxSignalFloat_2Args _on_loc;
    sfeDLGrLoc _grLoc;
};

//#endif