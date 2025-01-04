/* Autor: Ernesto Tolocka (profe Tolocka)
   Fecha creación: 3-01-2025
   Descripción: Demuestra el uso de algunas primitivas haciendo un gráfico de barras.
   Licencia: MIT
*/

// Incluir las bibliotecas necesarias
#include <GxEPD2_BW.h>

//Incluir las definiciones de las fuentes
#include <Fonts/FreeMonoBold9pt7b.h>

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
  // Definir canvas para contener al gráfico
  int canvasW = 500;
  int canvasH = 200;
  int canvasX = display.width()/2 - canvasW/2;
  int canvasY = 50;

  // Array para 50 valores 
  int values [50];

  // Prender pantalla
  displayPowerOn ();
  
  // Inicialización del epaper
  display.init(115200);
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);
  display.setRotation(0);
  
  display.setTextSize(1);

  // Configuración del texto
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b); 
  
   // Limpiar la pantalla
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE); // Fondo blanco
 
  // Dibujar Canvas
  display.drawRect(canvasX, canvasY, canvasW, canvasH, GxEPD_BLACK);

  // Escala vertical
  for (int x=1; x<50; x++) {
    display.drawLine (canvasX+(10*x), canvasY, canvasX+(10*x), canvasY+canvasH-1, GxEPD_BLACK);
  }

  // Escala horizontal
  for (int y=1; y<20; y++) {
    display.drawLine (canvasX, canvasY+(10*y), canvasX+canvasW-1, canvasY+(10*y), GxEPD_BLACK);
  }

  // Etiquetas de valores verticales
  display.setCursor(canvasX-70, canvasY);
  display.print ("$100K");
  display.setCursor(canvasX-70, canvasY+(canvasH/2));
  display.print (" $50K");
  display.setCursor(canvasX-70, canvasY+canvasH);
  display.print ("  $0");

  //Llenar el array con valores aleatorios
  for (int i=0; i<50; i++) {
    values [i] = 70 + random(-20, 21);
  }

  // Factor de escala
  int scale = canvasH / 100;

  // Graficar los 50 valores
  for (int i=0; i<50; i++) {
    int y = values[i]*scale;
    display.fillRect (canvasX+(i*10), canvasY + (canvasH -y), 10, y, GxEPD_BLACK);
  }

  // Refrescar pantalla
  display.display (); 
}

void loop() {
  //No hace nada
}