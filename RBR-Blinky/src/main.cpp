/*
 * @file board.h
 * @author Saveerapong (Guitar)
 * @brief code for LED to blink 
 * and buttons to control cycle time and duty cycle of blinking idk
*/

#include <Arduino.h>
#include "board.h"

uint8_t prev_button = 0;
uint8_t duty_cycle = 50;
uint32_t cycle_time = 1000;
uint32_t cycle_start = 0;

// put function declarations here:
void buttonHandler();

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(BUTTON_1, BUTTON_MODE);
  pinMode(BUTTON_2, BUTTON_MODE);
  pinMode(BUTTON_3, BUTTON_MODE);
}

void loop() {

  buttonHandler();

  uint32_t on_time = (cycle_time * duty_cycle) / 100;
  // uint32_t off_time = cycle_time - on_time;

  uint32_t time = millis();
  if (time - cycle_start >= cycle_time) {
    cycle_start = time;
  }

  if (time - cycle_start < on_time) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }

}

// put function definitions here:
void buttonHandler() {
  if (digitalRead(BUTTON_1) == BUTTON_ACTIVE) {
    if (prev_button != 1) {
      prev_button = 1;
      cycle_time += 100;
    }
  }
  else if (digitalRead(BUTTON_2) == BUTTON_ACTIVE) {
    if (prev_button != 2) {
      prev_button = 2;
      if (cycle_time >= 200) {
        cycle_time -= 100;
      }
    }
  }
  else if (digitalRead(BUTTON_3) == BUTTON_ACTIVE) {
    if (prev_button != 3) {
      prev_button = 3;
      duty_cycle = (duty_cycle + 25) % 100;
    }
  }
  else {
    prev_button = 0;
  }
}