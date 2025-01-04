/* Author: Ernesto Tolocka (Profe Tolocka)
   Creation Date: 01-03-2025
   Description: Demonstrates the use of partial refresh.
   Prints the value of an ascending counter, first in full refresh mode
   and then in partial refresh mode.
   License: MIT
*/

// Include the GxEPD2 libraries
#include <GxEPD2_BW.h>

// Include font definitions
#include <Fonts/FreeSansBold24pt7b.h>

// Define pins for CrowPanel
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
  digitalWrite(7, HIGH);     // Turn on the ePaper power supply
}

void setup() 
{
  int x=0;   // Counter 

  displayPowerOn ();      // Turn on the ePaper
  
  // Initialize the ePaper
  display.init(115200);
  
  display.setRotation(0);
  display.setTextColor(GxEPD_BLACK);
  display.setTextSize(1); 
  display.setFont(&FreeSansBold24pt7b);

  // Full or total refresh mode
  display.setFullWindow();

  for (x=1; x<11; x++) {
    display.firstPage();
    do
    {
      display.fillScreen(GxEPD_WHITE);
      display.setCursor(10, 35);
      display.print(x);
    }
    while (display.nextPage());
    delay (100);
  }
  display.fillScreen(GxEPD_WHITE);  

  // Partial refresh mode
  display.setPartialWindow(0, 0, 80, 40);

  for (x=1; x<11; x++) {
    display.firstPage();
    do
    {
      display.fillScreen(GxEPD_WHITE);
      display.setCursor(10, 35);
      display.print(x);
    }
    while (display.nextPage());
    delay (100);
  }
}

void loop() {
  // Does nothing
}
