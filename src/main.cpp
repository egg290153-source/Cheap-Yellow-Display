#include <Arduino.h>
#include <TFT_eSPI.h>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

TFT_eSPI tft = TFT_eSPI();

void checkData();
void displayData();
void paraData();

const uint8_t numChars = 32;
char receivedChars[numChars];
boolean newData = false;

struct tele{
  int MPH;
  int RPMS;
  string Gear;
};

tele car;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_WHITE);


  tft.drawRect(10, 10, 305, 110, TFT_BLACK);
  tft.drawRect(10, 125, 305, 110, TFT_BLACK);

  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(3);

  tft.drawString("Gear: ", 150, 55, 1);
  tft.drawString("MPH: ", 25, 55, 1);
  tft.drawString("RPMS:", 25, 165, 1);
}

void loop() {
  checkData();

  if(newData == true){
  paraData();
  displayData();
  newData = false;
  }

}

void checkData(){
  static uint8_t ndx = 0;
  char rc;
  char endMarker = '\n';

  while(Serial.available() > 0 && newData == false){
    rc = Serial.read();

    if(rc != endMarker){
      receivedChars[ndx] = rc;
      ndx++;
      if(ndx >= numChars){
        ndx = numChars - 1;
      }
    }else{
      receivedChars[ndx] = '\0';
      ndx = 0;
      newData = true;
    }
  }

}

void displayData(){
  tft.fillRect(90, 37, 60, 60, TFT_WHITE);
  tft.setCursor(95, 55);
  tft.print(car.MPH);
    
  tft.fillRect(240, 37, 60, 60, TFT_WHITE);
  tft.setCursor(245, 55);
  tft.print(car.Gear.c_str());

  tft.fillRect(120, 147, 100, 60, TFT_WHITE);
  tft.setCursor(120, 165);
  tft.print(car.RPMS);
}

void paraData(){
  stringstream ss(receivedChars);

  ss >> car.MPH;
  ss >> car.RPMS;
  ss >> car.Gear;
}