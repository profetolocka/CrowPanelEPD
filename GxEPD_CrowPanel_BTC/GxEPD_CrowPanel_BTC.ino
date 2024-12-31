// Incluir las bibliotecas necesarias

#include <GxEPD2_BW.h>      // GxEPD2_579_GDEY0579T93
#include <WiFi.h>           // Funciones para la conexión WiFi

//Incluir las definiciones de las fuentes
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>

// Incluir el bitmap
#include "bitcoin.h"

// Definición de pines para CrowPanel
const int EINK_BUSY = 48;   
const int EINK_RST  = 47;   
const int EINK_DC   = 46;   
const int EINK_CS   = 45;  
const int EINK_SCK  = 12;  // (SCK)
const int EINK_MOSI = 11;  // (MOSI)

// Configuración de la red Wi-Fi
const char* ssid = "TuSSID";              // Reemplaza "TuSSID" con el nombre de tu red Wi-Fi
const char* password = "TuContraseña";    // Reemplaza "TuContraseñ

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
  
  // Conexión a la red Wi-Fi
  Serial.println("Conectando a Wi-Fi...");
  WiFi.begin(ssid, password);

  // Espera hasta que se conecte
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Una vez conectado
  Serial.println("");
  Serial.println("Conectado a Wi-Fi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP()); // Muestra la IP asignada al ESP32S3

  
  
  // Limpiar la pantalla
  display.fillScreen(GxEPD_WHITE); // Fondo blanco
  // Cargar bitmap
  display.drawBitmap(50, 10, gImage_bitcoin, 250, 250, GxEPD_BLACK);
   
  // Refrescar pantalla
  display.display ();
}
void loop() {
  //No hace nada
}
