/* Author: Ernesto Tolocka (Profe Tolocka)
   Creation Date: 01-03-2025
   Description: Demonstrates the use of some primitives by creating a bar chart.
   License: MIT
*/

// Include necessary libraries
#include <GxEPD2_BW.h>

// Include font definitions
#include <Fonts/FreeMonoBold9pt7b.h>

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
  digitalWrite(7, HIGH);     // Turn on ePaper power
}

void setup() 
{
  // Define canvas to hold the chart
  int canvasW = 500;
  int canvasH = 200;
  int canvasX = display.width()/2 - canvasW/2;
  int canvasY = 50;

  // Array for 50 values
  int values [50];

  // Turn on the display
  displayPowerOn ();
  
  // Initialize ePaper
  display.init(115200);
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);
  display.setRotation(0);
  
  display.setTextSize(1);

  // Text configuration
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b); 
  
  // Clear the screen
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE); // White background
 
  // Draw canvas
  display.drawRect(canvasX, canvasY, canvasW, canvasH, GxEPD_BLACK);

  // Vertical scale
  for (int x=1; x<50; x++) {
    display.drawLine (canvasX+(10*x), canvasY, canvasX+(10*x), canvasY+canvasH-1, GxEPD_BLACK);
  }

  // Horizontal scale
  for (int y=1; y<20; y++) {
    display.drawLine (canvasX, canvasY+(10*y), canvasX+canvasW-1, canvasY+(10*y), GxEPD_BLACK);
  }

  // Vertical value labels
  display.setCursor(canvasX-70, canvasY);
  display.print ("$100K");
  display.setCursor(canvasX-70, canvasY+(canvasH/2));
  display.print (" $50K");
  display.setCursor(canvasX-70, canvasY+canvasH);
  display.print ("  $0");

  // Fill the array with random values
  for (int i=0; i<50; i++) {
    values [i] = 70 + random(-20, 21);
  }

  // Scaling factor
  int scale = canvasH / 100;

  // Plot the 50 values
  for (int i=0; i<50; i++) {
    int y = values[i]*scale;
    display.fillRect (canvasX+(i*10), canvasY + (canvasH -y), 10, y, GxEPD_BLACK);
  }

  // Refresh the screen
  display.display (); 
}

void loop() {
  // Does nothing
}
