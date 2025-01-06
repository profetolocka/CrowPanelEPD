// Incluir las bibliotecas necesarias

#include <GxEPD2_BW.h>      // GxEPD2 monocromo
#include <WiFi.h>           // Funciones para la conexión WiFi
#include <HTTPClient.h>     // Para hacer peticiones HTTP
#include <ArduinoJson.h>    // Para parsear JSON

//Incluir las definiciones de las fuentes
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// Incluir los bitmaps
#include "bitcoin.h"
#include "menuLateral.h"

// Definición de pines para CrowPanel
const int EINK_BUSY = 48;   
const int EINK_RST  = 47;   
const int EINK_DC   = 46;   
const int EINK_CS   = 45;  
const int EINK_SCK  = 12;  // (SCK)
const int EINK_MOSI = 11;  // (MOSI)

// Teclas MENU y EXIT
const int KEY_MENU = 2;
const int KEY_EXIT = 1;

// Monedas para cotizacion
const int CURR_USD = 0;
const int CURR_EUR = 1;

// Configuración de la red Wi-Fi
const char* ssid = "LosToloNetwork";              // Reemplaza "TuSSID" con el nombre de tu red Wi-Fi
const char* password = "performance15";    // Reemplaza "TuContraseñ

// URL de la API de CoinGecko para obtener el precio de Bitcoin en USD y euros
const char* endpoint = "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd,eur";

unsigned long tiempoAnterior = 0;  // Almacena el último tiempo registrado
const unsigned long intervalo = 30 * 1000;  // Retardo deseado (en milisegundos)

char valorBTC [15];       // Para el valor como string

int currency = CURR_USD;   // Arranca en USD

//GDEY0579T93    5.79" b/w 792x272, SSD1683
//Crea objeto del display
GxEPD2_BW<GxEPD2_579_GDEY0579T93, GxEPD2_579_GDEY0579T93::HEIGHT> display(GxEPD2_579_GDEY0579T93(EINK_CS, EINK_DC, EINK_RST, EINK_BUSY));

void displayPowerOn () {

  pinMode(7, OUTPUT);        
  digitalWrite(7, HIGH);     // Activa la alimentación del ePaper
}

bool keyExitPressed () {
  // Devuelve true si está apretada EXIT
  if (digitalRead(KEY_EXIT)==0) {
    delay (100);
    if (digitalRead (KEY_EXIT)==0)
      return true;
    else
      return false;  
  }
  else
    return false;
}

bool keyMenuPressed () {
  // Devuelve true si está apretada MENU
  if (digitalRead(KEY_MENU)==0) {
    delay (100);
    if (digitalRead (KEY_MENU)==0)
      return true;
    else
      return false;  
  }
  else
    return false;
}

void displayPrintPartial (char *valor) {
  // Imprime el valor del BTC con refresco parcial
  // Definir área parcial
  int windowX = 400; 
  int windowY = 132; 
  int windowW = 320;
  int windowH = 64;

  // Configurar ventana parcial
  display.setPartialWindow(windowX, windowY, windowW, windowH);

  // Mostrar valor en ePaper con refresco parcial
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(windowX, windowY + 40); // Ajusta la posición del cursor según la fuente
    display.setTextColor(GxEPD_BLACK);
    display.print(valor);
  }
  while (display.nextPage());
}

////////////////////////////////////////////////

void setup() 
{
  // Pines de las teclas
  pinMode (KEY_MENU, INPUT);   // MENU
  pinMode (KEY_EXIT, INPUT);   // EXIT

  Serial.begin (115200);

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
  
  displayPowerOn ();

  // Inicialización del epaper
  display.init(115200);
  display.setFullWindow();
  display.setRotation(0);

  // Limpiar la pantalla
  display.fillScreen(GxEPD_WHITE); // Fondo blanco
  
  //Dibujar marco
  display.drawRect(0, 0, 792, 272, GxEPD_BLACK);
  display.drawRect(1, 1, 790, 270, GxEPD_BLACK);

  // Cargar bitmaps
  display.drawBitmap(50, 10, gImage_bitcoin, 250, 250, GxEPD_BLACK);  // BTC
  display.drawBitmap (760,0, gImage_menuLateral, 32, 272, GxEPD_BLACK);  // Menu lateral

  // Mostrar textos
  display.setTextColor(GxEPD_BLACK);
  display.setTextSize(1);
  
  display.setFont(&FreeSansBold24pt7b);
  display.setCursor(350, 100);
  display.print ("Cotizacion BTC");

  // Refrescar pantalla
  display.display ();
}


void loop() {
    
  unsigned long tiempoActual = millis();
 
  //Teclas
  if (keyExitPressed())  {
    currency = CURR_EUR;
    tiempoAnterior = tiempoActual - intervalo; // Fuerza actualizacion
  }

  if (keyMenuPressed()) {
    currency = CURR_USD;
    tiempoAnterior = tiempoActual - intervalo; // Fuerza actualizacion
  }
 
  // Verifica si ha pasado el intervalo
  if (tiempoActual - tiempoAnterior >= intervalo) {
    // Actualiza el tiempo registrado
    tiempoAnterior = tiempoActual;

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
          // Parsear valores
          float priceUSD = doc["bitcoin"]["usd"];
          float priceEUR = doc["bitcoin"]["eur"];

          // Preparar según la moneda
          if (currency == CURR_USD) 
            sprintf(valorBTC, "USD %.0f", priceUSD);
          else
            sprintf(valorBTC, "EUR %.0f", priceEUR);

          Serial.println(valorBTC);

          // Imprime valor usando Refresco Parcial
          displayPrintPartial (valorBTC);
          
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


  }

}
