#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <math.h> 

#include <ArduinoJson.h>

#define TFT_CS        10
#define TFT_RST        7 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         9


//Set up some default colours
#define GROUNDCOLOR 0x00ff00
#define SKYCOLOR 0x0000ff


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);




void setup(void) {
Serial.begin(9600);
	tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
	tft.setRotation(0); // set display orientation 
    tft.fillScreen(GROUNDCOLOR);
	tft.fillRect(0,0,128,32,SKYCOLOR);
	delay(100);

	uint8_t time = millis();

	tft.fillScreen(GROUNDCOLOR);
	tft.fillRect(0,0,128,32,SKYCOLOR);

	//This is the start screen
	/* print_text(10,40,"A WALK IN",2,0xff0000); */
	/* print_text(5,60," THE PARK ",2,0xff0000); */
	/* print_text(20,90,"Whip to start",1,0xff0000); */

	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	tft.fillScreen(ST7735_BLACK);

}

void loop() { // run over and over
	if (Serial.available()) {
		
		StaticJsonDocument<500> doc;

		String str = Serial.readString();
		/* Serial.println("Hello"); */
		DeserializationError error = deserializeJson(doc, str);

		// Test if parsing succeeds.
		if (error) {
			Serial.print(F("deserializeJson() failed: "));
			Serial.println(error.f_str());
			return;
		}else{
		/* deserializeJson(doc,str); */
		/* serializeJson(doc["rate"],Serial); */
		/* char* charStr = str.c_str(); */
		/* Serial.print(str); */
		/* char* time = strdup(String(doc["time"]).c_str()); */
		/* char* asset_id_base = strdup(String(doc["asset_id_base"]).c_str()); */
		/* char* asset_id_quote = strdup(String(doc["asset_id_quote"]).c_str()); */
		/* char* rate = strdup(String(doc["rate"]).c_str()); */
		String time;
		String asset_id_base;
		String asset_id_quote;
		String rate;
		serializeJson(doc["time"],time);
		serializeJson(doc["asset_id_base"],asset_id_base);
		serializeJson(doc["asset_id_quote"],asset_id_quote);
		serializeJson(doc["rate"],rate);


		serializeJson(doc["time"],Serial);
		serializeJson(doc["asset_id_base"],Serial);
		serializeJson(doc["asset_id_quote"],Serial);
		serializeJson(doc["rate"],Serial);
		
		char* timeCh, *asset_id_baseCh,*asset_id_quoteCh,*rateCh;
		timeCh = strdup(time.c_str());
		timeCh = strtok(timeCh,".");
		asset_id_baseCh =  strdup(asset_id_base.c_str());
		asset_id_quoteCh = strdup(asset_id_quote.c_str());
		rateCh = strdup(rate.c_str());

		displayData(timeCh,asset_id_baseCh,asset_id_quoteCh,rateCh);
		delay(5000);
		tft.fillScreen(ST7735_BLACK);
		
		}

	}
}





void print_text(byte x_pos, byte y_pos, char *text, byte text_size, uint16_t color) {		//print char* array to the screen
  tft.setCursor(x_pos, y_pos);
  tft.setTextSize(text_size);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}


void displayData(char* chS, char* aib, char* aiq, char* rate){
	print_text(0,10,chS,1,ST7735_WHITE);
	print_text(30,40,aib,2,ST7735_WHITE);
	print_text(30,80,aiq,1,ST7735_WHITE);
	print_text(30,100,rate,1,ST7735_WHITE);
}

