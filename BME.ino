#include <BME280SpiSw.h>
#include <BME280Spi.h>
#include <BME280I2C_BRZO.h>
#include <BME280I2C.h>
#include <BME280.h>
BME280I2C bme;

float temp(NAN), hum(NAN), pres(NAN);
BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
BME280::PresUnit presUnit(BME280::PresUnit_torr);


void BMESetup() {
	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
		Serial.println(F("SSD1306 allocation failed"));
		for (;;); // Don't proceed, loop forever
	}


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
}