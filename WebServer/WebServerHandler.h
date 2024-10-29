#ifndef WEB_SERVER_HANDLER_H
#define WEB_SERVER_HANDLER_H

#include <Arduino.h>
#include <WiFiS3.h>
#include <ArduinoHttpClient.h>

extern const char* ssid;
extern const char* password;

extern WiFiSSLClient client;
extern WiFiServer server;
extern String active;
extern String inactive;

void setupWifi();
void openWebServer(int activator);
String getHTTPContent(char *aServerName, char *aPath, uint16_t aServerPort);

#endif