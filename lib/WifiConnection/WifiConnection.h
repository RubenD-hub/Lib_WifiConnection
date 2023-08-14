/**
 * Libreria que se encarga de la busqueda automatica de redes WiFi, conexion y
 * reseteo de redes WiFi almacenadas.
 * @author: Ruben Sanchez Loperena
 */

/*
**********************************************************
**                Macros de Procesamiento               **
**********************************************************
*/

#ifdef ESP8266
#ifndef LEDBLINK
#define LEDBLINK 2
#endif
#endif

/*
**********************************************************
**                       Librerias                      **
**********************************************************
*/

#include <Arduino.h>
#include <DNSServer.h>
#include <Ticker.h>
#include <WiFiManager.h>

/*
**********************************************************
**                       Instancias                     **
**********************************************************
*/

Ticker tic_led;  // Libreria para llamar funciones repetidas cada cierto tiempo
WiFiManager wm;  // Libreria auto conectar WiFi

/*
**********************************************************
**                       Funciones                      **
**********************************************************
*/

//* Funcion encargada del cambio de estado del led
void blinkingLedWifi() {
  byte state = digitalRead(LEDBLINK);
  digitalWrite(LEDBLINK, !state);
}

//* Funcion encargada en la busqueda y conexion de redes WiFi
void Connection_Wifi(char *name_wifi) {
  pinMode(LEDBLINK, OUTPUT);
  tic_led.attach(0.2, blinkingLedWifi);  // Inicia el parpadeo del led

  bool res;
  res = wm.autoConnect(name_wifi);  // Inicia la coneccion WiFi, si no hay red inicia un servidor donde buscara y se conectara a una red

  if (!res) {
    Serial.println("Conexion fallida...");
    ESP.restart();
  } else {
    Serial.println("Conectado...yeey :)");
    tic_led.detach();  // Paramos el parpadeo
    digitalWrite(LEDBLINK, HIGH);
  }
}

//* Funcion que elimina las credenciales WiFi almacenadas
void resetWifi() {
  wm.resetSettings();
  delay(500);
  ESP.restart();
}
