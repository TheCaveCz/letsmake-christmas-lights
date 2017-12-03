uint8_t modesCount;
uint8_t modesCurrent;
uint32_t modesStartTime;
uint8_t modesReverse;

MODE(autoswitch) {
  uint8_t mode = ((time / MODE_AUTOSWITCH_TIME) % (modesCount - 1)) + 1;
  if (mode >= modesCount) return 0;

  ModeFunction f = modes[mode];
  return f(led, time);
}

void modesSet(uint8_t newMode) {
  modesCurrent = newMode;
  if (modesCurrent >= modesCount) {
    modesCurrent = 0;
  }
  modesStartTime = millis();
}

void modesSetup() {
  modesCount = 0;
  while (modes[modesCount]) {
    modesCount++;
  }
  modesReverse = 0;
  modesSet(0);
}

void modesButton(uint8_t type) {
  switch (type) {
    case BUTTON_EVENT_SHORT:
      modesSet(modesCurrent + 1);
      break;
    case BUTTON_EVENT_LONG_START:
      modesReverse = modesReverse ? 0 : 1;
      break;
  }
}

void modesLoop() {
  if (modesCurrent >= modesCount) return;

  ModeFunction f = modes[modesCurrent];
  uint32_t time = millis() - modesStartTime;
  uint32_t c;
  for (uint8_t led = 0; led < PIXELS_COUNT; led++) {
    c = f(led, time);
    if ((c & 0xff000000ul) == 0) {
      pixelsSetColor(modesReverse ? led : PIXELS_COUNT - led - 1, c);
    }
  }

  pixelsShow();
}

