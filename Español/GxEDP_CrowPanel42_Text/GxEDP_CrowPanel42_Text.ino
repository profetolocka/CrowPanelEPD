/* Autor: Ernesto Tolocka (profe Tolocka)
   Fecha creación: 28-12-2024
   Descripción: Demuestra el uso de distintas fuentes para mostrar texto.
   License: MIT
*/

// Incluir las bibliotecas de GxEPD2
#include <GxEPD2_BW.h>

//Incluir las definiciones de las fuentes
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoOblique12pt7b.h>
#include <Fonts/FreeSerifBold18pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>

// Definición de pines para CrowPanel
const int EINK_BUSY = 48;   
const int EINK_RST  = 47;   
const int EINK_DC   = 46;   
const int EINK_CS   = 45;  
const int EINK_SCK  = 12;  // (SCK)
const int EINK_MOSI = 11;  // (MOSI)

//GDEY0579T93    5.79" b/w 792x272, SSD1683
//Crea objeto del display
GxEPD2_BW<GxEPD2_154_GDEW0154T8, GxEPD2_154_GDEW0154T8::HEIGHT> display(GxEPD2_154_GDEW0154T8(EINK_CS, EINK_DC, EINK_RST, EINK_BUSY));

void displayPowerOn () {
  pinMode(7, OUTPUT);        
  digitalWrite(7, HIGH);     // Activa la alimentacion del ePaper
}

void setup() 
{

  displayPowerOn ();      // Prende el ePaper
  
  // Inicialización del epaper
  display.init(115200);
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);
  display.setRotation(0);
  
  display.setTextColor(GxEPD_BLACK);
  display.setTextSize(1);
  
  display.setFont(&FreeMono9pt7b);
  display.setCursor(10, 20);
  display.print ("Hola mundo!");
  
  display.setFont(&FreeMono12pt7b);
  display.setCursor(10, 50);
  display.print ("Hola mundo!");
  
  display.setFont(&FreeMonoBold12pt7b);
  display.setCursor(10, 80);
  display.print ("Hola mundo!");
  
  display.setFont(&FreeMonoOblique12pt7b);
  display.setCursor(10, 110);
  display.print ("Hola mundo!");
  
  display.setFont(&FreeSerifBold18pt7b);
  display.setCursor(10, 150);
  display.print ("Hola mundo!");

  display.setFont(&FreeSansBold24pt7b);
  display.setCursor(10, 200);
  display.print ("Hola mundo!");
  display.display ();
}


void loop() {
  //No hace nada
}