#include <Arduino.h>
#include <lightStrip.hpp>
#include <constants.hpp>
#include <Print.hpp>

LightStrip *ls1;

void setup()
{
  Serial.begin(9600);
  pinMode(9, HIGH);

  ls1 = new LightStrip(2, 11, QUARTER_HOUR);
}

void loop()
{
  ls1->tick();
}
