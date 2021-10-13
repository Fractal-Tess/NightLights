#pragma once
#include <Arduino.h>
#include <Enums.hpp>
#include <constants.hpp>
#include <Print.hpp>

class LightStrip
{

private:
    // The lightoutput signal pin (relay)
    int lightPin = lightPin;
    // The input pin(btn)
    int signalPin = signalPin;

    //Everything is expressed via miliseconds

    // The maximum allowed time in On state
    uint64_t maxIdleTime;
    // Current time
    uint64_t currentTime;
    // The time of the last click
    uint64_t lastBtnTriggerTime;
    // The time between now and the last click
    uint64_t btnDeltaTime;

    //Set initial values
    LightState lightState;
    // The current value of the btn
    ButtonState curBtnState;
    // The previous value of the btn
    ButtonState lastBtnState;

public:
    void tick();
    LightStrip(int signalPin, int lightPin, int maxIdleTime);

private:
    void HandleTime();
    void HandleButtonClick();
    void SwitchLights(LightState state);
    void ButtonPressed();
    void HandleIdleActivity();
};