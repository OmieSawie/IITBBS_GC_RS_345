#include <SoftwareSerial.h>
#include <SPI.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>


// Uncomment whatever type you're using!
//#define DHTTYPE DHT11 // DHT 11
#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)



const char* ssid = "Galaxy M51EE8C";
const char* password = "pgep2193";

//Your Domain name with URL path or IP address with path
String serverName = "http://rest-sandbox.coinapi.io/v1/exchangerate";

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

  /* Serial.begin(115200); */ 
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  /* Serial.println("Connecting"); */
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    /* Serial.print("."); */
  }
  /* Serial.println(""); */
  /* Serial.print("Connected to WiFi network with IP Address: "); */
  /* Serial.println(WiFi.localIP()); */
 
  /* Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading."); */
}

void loop() {
  // Send an HTTP POST request depending on timerDelay
  /* if ((millis() - lastTime) > timerDelay) { */
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
	
	for(int i=0;i<6;i++){
      /* String serverPath = serverName + "/BTC/USD?apikey=BCEC2DF6-46FC-4F25-9C9A-0A61A647AF47"; */
	  String serverPath = serverName + currencies[i][1];
	  serverPath = serverPath + "/USD?apikey=5F67685F-A31A-4C86-8AB5-792024A7FAA9";
		/* serverPath = serverPath + "/USD?apikey=BCEC2DF6-46FC-4F25-9C9A-0A61A647AF47"; */


      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
	  /* http.addHeader("X-CoinAPI-Key","BCEC2DF6-46FC-4F25-9C9A-0A61A647AF47"); */
  
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
        
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
		/* Serial.println(serverPath); */
        /* Serial.print("HTTP Response code: "); */
        /* Serial.println(httpResponseCode); */
		char json[] =
      "{\"time\":\"123456\",\"asset_id_base\":\"13518sada120\",\"asset_id_quote\":\"9876\",\"rate\":\"assd\"}";

        String payload = http.getString();
		StaticJsonDocument<500> doc;
		deserializeJson(doc,json);
        /* Serial.println(doc["rate"]); */
		/* serializeJson(doc["time"],Serial); */
		/* serializeJson(doc["asset_id_base"],Serial); */
		/* serializeJson(doc["asset_id_quote"],Serial); */
		/* serializeJson(doc["rate"],Serial); */
		serializeJsonPretty(doc,Serial);
		
		char * charPayload = strdup(String(payload).c_str());
		/* Serial.print(payload); */
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
	  delay(5000);
	  }
    }
    else {
      /* Serial.println("WiFi Disconnected"); */
    }


  /* } */
  while(true){
	delay(5000);
  }
}


