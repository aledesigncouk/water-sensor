#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// #include <DFRobot_SIM808.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Wire.h>
// #include <sim808.h>

// Declaration for SSD1306 display connected using I2C
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(
    128, 64, &Wire,
    -1);  // (width, height, wire, reset pin (-1 share Arduino reset))

SoftwareSerial BTserial(0, 1);  // RX | TX

// tank sensors
const int PIN_1 = 10;      // lev 1
const int PIN_2 = 16;      // lev 2
const int PIN_3 = 14;      // lev 3
const int PIN_4 = 15;      // lev 4
const int PIN_5 = 18;      // lev 5
const int PIN_6 = 19;      // lev 6
const int PIN_WASTE = 20;  // waste full

void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);
  // set digital pins
  pinMode(PIN_1, INPUT_PULLUP);
  pinMode(PIN_2, INPUT_PULLUP);
  pinMode(PIN_3, INPUT_PULLUP);
  pinMode(PIN_4, INPUT_PULLUP);
  pinMode(PIN_5, INPUT_PULLUP);
  pinMode(PIN_6, INPUT_PULLUP);
  pinMode(PIN_WASTE, INPUT_PULLUP);

  // initialize the OLED object
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  // Clear the buffer.
  display.clearDisplay();
}

void loop() {
  int LVL_1 = digitalRead(PIN_1);      // detect the status of the pin
  int LVL_2 = digitalRead(PIN_2);      // digitalRead(LVL_3);
  int LVL_3 = digitalRead(PIN_3);      // digitalRead(LVL_4);
  int LVL_4 = digitalRead(PIN_4);      // digitalRead(LVL_5);
  int LVL_5 = digitalRead(PIN_5);      // digitalRead(LVL_6);
  int LVL_6 = digitalRead(PIN_6);      // digitalRead(LVL_7);
  int WASTE = digitalRead(PIN_WASTE);  // digitalRead(LVL_8);
  // Serial.println(LVL_1);

  // send data by Bluetooth
  BTserial.print(LVL_1);
  BTserial.print(",");
  BTserial.print(LVL_2);
  BTserial.print(",");
  BTserial.print(LVL_3);
  BTserial.print(",");
  BTserial.print(LVL_4);
  BTserial.print(",");
  BTserial.print(LVL_5);
  BTserial.print(",");
  BTserial.print(LVL_6);
  BTserial.print(",");
  BTserial.print(WASTE);
  BTserial.print(";");

  // markers
  display.setRotation(3);
  display.setCursor(4, 90);
  display.println("1-");
  display.setCursor(4, 72);
  display.println("2-");
  display.setCursor(4, 55);
  display.println("3-");
  display.setCursor(4, 38);
  display.println("4-");
  display.setCursor(4, 20);
  display.println("5-");
  display.setCursor(4, 3);
  display.println("6-");
  display.setTextColor(WHITE, BLACK);

  // level bars
  display.display();
  if (LVL_6 == 0) {
    display.fillRect(20, 0, 40, 15, WHITE);
  } else {
    display.drawRect(20, 0, 40, 15, WHITE);
  }

  if (LVL_5 == 0) {
    display.fillRect(20, 17, 40, 15, WHITE);
  } else {
    display.drawRect(20, 17, 40, 15, WHITE);
  }

  if (LVL_4 == 0) {
    display.fillRect(20, 34, 40, 15, WHITE);
  } else {
    display.drawRect(20, 34, 40, 15, WHITE);
  }

  if (LVL_3 == 0) {
    display.fillRect(20, 51, 40, 15, WHITE);
  } else {
    display.drawRect(20, 51, 40, 15, WHITE);
  }

  if (LVL_2 == 0) {
    display.fillRect(20, 68, 40, 15, WHITE);
  } else {
    display.drawRect(20, 68, 40, 15, WHITE);
  }

  if (LVL_1 == 0) {
    display.fillRect(20, 85, 40, 15, WHITE);
  } else {
    display.drawRect(20, 85, 40, 15, WHITE);
  }

  // design a better waste warn + red led
  if (WASTE == 0) {
    display.fillRect(20, 102, 40, 15, WHITE);
  } else {
    display.drawRect(20, 102, 40, 15, WHITE);
  }

  display.display();
  display.clearDisplay();

  delay(1000);
}