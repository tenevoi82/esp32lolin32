


/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This sketch shows how to read values from Virtual Pins

  App project setup:
    Slider widget (0...100) on Virtual Pin V1
 *************************************************************/

/* Comment this out to disable prints and save space */

#include <DFRobotDFPlayerMini.h>
#include <Adafruit_SSD1306.h>
#include <EnvironmentCalculations.h>
#include <BME280SpiSw.h>
#include <BME280Spi.h>
#include <BME280I2C_BRZO.h>
#include <BME280I2C.h>
#include <BME280.h>

#define BLYNK_PRINT Serial

int threshold = 40;
bool touch1detected = false;
bool touch2detected = false;
bool touch1touched = false;
bool touch2touched = false;
auto touch1start = millis();
auto touch2start = millis();

void gotTouch1() {
	touch1start = millis();
}

void gotTouch2() {
	touch2start = millis();
}


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <Wire.h>
#include <SPI.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "QJ21QtY7b3G4otFfUoV3p2bezn6vDFvD";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "tenevoi";
char pass[] = "dimadima";


BlynkTimer timer;
BME280I2C bme;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NUMFLAKES     10 // Number of snowflakes in the animation example
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
DFRobotDFPlayerMini player;

static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };


float temp(NAN), hum(NAN), pres(NAN);
BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
BME280::PresUnit presUnit(BME280::PresUnit_torr);

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{

	bme.read(pres, temp, hum, tempUnit, presUnit);
	// You can send any value at any time.
	// Please don't send more that 10 values per second.
	Blynk.virtualWrite(V10, temp);
	Blynk.virtualWrite(V11, hum);
	Blynk.virtualWrite(V12, pres);
	printBMEValue();

}


// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.println("run");



  display.setTextSize(3);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(pinValue*10, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.clearDisplay();
  display.println(pinValue);
  display.display();
  // process received value
}


void printBMEValue() {
	static bool h = true;
	display.setTextSize(1);
	display.clearDisplay();
	display.setCursor(0, 0);

	display.print(temp);
	display.print(" C");
	if (h)display.print('.');
	h = !h;
	display.println();

	display.print(hum);
	display.print(" H");
	display.println();

	display.print(pres);
	display.print(" P");
	display.println();


	display.display();
}

BLYNK_CONNECTED() {
	display.setTextSize(2);      // Normal 1:1 pixel scale
	display.setTextColor(SSD1306_WHITE); // Draw white text
	display.setCursor( 10, 0);     // Start at top-left corner
	display.cp437(true);         // Use full 256 char 'Code Page 437' font
	display.clearDisplay();
	display.println("Connected to server");
	Serial.println("Connected to server");
	display.display();

}

BLYNK_APP_DISCONNECTED() {
	display.setTextSize(2);      // Normal 1:1 pixel scale
	display.setTextColor(SSD1306_WHITE); // Draw white text
	display.setCursor(0, 0);     // Start at top-left corner
	display.cp437(true);         // Use full 256 char 'Code Page 437' font
	display.clearDisplay();
	Serial.println("APP disconnected");
	display.println("APP disconnected");
	display.display();
	timer.changeInterval(0, 10000L);
}
BLYNK_APP_CONNECTED() {
	display.setTextSize(2);      // Normal 1:1 pixel scale
	display.setTextColor(SSD1306_WHITE); // Draw white text
	display.setCursor(0, 0);     // Start at top-left corner
	display.cp437(true);         // Use full 256 char 'Code Page 437' font
	display.clearDisplay();
	Serial.println("APP connected");
	display.println("APP connected");
	display.display();
	timer.changeInterval(0, 200L);
}


