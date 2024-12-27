#include "EPD.h"             // Funciones para controlar el panel
#include "Example579.h"      // Imagen a cargar en el panel

//OJO!! Debe ser si o si 27200, no 26928 que es el tamaño del .h
//EPD_W=800, asi que 800x272 / 8 = 27200
//En el video aclara que se define asi aunque el panel tenga menos
uint8_t ImageBW[27200];      // Array para almacenar la informacion de color de la imagen

void setup() {
  
  pinMode(7, OUTPUT);        
  digitalWrite(7, HIGH);     // Activa la alimentacion del panel

  EPD_GPIOInit();            // Iniciliza pines de control e interfaz

  //Inicializa un buffer para la imagen
  //Pasa la definicion de imagen, tamaño, rotacion y color de fondo
  Paint_NewImage(ImageBW, EPD_W, EPD_H, Rotation, WHITE);  
  
  //Se asegura de limpiar el buffer de imagen rellenando con color Blanco
  Paint_Clear(WHITE);       

  /***********************Quick screen cleaning works in local flashing mode*************************/
  //Inicializacion rápida
  EPD_FastMode1Init();       // Initialize EPD screen in Quick Mode 1
  
  // Limpia la pantalla 
  EPD_Display_Clear();      // Limpia la pantalla a nivel de hardware
  EPD_Update();             // Refresca para que se vea

  //Comente los 2 y funcionó igual
  //EPD_GPIOInit();            //Initialize the GPIO pin configuration of the EPD e-ink screen again
  //EPD_FastMode1Init();       //Re initialize the EPD screen in Quick Mode 1
      //EPD_ShowPicture(0, 0, 792, 272, gImage_home, WHITE); // Display image gImage_1 with starting coordinates of (0,0), width of 792, height of 272, and a white background color
  
  // Pasa la imagen al buffer
  //EPD_ShowPicture(0, 0, 792, 272, gImage_home, WHITE);

  EPD_ShowPicture(0, 0, 792, 272, gImage_Example579, WHITE);
  
  // Transfiere la imagen a la pantalla
  EPD_Display(ImageBW);      // Display images stored in the ImageBW array
    //  EPD_WhiteScreen_ALL_Fast(gImage_boot_setup); //Annotated code: Display boot settings image using quick mode
    //  EPD_PartUpdate();       //Annotated code: Updating a part of the screen
  //EPD_FastUpdate();          //Perform quick updates to refresh the screen
  
  EPD_FastUpdate(); 
  EPD_DeepSleep();          //Set the screen to deep sleep mode to save power
  delay(5000);              // Wait for 5000 milliseconds (5 seconds)
}

void loop() {
  //No hace nada
}


