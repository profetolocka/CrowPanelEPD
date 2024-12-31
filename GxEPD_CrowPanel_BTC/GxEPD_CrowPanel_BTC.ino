// Incluir las bibliotecas necesarias

#include <GxEPD2_BW.h>      // GxEPD2 monocromo
#include <WiFi.h>           // Funciones para la conexión WiFi
#include <HTTPClient.h>     // Para hacer peticiones HTTP
#include <ArduinoJson.h>    // Para parsear JSON


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
const char* ssid = "**";              // Reemplaza "TuSSID" con el nombre de tu red Wi-Fi
const char* password = "**";    // Reemplaza "TuContraseñ

// URL de la API de CoinGecko para obtener el precio de Bitcoin en USD
const char* endpoint = "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd";

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
  // Refrescar pantalla
  display.display ();
  
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
  Serial.print("Conectado a: ");
  Serial.println(WiFi.SSID());
  
  // Limpiar la pantalla
  display.fillScreen(GxEPD_WHITE); // Fondo blanco
  
  //Dibujar marco
  display.drawRect(0, 0, 792, 272, GxEPD_BLACK);
  display.drawRect(1, 1, 790, 270, GxEPD_BLACK);

  // Cargar bitmap
  display.drawBitmap(50, 10, gImage_bitcoin, 250, 250, GxEPD_BLACK);
  
  // Mostrar textos
  display.setTextColor(GxEPD_BLACK);
  display.setTextSize(1);
  
  display.setFont(&FreeSansBold24pt7b);
  display.setCursor(350, 80);
  display.print ("Cotizacion BTC");

  // Refrescar pantalla
  display.display ();
}
void loop() {
    
  char valorBTC[7];       // Para el valor como string

  // Solo intentamos hacer la petición si seguimos conectados
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(endpoint);           // Prepara la conexión
    int httpCode = http.GET();      // Lanza la petición GET a la API

    if (httpCode > 0) {
      // Si la respuesta es positiva, leemos el contenido
      String payload = http.getString();

      // Usamos ArduinoJson para parsear
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        // La respuesta de CoinGecko suele ser de la forma:
        // {
        //   "bitcoin": {
        //     "usd": 28381
        //   }
        // }
        float price = doc["bitcoin"]["usd"];
        Serial.print("BTC (USD): $");
        Serial.println(price);

        dtostrf(price, 6, 0, valorBTC);
        Serial.println(valorBTC);

        //Cambiar a refresco parcial
        display.setCursor(350, 120);
        display.print (valorBTC);
        display.display ();

      } else {

        // Si hay un error al parsear
        Serial.print("Error al parsear JSON: ");
        Serial.println(error.c_str());
      }
    } else {
      // Si el código de respuesta HTTP es negativo o falla
      Serial.print("Error en la petición: ");
      Serial.println(httpCode);
    }

    http.end(); // Cierra la conexión
  } else {
    Serial.println("WiFi desconectado, intentando reconectar...");
    WiFi.begin(ssid, password);
  }

  // Esperamos 15 segundos antes de la próxima lectura
  delay(15000);

}
