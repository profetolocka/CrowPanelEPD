/* Author: Ernesto Tolocka (profe Tolocka)
   Creation Date: Jan 6, 2024
   Description: Displays the real-time Bitcoin (BTC) price.
   The MENU and EXIT buttons allow switching between currencies (USD and Euro).
   License: MIT
*/

// Include necessary libraries
#include <GxEPD2_BW.h>      // GxEPD2 for monochrome displays
#include <WiFi.h>           // Functions for WiFi connection
#include <HTTPClient.h>     // For making HTTP requests
#include <ArduinoJson.h>    // For parsing JSON

// Include font definitions
#include <Fonts/FreeSansBold24pt7b.h>

// Include bitmaps
#include "bitcoin.h"
#include "sideMenu.h"

// Define pins for CrowPanel
const int EINK_BUSY = 48;   
const int EINK_RST  = 47;   
const int EINK_DC   = 46;   
const int EINK_CS   = 45;  
const int EINK_SCK  = 12;  // (SCK)
const int EINK_MOSI = 11;  // (MOSI)

// MENU and EXIT keys
const int KEY_MENU = 2;
const int KEY_EXIT = 1;

// Currencies for price display
const int CURR_USD = 0;
const int CURR_EUR = 1;

// Wi-Fi network configuration
const char* ssid = "******";       // Use your network name
const char* password = "******";    // Use your password

// CoinGecko API URL to fetch Bitcoin price in USD and EUR
const char* endpoint = "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd,eur";

unsigned long interval = 30 * 1000;  // Desired delay (in milliseconds)
unsigned long timePrev = millis() - interval;  // Initial delayed value

char valorBTC[15];       // For storing the price as a string

int currency = CURR_USD;   // Start with USD

// GDEY0579T93 5.79" b/w 792x272, SSD1683
// Create display object
GxEPD2_BW<GxEPD2_579_GDEY0579T93, GxEPD2_579_GDEY0579T93::HEIGHT> display(GxEPD2_579_GDEY0579T93(EINK_CS, EINK_DC, EINK_RST, EINK_BUSY));

void displayPowerOn() {
  // Activates ePaper power
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
}

bool keyExitPressed() {
  // Returns true if EXIT is pressed
  if (digitalRead(KEY_EXIT) == 0) {
    delay(100);
    if (digitalRead(KEY_EXIT) == 0)
      return true;
    else
      return false;
  } else
    return false;
}

bool keyMenuPressed() {
  // Returns true if MENU is pressed
  if (digitalRead(KEY_MENU) == 0) {
    delay(100);
    if (digitalRead(KEY_MENU) == 0)
      return true;
    else
      return false;
  } else
    return false;
}

void displayPrintPartial(char* valor) {
  // Prints BTC value using partial refresh
  // Define partial refresh area
  int windowX = 400;
  int windowY = 132;
  int windowW = 320;
  int windowH = 64;

  // Configure partial window
  display.setPartialWindow(windowX, windowY, windowW, windowH);

  // Display value on ePaper with partial refresh
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(windowX, windowY + 40); // Adjust cursor position based on font
    display.setTextColor(GxEPD_BLACK);
    display.print(valor);
  } while (display.nextPage());
}

////////////////////////////////////////////////

void setup() {
  // Configure key inputs
  pinMode(KEY_MENU, INPUT);   // MENU
  pinMode(KEY_EXIT, INPUT);   // EXIT

  Serial.begin(115200);

  // Attempt to connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Successful connection
  Serial.println("");
  Serial.print("Connected to: ");
  Serial.println(WiFi.SSID());

  displayPowerOn();   // Power on the screen

  // Initialize ePaper
  display.init(115200);
  display.setFullWindow();
  display.setRotation(0);

  // Clear the screen
  display.fillScreen(GxEPD_WHITE); // White background

  // Draw border
  display.drawRect(0, 0, 792, 272, GxEPD_BLACK);
  display.drawRect(1, 1, 790, 270, GxEPD_BLACK);

  // Load bitmaps
  display.drawBitmap(50, 10, gImage_bitcoin, 250, 250, GxEPD_BLACK);  // BTC
  display.drawBitmap(760, 0, gImage_sideMenu, 32, 272, GxEPD_BLACK);  // Side menu

  // Display text
  display.setTextColor(GxEPD_BLACK);
  display.setTextSize(1);

  display.setFont(&FreeSansBold24pt7b);
  display.setCursor(410, 100);
  display.print("BTC Price");

  // Refresh screen
  display.display();
}

void loop() {
  unsigned long timeActual = millis();

  // Keys
  if (keyExitPressed()) {
    currency = CURR_EUR;
    timePrev = timeActual - interval; // Force update
  }

  if (keyMenuPressed()) {
    currency = CURR_USD;
    timePrev = timeActual - interval; // Force update
  }

  // Check if the interval has passed
  if (timeActual - timePrev >= interval) {
    // Update the recorded time
    timePrev = timeActual;

    // Only attempt the request if connected
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(endpoint);           // Prepare the connection
      int httpCode = http.GET();      // Perform GET request to CoinGecko API

      if (httpCode > 0) {
        // If the response is positive, read the content
        String payload = http.getString();

        // Parse with ArduinoJson
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, payload);

        if (!error) {
          // Parse values
          float priceUSD = doc["bitcoin"]["usd"];
          float priceEUR = doc["bitcoin"]["eur"];

          // Prepare based on the currency
          if (currency == CURR_USD)
            sprintf(valorBTC, "USD %.0f", priceUSD);
          else
            sprintf(valorBTC, "EUR %.0f", priceEUR);

          Serial.println(valorBTC);

          // Print value using partial refresh
          displayPrintPartial(valorBTC);
        } else {
          // If there's an error parsing JSON
          Serial.print("Error parsing JSON: ");
          Serial.println(error.c_str());
        }
      } else {
        // If the HTTP response code is negative or fails
        Serial.print("Request error: ");
        Serial.println(httpCode);
      }

      http.end(); // Close the connection

    } else {
      Serial.println("WiFi disconnected, attempting to reconnect...");
      WiFi.begin(ssid, password);
    }
  }
}
