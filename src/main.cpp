#include <Arduino.h>
#include <lightStrip.hpp>
#include <constants.hpp>

LightStrip *ls1;

void setup()
{
  Serial.begin(9600);
  ls1 = new LightStrip(2, 11, QUARTER_HOUR);
}

void loop()
{
  ls1->tick();
}
