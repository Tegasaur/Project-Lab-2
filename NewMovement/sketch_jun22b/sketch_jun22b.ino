//First steps with the Kentec Display

#include "SPI.h"


#include "Screen_K35_SPI.h"
Screen_K35_SPI myScreen;

uint16_t colours[6];
uint16_t x;
uint16_t y;
uint16_t z;
uint8_t initFlag;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("hello");
  Serial.println();

  pinMode(RED_LED, OUTPUT);
  myScreen.begin();
  myScreen.clear();
  colours[0] = myScreen.calculateColour(255, 0, 0);
  colours[1] = myScreen.calculateColour(0, 255, 0);
  colours[2] = myScreen.calculateColour(0, 0, 255);
  colours[3] = myScreen.calculateColour(255, 255, 255);
  colours[4] = myScreen.calculateColour(255, 255, 0);
  colours[5] = myScreen.calculateColour(0, 0, 0);
  x = 0;
  y = 0;
  z = 0;

  myScreen.setPenSolid(true);
  myScreen.setFontSolid(false);
  myScreen.setFontSize(2);

  initFlag = 1;
}

void loop() {
  if (initFlag)
  {
    drawHomeScreen();
    initFlag = 0;
  }
  if (myScreen.isTouch() > 0)
  {
    myScreen.getTouch(x, y, z);
    myScreen.gText(10, 10, btoa(x, 8), colours[3]);
    Serial.print(x);
    Serial.print(" ");
    Serial.print(y);
    Serial.print(" ");
    Serial.println(z);
  }
  if (z > 100)
  {
    if ((x < 160 && x > 0) && (y < 240 && y > 100))
    {
      digitalWrite(RED_LED, HIGH);
    }
    else if ((x < 320 && x > 160) && (y > 100 && y < 240))
    {
      digitalWrite(RED_LED, LOW);
    }
    else if ((x < 320 && x > 160) && (y > 0 && y < 100))
    {
      drawSettingsScreen();
    }

  }
}



void drawHomeScreen()
{
  myScreen.clear();
  myScreen.gText(30, 50, "TOUCH LCD DEMO", colours[4]);
  myScreen.rectangle(0, 100, 160, 239, colours[1]);
  myScreen.gText(50, 180, "ON", colours[0]);
  myScreen.rectangle(160, 100, 319, 239, colours[0]);
  myScreen.gText(235, 180, "OFF", colours[1]);
  myScreen.rectangle(160, 0, 319, 100, colours[2]);
  myScreen.gText(180, 50, "SETTINGS", colours[3]);
}

void drawSettingsScreen()
{
  myScreen.clear();
  myScreen.gText(10, 10, "TOUCH LCD DEMO", colours[0]);
  myScreen.gText(10, 30, "TOUCH LCD DEMO", colours[1]);
  myScreen.gText(10, 50, "TOUCH LCD DEMO", colours[2]);
  myScreen.gText(10, 70, "TOUCH LCD DEMO", colours[3]);
  myScreen.gText(10, 90, "TOUCH LCD DEMO", colours[4]);
}
