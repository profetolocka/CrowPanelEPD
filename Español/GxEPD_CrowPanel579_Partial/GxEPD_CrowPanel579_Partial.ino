/* Autor: Ernesto Tolocka (profe Tolocka)
   Fecha creación: 3-01-2025
   Descripción: Demuestra el uso del refresco parcial.
   Imprime el valor de un contador ascendente, primero en modo refresco total
   y luego en modo de refresco parcial.
   Licencia: MIT
*/

// Incluir las librerias de GxEPD2
#include <GxEPD2_BW.h>

//Incluir las definiciones de las fuentes
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
GxEPD2_BW<GxEPD2_579_GDEY0579T93, GxEPD2_579_GDEY0579T93::HEIGHT> display(GxEPD2_579_GDEY0579T93(EINK_CS, EINK_DC, EINK_RST, EINK_BUSY));

void displayPowerOn () {
  pinMode(7, OUTPUT);        
  digitalWrite(7, HIGH);     // Activa la alimentacion del ePaper
}

void setup() 
{

  int x=0;   // Contador 

  
  displayPowerOn ();      // Prende el ePaper
  
  // Inicialización del epaper
  display.init(115200);
  
  display.setRotation(0);
  display.setTextColor(GxEPD_BLACK);
  display.setTextSize(1); 
  display.setFont(&FreeSansBold24pt7b);

  // Modo de refresco completo o total
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


  // Modo de refresco parcial
  display.setPartialWindow (0,0,80,40);

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
  //No hace nada
}