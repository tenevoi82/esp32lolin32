#include <BME280I2C.h>
#include <DFRobotDFPlayerMini.h>


#include <Adafruit_SSD1306.h>
#include <EnvironmentCalculations.h>
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include <WiFiClient.h>

#include <Wire.h>
#include <SPI.h>

const char auth[] = "QJ21QtY7b3G4otFfUoV3p2bezn6vDFvD";
char ssid[] = "tenevoi";
char pass[] = "dimadima";


extern Adafruit_SSD1306 display;
extern BlynkTimer timer;
extern BME280I2C bme;
extern BME280::TempUnit tempUnit;
extern BME280::PresUnit presUnit;
extern DFRobotDFPlayerMini player;
extern float temp, hum, pres;
extern int filecount;

void myTimerEvent()
{
	// You can send any value at any time.
	// Please don't send more that 10 values per second.
	bme.read(pres, temp, hum, tempUnit, presUnit);
	Blynk.virtualWrite(V10, temp);
	Blynk.virtualWrite(V11, hum);
	Blynk.virtualWrite(V12, pres);
	printBMEValue();
}

void printBMEValue() {
	static bool h = true;
	display.setTextSize(2);
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


void setup()
{
  Serial.begin(115200);
  PlayerSetup();
  setupTouch();
  BMESetup();
  
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
  Blynk.setProperty(V20, "max", filecount);
}

void loop()
{
  Touchcheck();
  Blynk.run();
  timer.run(); 
  PlayerRun();
}