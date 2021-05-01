#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncDNSServer.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_NeoPixel.h>
#include <configuration.h>

// Global Objects
AsyncDNSServer dnsServer;
AsyncWebServer webServer(PORT);
Adafruit_NeoPixel strip(LED_COUNT, LED_CONTROL_PIN, NEO_GRB + NEO_KHZ800);

// Global Properties
enum Patterns { OFF, LED1, LED2, LED3, LED4};
Patterns pattern = OFF;

// Pages
const char * indexPage =
#include "html/index.min.html"
;

// LED State
uint8_t val = 0;
uint8_t dir = 0;

void setup() {

  Serial.begin(9600);
  Serial.println("Starting up");

  randomSeed(analogRead(0)); // Use noise on A0 as random seed

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
  webServer.on("/off", HTTP_GET, [] (AsyncWebServerRequest *request) {
    pattern = OFF;
    request->redirect("/");
  });

  webServer.begin();

  // Turn on onboard LED for status
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Neopixel Setup
  strip.begin();
  strip.show();
}

void loop() {
  switch (pattern) {
    case OFF:
      strip.clear();
      strip.show();
      break;
    case LED1:
      for (size_t i = 0; i < LED_COUNT; i++) {
        strip.clear();
        strip.setPixelColor(i, 255, 255, 255);
        strip.setPixelColor((i + LED_COUNT / 2) % LED_COUNT, 255, 255, 255);
        strip.setBrightness(255/3);
        strip.show();
        delay(100);
      }
      break;
    case LED2:
      strip.clear();
      strip.setPixelColor(random(LED_COUNT), random(255), random(255), random(255));
      strip.setBrightness(255/3);
      strip.show();
      delay(150);
      break;
    case LED3:
      strip.fill(Adafruit_NeoPixel::Color(255, 0 + val, 0), 0, 8);
      strip.fill(Adafruit_NeoPixel::Color(255, 255, 0 + val), 9, 16);
      strip.fill(Adafruit_NeoPixel::Color(0, 255 - val, 255), 17, LED_COUNT);
      strip.setBrightness(255/3);
      delay(10);
      strip.show();
      if(val == 255) {
        dir = -1;
      }
      else if(val == 0) {
        dir = 1;
      }
      val += dir;
      break;
    case LED4:
      uint32_t randColor = Adafruit_NeoPixel::Color(random(255), random(255), random(255));
      for (size_t i = 0; i < LED_COUNT; i++) {
        strip.setPixelColor(i, randColor);
        strip.setPixelColor((i + LED_COUNT / 2) % LED_COUNT, randColor);
        strip.setBrightness(255/3);
        strip.show();
        delay(50);
      }
      for (size_t i = 0; i < LED_COUNT; i++) {
        strip.setPixelColor(i, 0, 0, 0);
        strip.setPixelColor((i + LED_COUNT / 2) % LED_COUNT, 0, 0, 0);
        strip.setBrightness(255/3);
        strip.show();
        delay(50);
      }
      break;
  }
}
