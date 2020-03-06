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


void setupTouch() {
	touchAttachInterrupt(T2, gotTouch1, threshold);
	touchAttachInterrupt(T3, gotTouch2, threshold);
}

void Touchcheck() {
	if (millis() - touch1start > 50 && touch1touched) {
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
}