
void setup() {
  Serial.begin(9600);
  modesSetup();
  buttonSetup(modesButton);
  pixelsBegin();
}

void loop() {
  buttonCheck();
  modesLoop();
}

