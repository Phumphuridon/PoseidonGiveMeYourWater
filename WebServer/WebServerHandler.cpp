#include "WebServerHandler.h"

const char* ssid = "DESKTOP-POPFKGC 0291";
const char* password = "261)50mN";

WiFiSSLClient client;
WiFiServer server = WiFiServer(80);
String active = "";
String inactive = "";
int isActive = 0;

void setupWifi() {
  pinMode(7, INPUT);
  Serial.begin(9600);
  while (WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    delay(1000);
  }
  Serial.print("Connected : ");
  Serial.println(WiFi.localIP());
  
  server.begin();
  active = getHTTPContent("www.it.kmitl.ac.th", "/~it66070162/PhycomProject/status/Active.html", 443);
  inactive = getHTTPContent("www.it.kmitl.ac.th", "/~it66070162/PhycomProject/status/Inactive.html", 443);
  //getHTTPContent("www.it.kmitl.ac.th", "/~it66070162/PhycomProject/status/Active.html", 443);
}

void openWebServer() {
  WiFiClient client = server.available();  // listen for incoming clients

  if (client) {                    // if you get a client,
    Serial.println("new client");  // print a message out the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    while (client.connected()) {   // loop while the client's connected
      if (client.available()) {    // if there's bytes to read from the client,
        char c = client.read();    // read a byte, then
        Serial.write(c);           // print it out to the serial monitor
        if (c == '\n') {           // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print(digitalRead(7) ? active : inactive);

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {  // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

String getHTTPContent(char *aServerName, char *aPath, uint16_t aServerPort) {
  HttpClient http = HttpClient(client, aServerName, aServerPort);
  http.get(aPath);

  int statusCode = http.responseStatusCode();
  String response = http.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
  http.stop();

  return response;
}
