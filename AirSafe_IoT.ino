#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Smoke Detector System"
#define BLYNK_AUTH_TOKEN "qu3MLaPREtmZd7vv1j4Q1sV9nMF0d56w"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "off ja";
char pass[] = "12345678";

BlynkTimer timer;

const int smokeA0 = 34;
int sensorThres = 100;
int data;

void sendSensor() {
    data = analogRead(smokeA0);
    Blynk.virtualWrite(V0, data);

    if (data > 34) {
        Blynk.logEvent("smoke_has_been_detected_in_the_house", "Smoke has been detected in the house");

        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(30, 0);
        display.println(F("Smoke"));
        display.setCursor(15, 20);
        display.println(F("has been"));
        display.setCursor(15, 45);
        display.println(F("Detected."));
        display.display();
    } else {
        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(15, 15);
        display.println(F("No smoke"));
        display.setCursor(15, 45);
        display.println(F("Detected."));
        display.display();
    }
}

void setup() {
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
    pinMode(smokeA0, INPUT);
    timer.setInterval(2500L, sendSensor);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        return;  // Exit setup instead of infinite loop
    }

    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    display.println(F("Initializing..."));
    display.display();
}

void loop() {
    Blynk.run();
    timer.run();
}
