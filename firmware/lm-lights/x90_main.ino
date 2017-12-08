#if REPORT_FPS
uint16_t fps;
uint32_t lastFrameReport;
#endif

void setup() {
#if REPORT_FPS
  Serial.begin(9600);
  fps = 0;
  lastFrameReport = millis();
#endif
  modesSetup();
  buttonSetup(modesButton);
  pixelsBegin();
}

void loop() {
  buttonCheck();
#if REPORT_FPS
  uint32_t start = millis();
  modesLoop();
  uint32_t time = millis();
  fps = 1000 / (time - start);

  if (time - lastFrameReport > 500) {
    Serial.println(fps);
    lastFrameReport = time;
  }
#else
  modesLoop();
#endif
}

