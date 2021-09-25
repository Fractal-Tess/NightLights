#include <Arduino.h>

const int IDLE_TURN_OFF = 1800; //  1800 sec = 60s * 30m
const int BTN_CLICK_DOWNTIME = 1;
const int RELAY_PIN = 11;
const int BTN_PIN = 2;

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
  unsigned int maxIdleTime = IDLE_TURN_OFF;

  int lastBtnTriggerTime = 0; //Measure this in MS since last trigger  (seconds)
  int currentTime = 0;
  int btnDeltaTime = 0;

  LightState currentState = OFF;
  ButtonState curBtnState = UP;
  ButtonState lastBtnState = UP;

  void HandleTime()
  {
    // Set current time
    currentTime = (int)(millis() / 1000);
    // Set the time between now and the last click
    btnDeltaTime = currentTime - lastBtnTriggerTime;
  }

  void HandleButtonClick()
  {
    //Read the button pim
    int pinValue = digitalRead(BTN_PIN);
    // If it's high, then we are pressed
    if (pinValue)
      curBtnState = DOWN;
    // Else it's not pressed
    else
      curBtnState = UP;

    // If btn is pressed and the last recorded state of the btn was not being pressed, then >
    // if (curBtnState == DOWN && lastBtnState == UP)
    if (curBtnState == DOWN && lastBtnState == UP && btnDeltaTime >= BTN_CLICK_DOWNTIME)
    {
      lastBtnState = DOWN;
      lastBtnTriggerTime = currentTime;
      ButtonPressed();
    }
    //If the button is pressed, but the last btn state is down
    else if (curBtnState == UP && lastBtnState == DOWN)
      lastBtnState = UP;
  }

  void ButtonPressed()
  {
    switch (currentState)
    {
    case ON:
      SwitchState(OFF);
      break;
    case OFF:
      SwitchState(ON);
      break;
    }
  }

  void HandleIdleActivity()
  {
    if (currentState == ON && btnDeltaTime >= maxIdleTime)
    {
      SwitchState(OFF);
    }
  }

  void SwitchState(LightState state)
  {
    if (state == ON)
    {
      digitalWrite(RELAY_PIN, HIGH);
      lastBtnTriggerTime = currentTime;
      currentState = ON;
    }
    else if (state == OFF)
    {
      digitalWrite(RELAY_PIN, LOW);
      currentState = OFF;
    }
  }

public:
  void tick()
  {
    HandleTime();
    HandleIdleActivity();
    HandleButtonClick();
  }
};

LightStrip ls;

void setup()
{
  //11 => Light strip signal
  pinMode(RELAY_PIN, OUTPUT);
  //2 => Button input pin
  pinMode(BTN_PIN, INPUT);
  Serial.begin(9600);
}

void loop()
{
  ls.tick();
}
