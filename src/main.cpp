/*
**********************************************************
**                Macros de Procesamiento               **
**********************************************************
*/

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#define LEDBLINK 2      // Led indicador wifi
#define INTERBUTTON D2  // Pin de interrupcion -> Reset wifi

#elif defined(ESP32)
#include <WiFi.h>
#define LEDBLINK = 33s
#endif

/*
**********************************************************
**                       Librerias                      **
**********************************************************
*/

#include <Arduino.h>

#include "WifiConnection.h"

/*
**********************************************************
**                  Variables Globales                  **
**********************************************************
*/
char nameWifi[] = "WifiPlataform";
long lastDebounceButton = 0;
bool state_reset = false;

/*
**********************************************************
**                       Instancias                     **
**********************************************************
*/

/*
**********************************************************
**               Declaracion de Funciones               **
**********************************************************
*/

void IRAM_ATTR toggleButton();

/*
**********************************************************
**                      Void Setup                      **
**********************************************************
*/

void setup() {
  Serial.begin(115200);

  // -----Configuracion de la interrupcion-----
  pinMode(INTERBUTTON, INPUT_PULLUP);
  attachInterrupt(INTERBUTTON, toggleButton, RISING);

  // -----Auto conexion wifi-----
  Connection_Wifi(nameWifi);
}

/*
**********************************************************
**                       Void Loop                      **
**********************************************************
*/

void loop() {
  // -----Verificacion para el reset wifi-----
  if (state_reset != 0) {
    resetWifi();
  }

  Serial.println("Led On");
  delay(1000);
  Serial.println("Led Off");
  delay(1000);
}

/*
**********************************************************
**               Definicion de Funciones                **
**********************************************************
*/

//* Funcion interrupcion -> reset wifi
void toggleButton() {
  if ((millis() - lastDebounceButton) > 250) {
    lastDebounceButton = millis();
    // Serial.println("INTERRUPCION ON");  // Verificamos si se activa la
    // interrupcion
    state_reset = true;
  }
}
