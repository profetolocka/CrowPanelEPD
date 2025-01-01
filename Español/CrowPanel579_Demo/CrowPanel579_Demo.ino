/* Autor: Ernesto Tolocka (profe Tolocka)
   Fecha creación: 28-12-2024
   Descripción: Demuestra el uso de las funciones necesarias para mostrar un bitmap a pantalla completa.
   License: MIT
*/

#include "EPD.h"             // Funciones para controlar el panel
#include "Example579.h"      // Imagen a cargar en el panel

uint8_t ImageBW[27200];      // Array para almacenar la informacion de color de la imagen (800x272)

void setup() {
  
  pinMode(7, OUTPUT);        
  digitalWrite(7, HIGH);     // Activa la alimentacion del panel

  EPD_GPIOInit();            // Iniciliza pines de control e interfaz     

  EPD_Init();                 // Inicializa la pantalla
  
  EPD_Display_Clear();        // Limpia la pantalla a nivel de hardware

  EPD_Update();               // Refresca para que se vea

  //Inicializa un buffer para la imagen
  //Pasa la definicion de imagen, tamaño, rotacion y color de fondo
  Paint_NewImage(ImageBW, EPD_W, EPD_H, Rotation, WHITE);  
 
  EPD_ShowPicture(0, 0, 792, 272, gImage_Example579, WHITE);  //Pasa la imagen al buffer
  EPD_Display(ImageBW);       // Transfiere la imagen del buffer a la pantalla

  EPD_Update();               // Refresca para actualizar

  EPD_DeepSleep();           // Activar modo de bajo consumo
}

void loop() {
  //No hace nada
}


