#include <Arduino.h>

const int IDLE_TURN_OFF = 1800; //  1800s = 60s per minute * 30 minutes
const int BTN_CLICK_DOWNTIME = 3;

enum LightState
{
  OFF,
  ON
};
enum ButtonState
{
  UP,
  DOWN
};

template <typename... Args>
void pprint(const Args &...a)
{
  using expander = int[];
  (void)expander{0, ((void)Serial.println(a), 0)...};
}

class LightStrip
{
private:
  int lightPin = lightPin;
  int btnPin = btnPin;

  unsigned long maxIdleTime = 900; // Default value
  unsigned long currentTime = 0;
  unsigned long lastBtnTriggerTime = 0;
  unsigned long btnDeltaTime = 0;

  LightState lightState = OFF;
  ButtonState curBtnState = UP;
  ButtonState lastBtnState = UP;

public:
  void tick()
  {
    HandleTime();
    HandleIdleActivity();
    HandleButtonClick();
  }

  LightStrip(int btnPin, int lightPin, int maxIdleTime)
  {
    this->maxIdleTime = maxIdleTime;
    this->lightPin = lightPin;
    this->btnPin = btnPin;
    pinMode(btnPin, INPUT);
    pinMode(lightPin, OUTPUT);
  }

private:
  void HandleTime()
  {
    // Set current time in seconds
    currentTime = (int)(millis() / 1000);
    // Set the time between now and the last click
    btnDeltaTime = currentTime - lastBtnTriggerTime;
  }

  void HandleButtonClick()
  {
    int pinVal = digitalRead(btnPin);
    if (pinVal == HIGH)
      curBtnState = DOWN;
    else
      curBtnState = UP;

    // If btn is pressed and the last recorded state of the btn was not pressed
    if (curBtnState == DOWN && lastBtnState == UP && btnDeltaTime >= BTN_CLICK_DOWNTIME)
    {
      lastBtnTriggerTime = currentTime;
      lastBtnState = DOWN;
      ButtonPressed();
    }
    //If the button is not pressed and the last state is down
    else if (curBtnState == UP && lastBtnState == DOWN)
      lastBtnState = UP;
  }

  void ButtonPressed()
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

  void HandleIdleActivity()
  {
    if (lightState == LightState::ON && btnDeltaTime >= maxIdleTime)
    {
      SwitchLights(LightState::OFF);
    }
  }

  void SwitchLights(LightState state)
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
};

LightStrip *ls1;

void setup()
{
  Serial.begin(9600);

  ls1 = new LightStrip(2, 11, 1800);
}

void loop()
{
  ls1->tick();
}
