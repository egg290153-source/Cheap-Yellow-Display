#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_WHITE);


  tft.drawRect(10, 10, 145, 225, TFT_BLACK);
  tft.drawRect(165, 10, 145, 225, TFT_BLACK);
}

void loop() {
  // put your main code here, to run repeatedly:
}
