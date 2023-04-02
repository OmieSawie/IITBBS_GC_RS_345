/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  
  Code compatible with ESP8266 Boards Version 3.0.0 or above 
  (see in Tools > Boards > Boards Manager > ESP8266)
*/


#include <Adafruit_GFX.h>    // Core graphics library
#include <XTronical_ST7735.h> // Hardware-specific library
#include <SPI.h>

// set up pins we are going to use to talk to the screen
#define TFT_DC     D4       // register select (stands for Data Control perhaps!)
#define TFT_RST   D3         // Display reset pin, you can also connect this to the ESP8266 reset
                            // in which case, set this #define pin to -1!
#define TFT_CS   D2       // Display enable (Chip select), if not enabled will not talk on SPI bus


// initialise the routine to talk to this display with these pin connections (as we've missed off
// TFT_SCLK and TFT_MOSI the routine presumes we are using hardware SPI and internally uses 13 and 11
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);  

float p = 3.1415926;


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

const char* ssid = "Galaxy M51EE8C";
const char* password = "pgep2193";

//Your Domain name with URL path or IP address with path
String serverName = "http://rest.coinapi.io/v1/exchangerate/";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 10000;

String currencies[6][2] = {
	{"Bitcoin","BTC"},
	{"Ethereum","ETC"},
	{"Dogecoin","DOGE"},
	{"Solana","SOL"},
	{"BNB","BNB"},
	{"Litecoin","LTC"},
} ;



void setup() {
	tft.init();   // initialize a ST7735S chip,

  /* Serial.begin(115200); */ 
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  // Send an HTTP POST request depending on timerDelay
  /* if ((millis() - lastTime) > timerDelay) { */
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
	
	for(int i=0;i<6;i++){
	tft.fillScreen(ST7735_BLACK);
      /* String serverPath = serverName + "/BTC/USD?apikey=BCEC2DF6-46FC-4F25-9C9A-0A61A647AF47"; */
	  String serverPath = serverName + currencies[i][1];
	  serverPath = serverPath + "/USD?apikey=5F67685F-A31A-4C86-8AB5-792024A7FAA9";

      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
	  /* http.addHeader("X-CoinAPI-Key","BCEC2DF6-46FC-4F25-9C9A-0A61A647AF47"); */
  
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
        
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
		Serial.println(serverPath);
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
		
		/* DynamicJsonDocument doc(1024); */
		/* deserializeJson(doc,http); */
		/* Serial.println(doc); */
		
		char * charPayload = strdup(String(payload).c_str());

		/* String strPayload = String(payload); */
		/* char* charPayload = strPayload.c_str(); */

		testdrawtext(charPayload,ST7735_WHITE);

		/* const char* sensor = doc["sensor"]; */
		/* long time          = doc["time"]; */
		/* double latitude    = doc["data"][0]; */
		/* double longitude   = doc["data"][1]; */

      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
	  delay(2000);
	  }
    }
    else {
      Serial.println("WiFi Disconnected");
    }


  /* } */
  while(true){
	delay(5000);
  }
}











/* Demo for XTronical 7735 driver library for generic 128x128 pixel
   TFT displays, based on the one from ADAFruit, their original
   header comments are below.
 */

/***************************************************
  This is a library for the genric 1.8" SPI display.

This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
The 1.8" TFT shield
  ----> https://www.adafruit.com/product/802
The 1.44" TFT breakout
  ----> https://www.adafruit.com/product/2088
as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/



/* void Demo(uint16_t rotation) */
/* { */

/*   tft.setRotation(rotation); */
/*   uint16_t time = millis(); */
/*   tft.fillScreen(ST7735_BLACK); */
/*   time = millis() - time; */

/*   delay(500); */

/*   // large block of text */
/*   tft.fillScreen(ST7735_BLACK); */
 
/*   testdrawtext("This is a test of some very log text that I written for the sole purpose of checking if the display displays very long text correctly.", ST7735_WHITE); */
/*   delay(1000); */

/*   // tft print function! */
/*   tftPrintTest(); */
/*   delay(4000); */

/*   // a single pixel */
/*   tft.drawPixel(tft.width()/2, tft.height()/2, ST7735_GREEN); */
/*   delay(500); */

/*   testdrawrects(ST7735_GREEN); */
/*   delay(500); */

/*   testfillrects(ST7735_YELLOW, ST7735_MAGENTA); */
/*   delay(500); */

/*   tft.fillScreen(ST7735_BLACK); */
/*   testfillcircles(10, ST7735_BLUE); */
/*   testdrawcircles(10, ST7735_WHITE); */
/*   delay(500); */

/*   testroundrects(); */
/*   delay(500); */

/*   testtriangles(); */
/*   delay(1000); */
/*   for(int i=2;i>0;i--) */
/*   { */
/*     tft.invertDisplay(true); */
/*     delay(500); */
/*     tft.invertDisplay(false); */
    delay(500);
  }
}



void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0,0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}

void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.println("I'm running");
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(3);
  tft.println("on a");
  tft.setTextColor(ST7735_BLUE);
  tft.println("NodeMCU");
  tft.setTextSize(4);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Ha ha!");
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST7735_GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST7735_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST7735_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST7735_WHITE);
  tft.print(" seconds.");
}

void mediabuttons() {
  // play
  tft.fillScreen(ST7735_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST7735_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
}
void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}
void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  tft.fillScreen(ST7735_BLACK);
  int color = 0xF800;
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0 ; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  tft.fillScreen(ST7735_BLACK);
  int color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft.width()-2;
    int h = tft.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}
