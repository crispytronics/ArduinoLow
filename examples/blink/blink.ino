#include <ArduinoLow.h>

void setup() {
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  sleepTimer(PRESCALE_32);
  sleepMode(SLEEP_POWER_SAVE);
}
void loop() {
  digitalWrite(9, LOW);
  sleep();
  digitalWrite(9, HIGH);
  sleep();
}