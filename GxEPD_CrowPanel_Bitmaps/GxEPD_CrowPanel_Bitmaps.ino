// Incluir las bibliotecas necesarias
#include <GxEPD2_BW.h>

//Incluir las definiciones de las fuentes
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>

// Incluir el bitmap
#include "cafe120.h"

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
  
  display.setTextSize(1);
  
  // Limpiar la pantalla
  display.fillScreen(GxEPD_WHITE); // Fondo amarillo
  // Cargar bitmap
  display.drawBitmap(6, 6, gImage_cafe120, 120, 120, GxEPD_BLACK);
   
  // Imprimir "Latte"
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(145, 50);
  display.setFont(&FreeSansBold18pt7b); 
  display.print ("Latte");
  // Imprimir "-10%"
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(130, 100);
  display.setFont(&FreeSansBold24pt7b); 
  display.print ("-10%");
  // Refrescar pantalla
  display.display ();
}
void loop() {
  //No hace nada
}