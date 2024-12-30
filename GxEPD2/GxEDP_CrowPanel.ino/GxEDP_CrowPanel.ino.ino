// Incluir las bibliotecas de GxEPD2
#include <GxEPD2_BW.h>

//Incluir fuente para el texto
#include <Fonts/FreeSans9pt7b.h>

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

void setup() 
{
  
  pinMode(7, OUTPUT);        
  digitalWrite(7, HIGH);     // Activates the panel's power supply
  
  
  // Inicialización del epaper
  display.init(115200);
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);
  display.setRotation(0);
  
  //Inicializa parámetros del texto
  display.setTextColor(GxEPD_BLACK);
  display.setTextSize(2);
  display.setFont(&FreeSans9pt7b);

  //Imprime texto
  display.setCursor(0, 30);
  display.println ("Hooooooooooooooola mundoooooooooooo!");
  display.println ("Hooooooooooooooola mundoooooooooooo!");
  display.println ("Hooooooooooooooola mundoooooooooooo!");
  display.println ("Hooooooooooooooola mundoooooooooooo!");
  display.println ("Hooooooooooooooola mundoooooooooooo!");
  display.println ("Hooooooooooooooola mundoooooooooooo!");

  
  //Actualiza ePaper
  display.display ();
}

void loop() {
  //No hace nada
}