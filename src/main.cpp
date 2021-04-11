#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncDNSServer.h>
#include <ESPAsyncWebServer.h>
#include <configuration.h>

// Global Objects
AsyncDNSServer dnsServer;
AsyncWebServer webServer(PORT);

// Global Properties
enum Patterns { LED1=1, LED2, LED3, LED4 };
Patterns pattern = LED1;

// Pages
const char * indexPage =
#include "html/index.min.html"
;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up");

  WiFi.softAP(SSID, PASSWORD, CHANNEL, HIDDEN, MAX_CLIENTS) ? Serial.println("Wifi Network Started")
                                                            : Serial.println("Wifi Network Failed to Start");


  dnsServer.setErrorReplyCode(AsyncDNSReplyCode::ServerFailure);
  dnsServer.start(53, DOMAIN_NAME, IPAddress(192,168,4,1));

  // Register Routes
  webServer.on("/", HTTP_GET, [] (AsyncWebServerRequest *request) {
    char response[1000];
    sprintf(response, indexPage, "Test Title", pattern, 100);
    request->send(200, "text/html", response);
  });
  webServer.on("/led1", HTTP_GET, [] (AsyncWebServerRequest *request) {
    pattern = LED1;
    request->redirect("/");
  });
  webServer.on("/led2", HTTP_GET, [] (AsyncWebServerRequest *request) {
    pattern = LED2;
    request->redirect("/");
  });
  webServer.on("/led3", HTTP_GET, [] (AsyncWebServerRequest *request) {
    pattern = LED3;
    request->redirect("/");
  });
  webServer.on("/led4", HTTP_GET, [] (AsyncWebServerRequest *request) {
    pattern = LED4;
    request->redirect("/");
  });

  webServer.begin();

  // Turn on onboard LED for status
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  switch (pattern) {
    case LED1:
      // Run LED Function
      break;
    case LED2:
      // Run LED Function
      break;
    case LED3:
      // Run LED Function
      break;
    case LED4:
      // Run LED Function
      break;
  }
}
