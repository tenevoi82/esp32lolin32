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

