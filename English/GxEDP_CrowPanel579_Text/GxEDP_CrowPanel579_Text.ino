/* Author: Ernesto Tolocka (profe Tolocka)
   Creation Date: 28-12-2024
   Description: Demonstrates the use of different fonts to display text.
   License: MIT
*/

// Include the GxEPD2 libraries
#include <GxEPD2_BW.h>

// Include font definitions
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoOblique12pt7b.h>
#include <Fonts/FreeSerifBold18pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>

// Pin definitions for CrowPanel
const int EINK_BUSY = 48;   
const int EINK_RST  = 47;   
const int EINK_DC   = 46;   
const int EINK_CS   = 45;  
const int EINK_SCK  = 12;  // (SCK)
const int EINK_MOSI = 11;  // (MOSI)

// GDEY0579T93    5.79" b/w 792x272, SSD1683
// Create display object
GxEPD2_BW<GxEPD2_579_GDEY0579T93, GxEPD2_579_GDEY0579T93::HEIGHT> display(GxEPD2_579_GDEY0579T93(EINK_CS, EINK_DC, EINK_RST, EINK_BUSY));

void displayPowerOn () {
  pinMode(7, OUTPUT);        
  digitalWrite(7, HIGH);     // Activates ePaper power supply
}

void setup() 
{

  displayPowerOn();      // Turns on the ePaper
  
  // ePaper initialization
  display.init(115200);
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);
  display.setRotation(0);
  
  display.setTextColor(GxEPD_BLACK);
  display.setTextSize(1);
  
  display.setFont(&FreeMono9pt7b);
  display.setCursor(10, 20);
  display.print("Hello world!");
  
  display.setFont(&FreeMono12pt7b);
  display.setCursor(10, 50);
  display.print("Hello world!");
  
  display.setFont(&FreeMonoBold12pt7b);
  display.setCursor(10, 80);
  display.print("Hello world!");
  
  display.setFont(&FreeMonoOblique12pt7b);
  display.setCursor(10, 110);
  display.print("Hello world!");
  
  display.setFont(&FreeSerifBold18pt7b);
  display.setCursor(10, 150);
  display.print("Hello world!");

  display.setFont(&FreeSansBold24pt7b);
  display.setCursor(10, 200);
  display.print("Hello world!");
  display.display();
}

void loop() {
  // Does nothing
}
