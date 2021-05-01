#pragma once

/////////////////////////////////////////////////
/// General Configuration
/////////////////////////////////////////////////

// Turn Status LED On?
#define STATUS false


/////////////////////////////////////////////////
/// Wifi Configuration
/////////////////////////////////////////////////

// Set the Network Name
#define SSID "Gradcap"

// Set the network password (if blank open network)
#define PASSWORD ""

// Make the network hidden?
#define HIDDEN false

// Maximum number of simultaneous connected clients (0 - 8)
#define MAX_CLIENTS 4

// Set the wifi channel (Useful if in congested networks)
#define CHANNEL 6


/////////////////////////////////////////////////
/// Webserver Configuration
/////////////////////////////////////////////////

// Domain name of the webserver -- also used in DNS requests
#define DOMAIN_NAME "gradcap.io"

// Webserver Port
#define PORT 80


/////////////////////////////////////////////////
/// Pinout Configuration
/////////////////////////////////////////////////

// Neopixel Data Control Pin
#define LED_CONTROL_PIN 5

// LED Count(For Addressing)
#define LED_COUNT 26

//  Pixel Type:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
#define PIXEL_TYPE NEO_GRB + NEO_KHZ800
