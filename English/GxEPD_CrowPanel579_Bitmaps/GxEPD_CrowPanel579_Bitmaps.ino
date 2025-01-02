/* Author: Ernesto Tolocka (profe Tolocka)
   Creation Date: 28-12-2024
   Description: Demonstrates how to load a bitmap image.
   License: MIT
*/

// Include the necessary libraries
#include <GxEPD2_BW.h>

// Include the bitmap
#include "bitcoin.h"

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
  digitalWrite(7, HIGH);     // Activates the ePaper power supply
}

void setup() 
{
  
  displayPowerOn();
  
  // ePaper initialization
  display.init(115200);
  display.setFullWindow();
  display.setRotation(0);
  
  // Clear the screen
  display.fillScreen(GxEPD_WHITE); // White background
  // Load bitmap
  display.drawBitmap(50, 10, gImage_bitcoin, 250, 250, GxEPD_BLACK);
   
  // Refresh the screen
  display.display();
}

void loop() {
  // Does nothing
}
