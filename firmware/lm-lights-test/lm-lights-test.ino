#define PIN_BUTTON 7
#define PIN_BUTTON_GND 6
#define PIN_PIXELS 3

#define PIXELS_COUNT 50


void setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_BUTTON_GND, OUTPUT);
  digitalWrite(PIN_BUTTON_GND, LOW);
  
  pixelsBegin();
}

void loop() {
  uint8_t button = digitalRead(PIN_BUTTON);

  uint32_t color1 = button ? 0xff0000 : 0x00ff00;
  uint32_t color2 = button ? 0x00ff00 : 0xff0000;

  for (int i = 1; i < PIXELS_COUNT - 1; i++) {
    pixelsSetColor(i, i & 1 ? color1 : color2);
  }
  pixelsSetColor(0, 0x0000ff);
  pixelsSetColor(PIXELS_COUNT - 1, 0x0000ff);
  pixelsShow();
  delay(50);
}

