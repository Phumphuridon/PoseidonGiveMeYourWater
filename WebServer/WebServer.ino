#include "WebServerHandler.h"

void setup(){
  pinMode(7, INPUT);
  setupWifi();
}

void loop(){
  openWebServer(digitalRead(7));
}