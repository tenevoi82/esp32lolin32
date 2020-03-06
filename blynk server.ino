
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
#include <BlynkSimpleEsp32.h>
#define BLYNK_PRINT Serial
BlynkTimer timer;

BLYNK_CONNECTED() {
	display.setTextSize(2);      // Normal 1:1 pixel scale
	display.setTextColor(SSD1306_WHITE); // Draw white text
	display.setCursor(10, 0);     // Start at top-left corner
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

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(1)
{
	int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
	Serial.println("run");



	display.setTextSize(3);      // Normal 1:1 pixel scale
	display.setTextColor(SSD1306_WHITE); // Draw white text
	display.setCursor(pinValue * 10, 0);     // Start at top-left corner
	display.cp437(true);         // Use full 256 char 'Code Page 437' font
	display.clearDisplay();
	display.println(pinValue);
	display.display();
	// process received value
}

BLYNK_WRITE(3)
{
	String action = param.asString(); // assigning incoming value from pin V1 to a variable
	if (action == "play")player.play();
	if (action == "stop")player.stop();
	if (action == "next")player.next();
	if (action == "prev")player.previous();
	Blynk.setProperty(V3, "label", action);

	Serial.println(action);
}
BLYNK_WRITE(20)
{
	int action = param.asInt(); // assigning incoming value from pin V1 to a variable

	Blynk.setProperty(V20, "label", action);
	player.play(action);
	Serial.println(action);
}