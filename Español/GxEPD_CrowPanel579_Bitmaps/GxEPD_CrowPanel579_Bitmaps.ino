/* Autor: Ernesto Tolocka (profe Tolocka)
   Fecha creación: 28-12-2024
   Descripción: Demuestra como cargar una imagen bitmap.
   License: MIT
*/

// Incluir las bibliotecas necesarias
#include <GxEPD2_BW.h>

// Incluir el bitmap
#include "bitcoin.h"

// Definición de pines para CrowPanel
const int EINK_BUSY = 48;   
const int EINK_RST  = 47;   
const int EINK_DC   = 46;   
const int EINK_CS   = 45;  
const int EINK_SCK  = 12;  // (SCK)
const int EINK_MOSI = 11;  // (MOSI)

//GDEY0579T93    5.79" b/w 792x272, SSD1683
//Crea objeto del display
GxEPD2_BW<GxEPD2_579_GDEY0579T93, GxEPD2_579_GDEY0579T93::HEIGHT> display(GxEPD2_579_GDEY0579T93(EINK_CS, EINK_DC, EINK_RST, EINK_BUSY));

void displayPowerOn () {

  pinMode(7, OUTPUT);        
  digitalWrite(7, HIGH);     // Activa la alimentación del ePaper
}

void setup() 
{
  
  displayPowerOn ();
  
  // Inicialización del epaper
  display.init(115200);
  display.setFullWindow();
  display.setRotation(0);
  
  // Limpiar la pantalla
  display.fillScreen(GxEPD_WHITE); // Fondo blanco
  
  // Ancho y alto del bitmap
  int bitmapW = 250;
  int bitmapH = 250;

  int bitmapX = (display.width () - bitmapW)/2;
  int bitmapY = (display.height() - bitmapH)/2;
  
  //Cargar bitmap
  display.drawBitmap(bitmapX, bitmapY, gImage_bitcoin, 250, 250, GxEPD_BLACK);
   
  // Refrescar pantalla
  display.display ();
}


void loop() {
  //No hace nada
}