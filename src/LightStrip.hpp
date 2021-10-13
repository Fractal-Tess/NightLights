#pragma once
#include <Arduino.h>
#include <Enums.hpp>
#include <constants.hpp>
#include <FPrint.hpp>
class LightStrip
{

private:
    // The lightoutput signal pin (relay)
    int lightPin = lightPin;
    // The input pin(btn)
    int signalPin = signalPin;

    //Everything is expressed via miliseconds

    // The maximum allowed time in On state
    uint32_t maxIdleTime;
    // Current time
    uint32_t currentTime;
    // The time of the last click
    uint32_t lastBtnTriggerTime;
    // The time between now and the last click
    uint32_t btnDeltaTime;

    //Set initial values
    LightState lightState;
    // The current value of the btn
    ButtonState curBtnState;
    // The previous value of the btn
    ButtonState lastBtnState;

public:
    void tick(void);
    LightStrip(uint8_t signalPin, uint8_t lightPin, uint32_t maxIdleTime);

private:
    void HandleTime(void);
    void HandleButtonClick(void);
    void SwitchLights(LightState state);
    void ButtonPressed(void);
    void HandleIdleActivity(void);
};