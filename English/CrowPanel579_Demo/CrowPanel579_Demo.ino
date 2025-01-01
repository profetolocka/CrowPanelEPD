/* Author: Ernesto Tolocka (profe Tolocka)
   Creation Date: 28-12-2024
   Description: Demonstrates the use of the necessary functions to display a full-screen bitmap.
   License: MIT
*/

#include "EPD.h"             // Functions to control the panel
#include "Example579.h"      // Image to load on the panel

uint8_t ImageBW[27200];      // Array to store the image color information (800x272)

void setup() {
  
  pinMode(7, OUTPUT);        
  digitalWrite(7, HIGH);     // Activates the panel's power supply

  EPD_GPIOInit();            // Initializes control and interface pins     

  EPD_Init();                 // Initializes the display
  
  EPD_Display_Clear();        // Clears the display at the hardware level

  EPD_Update();               // Refreshes the display to make it visible

  // Initializes a buffer for the image
  // Passes the image definition, size, rotation, and background color
  Paint_NewImage(ImageBW, EPD_W, EPD_H, Rotation, WHITE);  
 
  EPD_ShowPicture(0, 0, 792, 272, gImage_Example579, WHITE);  // Loads the image into the buffer
  EPD_Display(ImageBW);       // Transfers the image from the buffer to the display

  EPD_Update();               // Refreshes to update the display

  EPD_DeepSleep();           // Activates low-power mode
}

void loop() {
  // Does nothing
}