BLYNK_DISCONNECTED() {
	display.setTextSize(2);      // Normal 1:1 pixel scale
	display.setTextColor(SSD1306_WHITE); // Draw white text
	display.setCursor(0, 0);     // Start at top-left corner
	display.cp437(true);         // Use full 256 char 'Code Page 437' font
	display.clearDisplay();
	display.println("Disconncted from server");
	Serial.println("Disconncted from server");
	display.display();		
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1,16,17);
  Serial.println("Start");
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  while (!player.begin(Serial2)) {  //Use softwareSerial to communicate with mp3.
	  Serial.println(F("Unable to begin:"));
	  Serial.println(F("1.Please recheck the connection!"));
	  Serial.println(F("2.Please insert the SD card!"));
	  delay(1000);
  }
  player.enableLoopAll();
  delay(500);
  player.volume(8);
  //delay(500);
  //auto startsens = millis();
  //long c=0;
  //long unsigned int  s = 0LL;
  //Serial.println("Start sens udapting");
  //while (c < 50000) {
	 // int p = touchRead(T2);
	 // if (p < threshold)
		//  threshold = p;
	 // c++;
  //}
  //threshold--;
  //threshold = 40;
  ////threshold = s / c;
  //Serial.print("thresh = ");
  //Serial.println(threshold);
  touchAttachInterrupt(T2, gotTouch1, threshold);
  touchAttachInterrupt(T3, gotTouch2, threshold);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
	  Serial.println(F("SSD1306 allocation failed"));
	  for (;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
// the library initializes this with an Adafruit splash screen.
  //display.display();
  //delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();


  while (!bme.begin())
  {
	  Serial.println("Could not find BME280 sensor!");
	  delay(1000);
  }
  // bme.chipID(); // Deprecated. See chipModel().
  switch (bme.chipModel())
  {
  case BME280::ChipModel_BME280:
	  Serial.println("Found BME280 sensor! Success.");
	  break;
  case BME280::ChipModel_BMP280:
	  Serial.println("Found BMP280 sensor! No Humidity available.");
	  break;
  default:
	  Serial.println("Found UNKNOWN sensor! Error!");
  }
  BME280::Settings set = bme.getSettings();
  set.filter = BME280::Filter::Filter_16;
  set.mode = BME280::Mode::Mode_Normal;
  set.standbyTime = BME280::StandbyTime::StandbyTime_1000ms;
  set.humOSR = BME280::OSR::OSR_X16;
  set.tempOSR = BME280::OSR::OSR_X16;
  set.presOSR = BME280::OSR::OSR_X16;
  bme.setSettings(set);



 pinMode(17, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);

}

