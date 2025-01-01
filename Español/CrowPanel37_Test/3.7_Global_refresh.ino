#include <Arduino.h>
#include "EPD.h"
#include "EPD_GUI.h"
#include "santa.h"
uint8_t ImageBW[12480];
void setup() {
  // put your setup code here, to run once:
  
  //Configura el pin 7 (xx) y activa el panel
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  //Iniciliza pines de control e interfaz
  EPD_GPIOInit();
  
  //Crea un buffer para la imagen
  //Pasa la definicion de imagen, tamaño, rotacion 
  Paint_NewImage(ImageBW, EPD_W, EPD_H, Rotation, WHITE);
  
  //Limpia el buffer con blanco
  Paint_Clear(WHITE); //Clear Canvas

  EPD_FastInit();
  EPD_Display_Clear();
  EPD_Update(); 

  //---Power on interface
  //  EPD_PartInit();
  EPD_FastInit();
  
  //Transfiere imagen al panel
  EPD_ShowPicture(0, 0, EPD_W, EPD_H, gImage_santa, WHITE);
  EPD_Display(ImageBW);
  EPD_Update();
  EPD_DeepSleep();
}

void loop() {
  // put your main code here, to run repeatedly:

}
