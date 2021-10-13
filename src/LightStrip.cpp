#include <LightStrip.hpp>

LightStrip::LightStrip(uint8_t signalPin, uint8_t lightPin, uint32_t maxIdleTime)
{
    this->signalPin = signalPin;
    this->lightPin = lightPin;
    this->maxIdleTime = maxIdleTime;
    pinMode(signalPin, INPUT);
    pinMode(lightPin, OUTPUT);

    this->currentTime = 0;
    this->lastBtnTriggerTime = 0;
    this->btnDeltaTime = 0;
    this->lightState = LightState::OFF;
    this->curBtnState = ButtonState::UP;
    this->lastBtnState = ButtonState::UP;
}

void LightStrip::tick()
{
    HandleTime();
    HandleIdleActivity();
    HandleButtonClick();
}

void LightStrip::HandleTime()
{
    currentTime = millis();
    btnDeltaTime = currentTime - lastBtnTriggerTime;
}

void LightStrip::HandleButtonClick()
{
    curBtnState = (digitalRead(signalPin) == HIGH) ? ButtonState::DOWN : ButtonState::UP;

    // If btn is pressed and the last recorded state of the btn was not pressed
    if (curBtnState == ButtonState::DOWN &&
        lastBtnState == ButtonState::UP &&
        btnDeltaTime >= DEFAULT_BTN_COOLDOWN)
    {
        lastBtnTriggerTime = currentTime;
        lastBtnState = ButtonState::DOWN;
        ButtonPressed();
    }
    //If the button is not pressed and the last state is down
    else if (curBtnState == ButtonState::UP && lastBtnState == ButtonState::DOWN)
        lastBtnState = ButtonState::UP;
}

void LightStrip::ButtonPressed()
{
    switch (lightState)
    {
    case LightState::ON:
        SwitchLights(LightState::OFF);
        break;
    case LightState::OFF:
        SwitchLights(LightState::ON);
        break;
    }
}

void LightStrip::HandleIdleActivity()
{
    if (lightState == LightState::ON && btnDeltaTime > maxIdleTime)
    {
        SwitchLights(LightState::OFF);
    }
}

void LightStrip::SwitchLights(LightState state)
{
    switch (state)
    {
    case LightState::ON:
        digitalWrite(lightPin, HIGH);
        lightState = LightState::ON;
        break;
    case LightState::OFF:
        digitalWrite(lightPin, LOW);
        lightState = LightState::OFF;
        break;
    }
}
