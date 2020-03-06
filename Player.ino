#include <DFRobotDFPlayerMini.h>
DFRobotDFPlayerMini player;


int filecount;

void PlayerSetup() {
	Serial2.begin(9600, SERIAL_8N1, 16, 17);
	Serial.println("Start");
	Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
	delay(100);
	while (!player.begin(Serial2)) {  //Use softwareSerial to communicate with mp3.
		Serial.println(F("Unable to begin:"));
		Serial.println(F("1.Please recheck the connection!"));
		Serial.println(F("2.Please insert the SD card!"));
		delay(1000);
	}

	filecount = player.readFileCounts();
	Serial.print("files found ");
	Serial.println(filecount);
	player.volume(10);
	int r = random(filecount);
	Serial.print("Plaing file number ");
	Serial.println(r);
	player.play(r);
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

void PlayerRun() {
	static auto m = millis();
	if (player.available()) {
		printDetail(player.readType(), player.read());
		if (millis() - m > 500) {
			m = millis();
			player.next();
		}
	}
}