void loop()
{

	if (millis()-touch1start>50 && touch1touched) {
		touch1touched = false;
		Serial.println("Touch 1 detected");
		Serial.println(touchRead(T2));
	}
	if (millis() - touch1start <= 50 && !touch1touched) {
		touch1touched = true;
		Serial.println("Touch 1 detected ");
	}
	if (touch2detected) {
		touch2detected = false;
		Serial.println("Touch 2 detected");
		Serial.println(touchRead(T3));
	}
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
  //Serial.println(touchRead(T2));
  if (player.available()) {
	  printDetail(player.readType(), player.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
}


void testdrawline() {
	int16_t i;

	display.clearDisplay(); // Clear display buffer

	for (i = 0; i < display.width(); i += 4) {
		display.drawLine(0, 0, i, display.height() - 1, SSD1306_WHITE);
		display.display(); // Update screen with each newly-drawn line
		delay(1);
	}
	for (i = 0; i < display.height(); i += 4) {
		display.drawLine(0, 0, display.width() - 1, i, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	delay(250);

	display.clearDisplay();

	for (i = 0; i < display.width(); i += 4) {
		display.drawLine(0, display.height() - 1, i, 0, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	for (i = display.height() - 1; i >= 0; i -= 4) {
		display.drawLine(0, display.height() - 1, display.width() - 1, i, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	delay(250);

	display.clearDisplay();

	for (i = display.width() - 1; i >= 0; i -= 4) {
		display.drawLine(display.width() - 1, display.height() - 1, i, 0, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	for (i = display.height() - 1; i >= 0; i -= 4) {
		display.drawLine(display.width() - 1, display.height() - 1, 0, i, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	delay(250);

	display.clearDisplay();

	for (i = 0; i < display.height(); i += 4) {
		display.drawLine(display.width() - 1, 0, 0, i, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	for (i = 0; i < display.width(); i += 4) {
		display.drawLine(display.width() - 1, 0, i, display.height() - 1, SSD1306_WHITE);
		display.display();
		delay(1);
	}

	delay(2000); // Pause for 2 seconds
}

void testdrawrect(void) {
	display.clearDisplay();

	for (int16_t i = 0; i < display.height() / 2; i += 2) {
		display.drawRect(i, i, display.width() - 2 * i, display.height() - 2 * i, SSD1306_WHITE);
		display.display(); // Update screen with each newly-drawn rectangle
		delay(1);
	}

	delay(2000);
}

void testfillrect(void) {
	display.clearDisplay();

	for (int16_t i = 0; i < display.height() / 2; i += 3) {
		// The INVERSE color is used so rectangles alternate white/black
		display.fillRect(i, i, display.width() - i * 2, display.height() - i * 2, SSD1306_INVERSE);
		display.display(); // Update screen with each newly-drawn rectangle
		delay(1);
	}

	delay(2000);
}

void testdrawcircle(void) {
	display.clearDisplay();

	for (int16_t i = 0; i < max(display.width(), display.height()) / 2; i += 2) {
		display.drawCircle(display.width() / 2, display.height() / 2, i, SSD1306_WHITE);
		display.display();
		delay(1);
	}

	delay(2000);
}

void testfillcircle(void) {
	display.clearDisplay();

	for (int16_t i = max(display.width(), display.height()) / 2; i > 0; i -= 3) {
		// The INVERSE color is used so circles alternate white/black
		display.fillCircle(display.width() / 2, display.height() / 2, i, SSD1306_INVERSE);
		display.display(); // Update screen with each newly-drawn circle
		delay(1);
	}

	delay(2000);
}

void testdrawroundrect(void) {
	display.clearDisplay();

	for (int16_t i = 0; i < display.height() / 2 - 2; i += 2) {
		display.drawRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i,
			display.height() / 4, SSD1306_WHITE);
		display.display();
		delay(1);
	}

	delay(2000);
}

void testfillroundrect(void) {
	display.clearDisplay();

	for (int16_t i = 0; i < display.height() / 2 - 2; i += 2) {
		// The INVERSE color is used so round-rects alternate white/black
		display.fillRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i,
			display.height() / 4, SSD1306_INVERSE);
		display.display();
		delay(1);
	}

	delay(2000);
}

void testdrawtriangle(void) {
	display.clearDisplay();

	for (int16_t i = 0; i < max(display.width(), display.height()) / 2; i += 5) {
		display.drawTriangle(
			display.width() / 2, display.height() / 2 - i,
			display.width() / 2 - i, display.height() / 2 + i,
			display.width() / 2 + i, display.height() / 2 + i, SSD1306_WHITE);
		display.display();
		delay(1);
	}

	delay(2000);
}

void testfilltriangle(void) {
	display.clearDisplay();

	for (int16_t i = max(display.width(), display.height()) / 2; i > 0; i -= 5) {
		// The INVERSE color is used so triangles alternate white/black
		display.fillTriangle(
			display.width() / 2, display.height() / 2 - i,
			display.width() / 2 - i, display.height() / 2 + i,
			display.width() / 2 + i, display.height() / 2 + i, SSD1306_INVERSE);
		display.display();
		delay(1);
	}

	delay(2000);
}

void testdrawchar(void) {
	display.clearDisplay();

	display.setTextSize(1);      // Normal 1:1 pixel scale
	display.setTextColor(SSD1306_WHITE); // Draw white text
	display.setCursor(0, 0);     // Start at top-left corner
	display.cp437(true);         // Use full 256 char 'Code Page 437' font

	// Not all the characters will fit on the display. This is normal.
	// Library will draw what it can and the rest will be clipped.
	for (int16_t i = 0; i < 256; i++) {
		if (i == '\n') display.write(' ');
		else          display.write(i);
	}

	display.display();
	delay(2000);
}

void testdrawstyles(void) {
	display.clearDisplay();

	display.setTextSize(1);             // Normal 1:1 pixel scale
	display.setTextColor(SSD1306_WHITE);        // Draw white text
	display.setCursor(0, 0);             // Start at top-left corner
	display.println(F("Hello, world!"));

	display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
	display.println(3.141592);

	display.setTextSize(2);             // Draw 2X-scale text
	display.setTextColor(SSD1306_WHITE);
	display.print(F("0x")); display.println(0xDEADBEEF, HEX);

	display.display();
	delay(2000);
}

void testscrolltext(void) {
	display.clearDisplay();

	display.setTextSize(2); // Draw 2X-scale text
	display.setTextColor(SSD1306_WHITE);
	display.setCursor(10, 0);
	display.println(F("scroll"));
	display.display();      // Show initial text
	delay(100);

	// Scroll in various directions, pausing in-between:
	display.startscrollright(0x00, 0x0F);
	delay(2000);
	display.stopscroll();
	delay(1000);
	display.startscrollleft(0x00, 0x0F);
	delay(2000);
	display.stopscroll();
	delay(1000);
	display.startscrolldiagright(0x00, 0x07);
	delay(2000);
	display.startscrolldiagleft(0x00, 0x07);
	delay(2000);
	display.stopscroll();
	delay(1000);
}

void testdrawbitmap(void) {
	display.clearDisplay();

	display.drawBitmap(
		(display.width() - LOGO_WIDTH) / 2,
		(display.height() - LOGO_HEIGHT) / 2,
		logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
	display.display();
	delay(1000);
}

#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2

void testanimate(const uint8_t* bitmap, uint8_t w, uint8_t h) {
	int8_t f, icons[NUMFLAKES][3];

	// Initialize 'snowflake' positions
	for (f = 0; f < NUMFLAKES; f++) {
		icons[f][XPOS] = random(1 - LOGO_WIDTH, display.width());
		icons[f][YPOS] = -LOGO_HEIGHT;
		icons[f][DELTAY] = random(1, 6);
		Serial.print(F("x: "));
		Serial.print(icons[f][XPOS], DEC);
		Serial.print(F(" y: "));
		Serial.print(icons[f][YPOS], DEC);
		Serial.print(F(" dy: "));
		Serial.println(icons[f][DELTAY], DEC);
	}
	
	for (;;) { // Loop forever...
		display.clearDisplay(); // Clear the display buffer

		// Draw each snowflake:
		for (f = 0; f < NUMFLAKES; f++) {
			display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
		}

		display.display(); // Show the display buffer on the screen
		delay(100);        // Pause for 1/10 second

		// Then update coordinates of each flake...
		for (f = 0; f < NUMFLAKES; f++) {
			icons[f][YPOS] += icons[f][DELTAY];
			// If snowflake is off the bottom of the screen...
			if (icons[f][YPOS] >= display.height()) {
				// Reinitialize to a random position, just off the top
				icons[f][XPOS] = random(1 - LOGO_WIDTH, display.width());
				icons[f][YPOS] = -LOGO_HEIGHT;
				icons[f][DELTAY] = random(1, 6);
			}
		}
	}
}



void printDetail(uint8_t type, int value) {
	switch (type) {
	case TimeOut:
		Serial.println(F("Time Out!"));
		break;
	case WrongStack:
		Serial.println(F("Stack Wrong!"));
		break;
	case DFPlayerCardInserted:
		Serial.println(F("Card Inserted!"));
		break;
	case DFPlayerCardRemoved:
		Serial.println(F("Card Removed!"));
		break;
	case DFPlayerCardOnline:
		Serial.println(F("Card Online!"));
		break;
	case DFPlayerUSBInserted:
		Serial.println("USB Inserted!");
		break;
	case DFPlayerUSBRemoved:
		Serial.println("USB Removed!");
		break;
	case DFPlayerPlayFinished:
		Serial.print(F("Number:"));
		Serial.print(value);
		Serial.println(F(" Play Finished!"));
		break;
	case DFPlayerError:
		Serial.print(F("DFPlayerError:"));
		switch (value) {
		case Busy:
			Serial.println(F("Card not found"));
			break;
		case Sleeping:
			Serial.println(F("Sleeping"));
			break;
		case SerialWrongStack:
			Serial.println(F("Get Wrong Stack"));
			break;
		case CheckSumNotMatch:
			Serial.println(F("Check Sum Not Match"));
			break;
		case FileIndexOut:
			Serial.println(F("File Index Out of Bound"));
			break;
		case FileMismatch:
			Serial.println(F("Cannot Find File"));
			break;
		case Advertise:
			Serial.println(F("In Advertise"));
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}