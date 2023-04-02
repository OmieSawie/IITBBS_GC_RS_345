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

		char * charPayload = strdup(String(payload).c_str());
		testdrawtext(charPayload,ST7735_WHITE);

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



void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0,0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}


