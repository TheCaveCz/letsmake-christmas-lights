//
//  Handles button debouncing and detecting short and long presses
//

// hold button longer that this time in milliseconds for long press
#define BUTTON_LONG_TRESHOLD 500UL

#define BUTTON_EVENT_SHORT 0
#define BUTTON_EVENT_LONG_START 1
#define BUTTON_EVENT_LONG_END 2

uint32_t buttonDownTime;
void(*buttonEvent)(uint8_t);

void buttonSetup(void(*event)(uint8_t)) {
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_BUTTON_GND, OUTPUT);
  digitalWrite(PIN_BUTTON_GND, LOW);

  buttonDownTime = 0;
  buttonEvent = event;
}

void buttonCheck() {
  bool pressed = digitalRead(PIN_BUTTON) == LOW;
  // time since button was pressed
  uint32_t delta = buttonDownTime == 0 || buttonDownTime == 0xfffffffful ? 0 : millis() - buttonDownTime;

  if (pressed && buttonDownTime == 0) {
    // button pressed, but time of press wasn't recorded. set it and bail
    buttonDownTime = millis();

  } else if (pressed && delta > BUTTON_LONG_TRESHOLD) {
    // button is still pressed and time exceeded long press treshold - fire long press event and mark it
    if (buttonEvent) buttonEvent(BUTTON_EVENT_LONG_START);
    buttonDownTime = 0xfffffffful;

  } else if (!pressed) {
    // button is not pressed - so if time is good for short press, fire the event and reset time
    if (buttonDownTime == 0xfffffffful) {
      if (buttonEvent) buttonEvent(BUTTON_EVENT_LONG_END);
    } else if (delta > 40) {
      if (buttonEvent) buttonEvent(BUTTON_EVENT_SHORT);
    }
    buttonDownTime = 0;
  }
}

