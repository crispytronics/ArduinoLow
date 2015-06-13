#include <ArduinoLow.h>

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  sleepTimer(PRESCALE_32);
  sleepMode(SLEEP_POWER_SAVE);
}
void loop() {
  if(isTicking()) {
    digitalWrite(8, LOW);
  }
  else {
    digitalWrite(8, HIGH);
  }
  
  digitalWrite(9, LOW);
  sleep();
  digitalWrite(9, HIGH);
  sleep();
}